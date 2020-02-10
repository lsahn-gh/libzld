/* zl-list.h
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

#ifndef __ZL_LIST_H__
#define __ZL_LIST_H__

#include <stdio.h>

#include <zl-tlv-type.h>

typedef struct _zl_list_t zl_list_t;
typedef struct _zl_elem_t zl_elem_t;

struct _zl_list_t
{
  size_t    length;
  zl_elem_t *head;
  zl_elem_t *tail;
};

struct _zl_elem_t
{
  zl_elem_t *next;
  void      *payload;
};

zl_list_t * zl_list_new         (void);
zl_list_t * zl_list_insert_head (zl_list_t *object, void *tlv);
zl_list_t * zl_list_insert_tail (zl_list_t *object, void *tlv);
zl_list_t * zl_list_enqueue     (zl_list_t *object, void *tlv);
zl_elem_t * zl_list_dequeue     (zl_list_t *object);
int         zl_list_is_empty    (zl_list_t *object);
size_t      zl_list_length      (zl_list_t *object);

#endif
