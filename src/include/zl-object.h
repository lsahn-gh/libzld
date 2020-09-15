/* zl-object.h
 *
 * Copyright 2019-2020 Leesoo Ahn <dev@ooseel.net>
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

#ifndef __ZL_OBJECT_H__
#define __ZL_OBJECT_H__

#include <priv/zl-macro.h>
#include <zl-tlv-common.h>

#include <zl-bind.h>

ZL_BEGIN_DECLS

typedef int (*fn_serialize_t) (char *, const void *);
typedef void (*fn_free_t) (void *);

typedef struct
{
  union {
    void *pointer;

    fn_serialize_t serialize;
    fn_free_t free;
  };
} zl_picky_t;

enum
{
  SERIALIZE_FN = 0,
  FREE_FN,
  N_FUNCTIONS,
};

/* -- Object Type -- */
typedef struct _zl_object_t zl_object_t;

#define ZL_GET_OBJECT(ptr) ((zl_object_t *)ptr)

zl_object_t * zl_object_new                 (void);
zl_object_t * zl_object_new_with_tlv_params (void *tlv,
                                             void *fn_serialize,
                                             void *fn_free);
void          zl_object_set_fn_serialize    (zl_object_t *object,
                                             void *new_fn);
void          zl_object_set_fn_free         (zl_object_t *object,
                                             void *new_fn);
int           zl_object_serialize_tlv       (zl_object_t *object,
                                             char *out_buf);
void          zl_object_free                (zl_object_t *object);

ZL_END_DECLS

#endif
