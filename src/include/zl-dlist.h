/* zl-dlist.h
 *
 * Copyright 2019-2020 Leesoo Ahn <yisooan@fedoraproject.org>
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
/* This is based on list.h of Linux Kernel */

#ifndef __ZL_DLIST_H__
#define __ZL_DLIST_H__

#include <stdlib.h>
#include <stdint.h>

typedef struct _zl_dlist_t zl_dlist_t;
struct _zl_dlist_t {
  struct _zl_dlist_t *prev, *next;
};

#define ZL_GET_DLIST(ptr)  ((zl_dlist_t *)ptr)

#define ZL_DLIST_HEAD_INIT(name) { &(name), &(name) }
#define ZL_DLIST_HEAD(name) zl_dlist_t name = ZL_DLIST_HEAD_INIT(name)

static inline void zl_dlist_init_head (zl_dlist_t *__head)
{
  if (__head == NULL)
    return;

  __head->next = __head;
  __head->prev = __head;
}

static inline int zl_dlist_empty (zl_dlist_t *head)
{
  if (head == NULL)
    return 1;

  return head->next == head;
}

static inline int __zl_list_add (zl_dlist_t *__new,
                                 zl_dlist_t *prev,
                                 zl_dlist_t *next)
{
  if (__new == NULL)
    return -1;

  __new->next = next;
  __new->prev = prev;
  prev->next = __new;
  next->prev = __new;

  return 0;
}

static inline int zl_dlist_add_head (zl_dlist_t *__head, zl_dlist_t *entry)
{
  if (__head == NULL || entry == NULL)
    return -1;

  return __zl_list_add(entry, __head, __head->next);
}

static inline int zl_dlist_add_tail (zl_dlist_t *__head, zl_dlist_t *entry)
{
  if (__head == NULL || entry == NULL)
    return -1;

  return __zl_list_add(entry, __head->prev, __head);
}

static inline int zl_dlist_enqueue (zl_dlist_t *__head, zl_dlist_t *entry)
{
  return zl_dlist_add_tail (__head, entry);
}

static inline int __zl_list_del (zl_dlist_t *entry)
{
  if (entry == NULL)
    return -1;

  entry->prev->next = entry->next;
  entry->next->prev = entry->prev;

  return 0;
}

static inline int zl_dlist_remove (zl_dlist_t *entry)
{
  if (entry == NULL)
    return -1;

  return __zl_list_del(entry);
}

static inline void * zl_dlist_remove_head (zl_dlist_t *head)
{
  void * ret = NULL;

  if (head == NULL)
    return ret;
  if (zl_dlist_empty (head))
    return ret;

  ret = head->next;
  __zl_list_del (head->next);

  return ret;
}

static inline void * zl_dlist_dequeue (zl_dlist_t *head)
{
  return zl_dlist_remove_head (head);
}

static inline void * zl_dlist_remove_tail (zl_dlist_t *head)
{
  void * ret = NULL;

  if (head == NULL)
    return ret;
  if (zl_dlist_empty (head))
    return ret;

  ret = head->prev;
  __zl_list_del (head->prev);

  return ret;
}

static inline void * zl_dlist_peek (zl_dlist_t *head)
{
  if (head == NULL)
    return NULL;
  if (zl_dlist_empty (head))
    return NULL;

  return head->next;
}

#define zl_dlist_foreach(pos, head) \
  for (pos = (head)->next; pos != (head); pos = pos->next)

#define zl_dlist_foreach_safe(pos, n, head) \
  for (pos = (head)->next, n = pos->next; pos != (head); pos = n, n = pos->next)

#endif
