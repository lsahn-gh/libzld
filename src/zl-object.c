/* zl-object.c
 *
 * Copyright 2019-2025 Leesoo Ahn <lsahn@ooseel.net>
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

#include <zl-mem.h>
#include <zl-object.h>
#include <zl-dlist.h>

struct _zl_object_t
{
  zl_dlist_t      _reserved;

  zl_tlv_cmn_t    *tlv;
  fn_serialize_t  serialize;
  fn_free_t       free;
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
zl_object_new_with_tlv_params (void *tlv,
                               void *fn_serialize,
                               void *fn_free)
{
  zl_object_t *new_obj;
  zl_picky_t picky;

  zl_ret_val_if_fail (tlv != NULL, NULL);
  zl_ret_val_if_fail (fn_free != NULL, NULL);

  new_obj = zl_object_new ();
  if ( unlikely(!new_obj) )
    return NULL;

  new_obj->tlv = tlv;

  picky.pointer = fn_serialize;
  new_obj->serialize = picky.serialize;

  picky.pointer = fn_free;
  new_obj->free = picky.free;

  return new_obj;
}

void
zl_object_set_fn_serialize (zl_object_t *object, void *new_fn)
{
  zl_picky_t picky;

  zl_ret_if_fail (object != NULL);
  zl_ret_if_fail (new_fn != NULL);

  picky.pointer = new_fn;
  object->serialize = picky.serialize;
}

void
zl_object_set_fn_free (zl_object_t *object, void *new_fn)
{
  zl_picky_t picky;

  zl_ret_if_fail (object != NULL);
  zl_ret_if_fail (new_fn != NULL);

  picky.pointer = new_fn;
  object->free = picky.free;
}

int
zl_object_serialize_tlv (zl_object_t *object, char *out_buf)
{
  int ret = 0;

  zl_ret_val_if_fail (object != NULL, 0);
  zl_ret_val_if_fail (out_buf != NULL, 0);

  if (object->serialize)
    ret = object->serialize (out_buf, object->tlv);

  return ret;
}

void
zl_object_free (zl_object_t *object)
{
  zl_ret_if_fail (object != NULL);

  if (object->free)
    object->free (object->tlv);
  zl_free (object);
}
