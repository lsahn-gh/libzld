/* zl-dlist.h
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
/* This is based on list.h of Linux Kernel */

#ifndef ZL_DLIST_H
#define ZL_DLIST_H

#include "priv/zl-compiler.h"

ZL_BEGIN_DECLS

#include "priv/zl-util.h"

/**
 * @brief Represents a node in a doubly linked list.
 */
typedef struct _zl_dlist_t {
  struct _zl_dlist_t *prev;
  struct _zl_dlist_t *next;
} zl_dlist_t;

/**
 * @brief Casts a generic pointer to a zl_dlist_t pointer.
 *
 * @param obj Pointer to an object (const void *).
 * @return zl_dlist_t* Converted object pointer.
 */
__forceinline__ zl_dlist_t * ZL_DLIST_TYPE (const void *obj) {
  return (zl_dlist_t *)obj;
}

/**
 * @brief Static initializer for doubly-linked list head.
 */
#define ZL_DLIST_HEAD_INIT(name) { &(name), &(name) }

/**
 * @brief Defines and initializes a doubly linked list head.
 */
#define ZL_DLIST_HEAD(name) zl_dlist_t name = ZL_DLIST_HEAD_INIT(name)

/**
 * @brief Initializes a doubly linked list.
 *
 * @param self Pointer to the head of the list.
 */
__forceinline__ void zl_dlist_init_head (zl_dlist_t * self)
{
  if (self == NULL)
    return;

  self->next = self;
  self->prev = self;
}

/**
 * @brief Verifies if a doubly linked list is empty.
 *
 * @param self Pointer to the head of the list.
 * @return 1 if the list is empty, 0 otherwise.
 */
__forceinline__ int zl_dlist_empty (zl_dlist_t * self)
{
  if (self == NULL)
    return 1;

  return self->next == self;
}

__forceinline__ int __zl_list_add (zl_dlist_t *__new,
                                   zl_dlist_t *prev,
                                   zl_dlist_t *next)
{
  __new->next = next;
  __new->prev = prev;
  prev->next = __new;
  next->prev = __new;

  return 0;
}

/**
 * @brief Adds an element to the head of a doubly linked list.
 *
 * @param self Pointer to the head of the list.
 * @param entry Pointer to a new element.
 * @return -1 if an error occurs, 0 otherwise.
 */
__forceinline__ int zl_dlist_add_head (zl_dlist_t * self,
                                       zl_dlist_t * entry)
{
  if (self == NULL || entry == NULL)
    return -1;

  return __zl_list_add(entry, self, self->next);
}

/**
 * @brief Adds an element to the tail of a doubly linked list.
 *
 * @param self Pointer to the head of the list.
 * @param entry Pointer to a new element.
 * @return -1 if an error occurs, 0 otherwise.
 */
__forceinline__ int zl_dlist_add_tail (zl_dlist_t * self,
                                       zl_dlist_t * entry)
{
  if (self == NULL || entry == NULL)
    return -1;

  return __zl_list_add(entry, self->prev, self);
}

/**
 * @brief Enqueues an element to the tail of a queue.
 *
 * @param self Pointer to the head of the queue.
 * @param entry Pointer to a new element.
 * @return -1 if an error occurs, 0 otherwise.
 */
__forceinline__ int zl_dlist_enqueue (zl_dlist_t * self,
                                      zl_dlist_t * entry)
{
  return zl_dlist_add_tail (self, entry);
}

__forceinline__ int __zl_list_del (zl_dlist_t * entry)
{
  entry->prev->next = entry->next;
  entry->next->prev = entry->prev;

  return 0;
}

/**
 * @brief Detaches an element from a doubly linked list.
 *
 * @param entry Pointer to the element.
 * @return -1 if an error occurs, 0 otherwise.
 */
__forceinline__ int zl_dlist_detach (zl_dlist_t * entry)
{
  if (entry == NULL)
    return -1;

  return __zl_list_del(entry);
}

/**
 * @brief Removes an element from the head of a doubly linked list.
 *
 * @param self Pointer to the head of the list.
 * @return The element on success, or NULL on error.
 */
__forceinline__ void * zl_dlist_remove_head (zl_dlist_t * self)
{
  void * ret = NULL;

  if (self == NULL)
    return ret;
  if (zl_dlist_empty (self))
    return ret;

  ret = self->next;
  __barrier__();
  __zl_list_del (self->next);

  return ret;
}

/**
 * @brief Removes an element from the tail of a doubly linked list.
 *
 * @param self Pointer to the head of the list.
 * @return The element on success, or NULL on error.
 */
__forceinline__ void * zl_dlist_remove_tail (zl_dlist_t * self)
{
  void * ret = NULL;

  if (self == NULL)
    return ret;
  if (zl_dlist_empty (self))
    return ret;

  ret = self->prev;
  __barrier__();
  __zl_list_del (self->prev);

  return ret;
}

/**
 * @brief Dequeues an element from the head of a queue.
 *
 * @param self Pointer to the head of the queue.
 * @return The element on success, or NULL on error.
 */
__forceinline__ void * zl_dlist_dequeue (zl_dlist_t * self)
{
  return zl_dlist_remove_head (self);
}

/**
 * @brief References the first element of a doubly linked list.
 *
 * @param self Pointer to the head of the list.
 * @return The element on success, or NULL on error.
 */
__forceinline__ void * zl_dlist_peek (zl_dlist_t * self)
{
  if (self == NULL)
    return NULL;
  if (zl_dlist_empty (self))
    return NULL;

  return self->next;
}

/**
 * @brief Iterates a doubly linked list (unsafe).
 *
 * Note. DO NOT delete elements in the block of the foreach due to
 * it iterates unsafely, a fault occurs otherwise.
 *
 * @param pos Variable holding the current element.
 * @param head Pointer to the list.
 */
#define zl_dlist_foreach(pos, head) \
  for (pos = (head)->next;          \
       pos != (head);               \
       pos = pos->next)

/**
 * @brief Iterates a doubly linked list (safe).
 *
 * Note. It's safe to delete elements in the block of the foreach
 * while iterating.
 *
 * @param pos Variable holding the current element.
 * @param n Variable holding the next element.
 * @param head Pointer to the list.
 */
#define zl_dlist_foreach_safe(pos, n, head)   \
  for (pos = (head)->next, n = pos->next;     \
       pos != (head);                         \
       pos = n, n = pos->next)

ZL_END_DECLS

#endif /* ZL_DLIST_H */
