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

#include <priv/zl-mem.h>

#include <zl-dlist.h>
#include <zl-object.h>
#include <zl-tlv-header.h>

struct _zl_object_t
{
  zl_dlist_t      _reserved;

  zl_tlv_hdr_t    *tlv;
  fn_serialize_t  serialize;
  fn_free_t       free;
};

zl_object_t * zl_object_new (void)
{
  zl_object_t *new_obj;

  new_obj = zl_calloc (1, sizeof(*new_obj));
  if ( unlikely(!new_obj) )
    return NULL;

  return new_obj;
}

zl_object_t * zl_object_new_with_tlv_params (void *tlv,
                                             fn_serialize_t serialize,
                                             fn_free_t free)
{
  zl_object_t *new_obj;

  zl_ret_val_if_fail (tlv != NULL, NULL);
  zl_ret_val_if_fail (serialize != NULL, NULL);
  zl_ret_val_if_fail (free != NULL, NULL);

  new_obj = zl_object_new ();
  if ( unlikely(!new_obj) )
    return NULL;

  new_obj->tlv = tlv;
  new_obj->serialize = serialize;
  new_obj->free = free;

  return new_obj;
}

void zl_object_set_serialize (zl_object_t *self,
                              fn_serialize_t new_serialize)
{
  zl_ret_if_fail (self != NULL);
  zl_ret_if_fail (new_serialize != NULL);

  self->serialize = new_serialize;
}

void zl_object_set_free (zl_object_t *self,
                         fn_free_t new_free)
{
  zl_ret_if_fail (self != NULL);
  zl_ret_if_fail (new_free != NULL);

  self->free = new_free;
}

int zl_object_serialize_tlv (zl_object_t *self,
                             char *out_buf)
{
  int ret = 0;

  zl_ret_val_if_fail (self != NULL, 0);
  zl_ret_val_if_fail (out_buf != NULL, 0);

  if (self->serialize)
    ret = self->serialize (out_buf, self->tlv);

  return ret;
}

void zl_object_free (zl_object_t *self)
{
  zl_ret_if_fail (self != NULL);

  if (self->free)
    self->free (self->tlv);
  zl_free (self);
}
