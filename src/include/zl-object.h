/* zl-object.h
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

#ifndef ZL_OBJECT_H
#define ZL_OBJECT_H

#include "priv/zl-compiler.h"

ZL_BEGIN_DECLS

#include "priv/zl-util.h"

/**
 * @brief Function pointer type for TLV serialization.
 */
typedef int   (*fn_serialize_t) (char * dest_buf, const void * src_tlv);

/**
 * @brief Function pointer type for TLV cleanup.
 */
typedef void  (*fn_free_t)      (void * tlv);

typedef struct {
  union {
    void * out;

    fn_serialize_t serialize;
    fn_free_t free;
  };
} zl_box_t;

enum
{
  SERIALIZE_FN = 0,
  FREE_FN,
  N_FUNCTIONS,
};

/**
 * @brief Encapsulates a TLV object and its associated serialization
 * and cleanup functions.
 */
typedef struct _zl_object_t zl_object_t;

/**
 * @brief Casts a generic pointer to a zl_object_t pointer.
 *
 * @param obj Pointer to an object (const void *).
 * @return zl_object_t* Converted object pointer.
 */
__forceinline__
zl_object_t * ZL_OBJECT_TYPE (const void *obj)
{
  return (zl_object_t *)obj;
}

/**
 * @brief Allocates a new zl_object_t object.
 *
 * @return zl_object_t* object pointer.
 */
zl_object_t * zl_object_new (void);

/**
 * @brief Allocates a new zl_object_t object with parameters.
 *
 * @param tlv Pointer to a TLV object (void *).
 * @param serialize Pointer to a serialize function.
 * @param free Pointer to a free function.
 * @return zl_object_t* object pointer.
 */
zl_object_t * zl_object_new_with_tlv_params (void *tlv,
                                             fn_serialize_t serialize,
                                             fn_free_t free);

/**
 * @brief Sets a new serialize function to a zl_object_t object.
 *
 * @param self Pointer to the object.
 * @param new_serialize Pointer to a new serialize function.
 */
void zl_object_set_serialize (zl_object_t *self,
                              fn_serialize_t new_serialize);

/**
 * @brief Sets a new free function to a zl_object_t object.
 *
 * @param self Pointer to the object.
 * @param new_free Pointer to a new free function.
 */
void zl_object_set_free (zl_object_t *self,
                         fn_free_t new_free);

/**
 * @brief Serializes a TLV object to a buffer.
 *
 * @param self Pointer to the object.
 * @param out_buf Pointer to the buffer.
 * @return int Written bytes to the buffer.
 */
int zl_object_serialize_tlv (zl_object_t *self,
                             char *out_buf);

/**
 * @brief Frees a TLV and zl_object_t object itself.
 *
 * @param self Pointer to the object.
 */
void zl_object_free (zl_object_t *self);

ZL_END_DECLS

#endif /* ZL_OBJECT_H */
