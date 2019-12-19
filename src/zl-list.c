/* zl-list.c
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

#include <priv/zl-macro.h>
#include <priv/zl-mem.h>

#include <zl-list.h>

/* -- Public APIs -- */
zl_list_t *
zl_list_new (void)
{
  void * new_list;

  new_list = zl_calloc (1, sizeof(zl_list_t));
  zl_ret_val_if (new_list == NULL, NULL);

  return new_list;
}

zl_list_t *
zl_list_insert_head (zl_list_t *object, void *tlv)
{
  zl_list_t *self;
  zl_elem_t *elem;

  zl_ret_val_if_fail (object != NULL, NULL);
  zl_ret_val_if_fail (tlv != NULL, NULL);

  self = object;
  elem = (zl_elem_t *)tlv;

  if (self->length == 0) {
    elem->next = elem;
    self->head = elem;
    self->tail = elem;
  } else {
    elem->next = self->head;
    self->head = elem;
  }

  self->length += 1;

  return self;
}

zl_list_t *
zl_list_insert_tail (zl_list_t *object, void *tlv)
{
  zl_list_t *self;
  zl_elem_t *elem;

  zl_ret_val_if_fail (object != NULL, NULL);
  zl_ret_val_if_fail (tlv != NULL, NULL);

  self = object;
  elem = (zl_elem_t *)tlv;

  if (self->length == 0) {
    elem->next = elem;
    self->head = elem;
    self->tail = elem;
  } else {
    elem->next = NULL;
    self->tail->next = elem;
    self->tail = elem;
  }

  self->length += 1;

  return self;
}

zl_list_t *
zl_list_enqueue (zl_list_t *object, void *tlv)
{
  zl_ret_val_if_fail (object != NULL, NULL);
  zl_ret_val_if_fail (tlv != NULL, NULL);

  return zl_list_insert_tail (object, tlv);
}

zl_elem_t *
zl_list_dequeue (zl_list_t *object)
{
  zl_list_t *self;
  zl_elem_t *elem = NULL;

  zl_ret_val_if_fail (object != NULL, NULL);

  self = object;

  if (self->length) {
    elem = self->head;
    self->head = self->head->next;

    self->length -= 1;
  }

  return elem;
}

int
zl_list_is_empty (zl_list_t *object)
{
  zl_list_t *self;

  zl_ret_val_if_fail (object != NULL, 0);

  return self->length == 0;
}
