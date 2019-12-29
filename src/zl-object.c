/* zl-object.c
 *
 * Copyright 2019 Leesoo Ahn <yisooan@fedoraproject.org>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <priv/zl-mem.h>
#include <zl-object.h>

struct _zl_object_t
{
  void          *next;
  zl_tlv_cmn_t  *tlv;

  int  (*fn_serialize)    (char *dst_buf, const void *src_tlv);
  void (*fn_deserialize)  (void *dst_tlv, const char *src_buf);
  void (*fn_free)         (zl_tlv_cmn_t *tlv);
};


zl_object_t *
zl_object_new (void)
{
  zl_object_t *new_obj;

  new_obj = zl_calloc (1, sizeof(*new_obj));
  if ( unlikely(!new_obj) )
    return NULL;

  return new_obj;
}

zl_object_t *
zl_object_new_with_2_params (void *tlv,
                             void *fn_free)
{
  zl_object_t *new_obj;

  zl_ret_val_if_fail (tlv != NULL, NULL);
  zl_ret_val_if_fail (fn_free != NULL, NULL);

  new_obj = zl_object_new ();
  if ( unlikely(!new_obj) )
    return NULL;

  new_obj->tlv = tlv;
  new_obj->fn_free = fn_free;

  return new_obj;
}

zl_object_t *
zl_object_new_with_4_params (void *tlv,
                             void *fn_serialize,
                             void *fn_deserialize,
                             void *fn_free)
{
  zl_object_t *new_obj;

  zl_ret_val_if_fail (tlv != NULL, NULL);
  zl_ret_val_if_fail (fn_free != NULL, NULL);

  new_obj = zl_object_new ();
  if ( unlikely(!new_obj) )
    return NULL;

  new_obj->tlv = tlv;
  new_obj->fn_serialize = fn_serialize;
  new_obj->fn_deserialize = fn_deserialize;
  new_obj->fn_free = fn_free;

  return new_obj;
}

void
zl_object_set_fn_serialize (zl_object_t *object, void *new_fn)
{
  zl_ret_if_fail (object != NULL);
  zl_ret_if_fail (new_fn != NULL);

  object->fn_serialize = new_fn;
}

void
zl_object_set_fn_deserialize (zl_object_t *object, void *new_fn)
{
  zl_ret_if_fail (object != NULL);
  zl_ret_if_fail (new_fn != NULL);

  object->fn_deserialize = new_fn;
}

void
zl_object_set_fn_free (zl_object_t *object, void *new_fn)
{
  zl_ret_if_fail (object != NULL);
  zl_ret_if_fail (new_fn != NULL);

  object->fn_free = new_fn;
}

int
zl_object_serialize_tlv (zl_object_t *object, char *out_buf)
{
  int ret = -1;

  zl_ret_val_if_fail (object != NULL, -1);
  zl_ret_val_if_fail (out_buf != NULL, -1);

  if (object->fn_serialize)
    ret = object->fn_serialize (out_buf, object->tlv);

  return ret;
}

void
zl_object_free (zl_object_t *object)
{
  zl_ret_if_fail (object != NULL);

  object->fn_free (object->tlv);
  zl_free (object);
}
