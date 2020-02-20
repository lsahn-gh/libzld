/* zl-queue.h
 *
 * Copyright 2020 Leesoo Ahn <yisooan@fedoraproject.org>
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

#ifndef __ZL_QUEUE_H__
#define __ZL_QUEUE_H__

#include "zl-dlist.h"

typedef zl_dlist_t zl_queue_t;

#define ZL_GET_QUEUE(ptr) ((zl_queue_t *)ptr)

#define ZL_QUEUE_HEAD_INIT(name) ZL_DLIST_HEAD_INIT(name)
#define ZL_QUEUE_HEAD(name) zl_queue_t name = ZL_QUEUE_HEAD_INIT(name)

static inline void zl_queue_init_head (zl_queue_t *__head)
{
  zl_dlist_init_head (ZL_GET_DLIST (__head));
}

static inline int zl_queue_empty (zl_queue_t *head)
{
  return zl_dlist_empty (ZL_GET_DLIST (head));
}

static inline int zl_queue_push (zl_queue_t *head, zl_queue_t *entry)
{
  return zl_dlist_add_tail (ZL_GET_DLIST (head), ZL_GET_DLIST (entry));
}

static inline void * zl_queue_pop (zl_queue_t *head)
{
  return zl_dlist_remove_head (ZL_GET_DLIST (head));
}

static inline void * zl_queue_peek (zl_queue_t *head)
{
  if (head == NULL)
    return NULL;
  if (zl_queue_empty (head))
    return NULL;

  return head->next;
}

#define zl_queue_foreach_safe(__head) zl_dlist_foreach_safe(ZL_GET_DLIST(__head))

#endif
