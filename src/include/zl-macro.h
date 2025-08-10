/* zl-macro.h
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

#ifndef __ZL_MACRO_H__
#define __ZL_MACRO_H__

#include <assert.h>

#define zl_ret_if(expr) \
  do { \
    if ((expr)) { \
      return; \
    } \
  } while(0)

#define zl_ret_val_if(expr, val) \
  do { \
    if ((expr)) { \
      return val; \
    } \
  } while(0)

#define zl_ret_if_fail(expr) \
  do { \
    if (!(expr)) { \
      return; \
    } \
  } while(0)

#define zl_ret_val_if_fail(expr, val) \
  do { \
    if (!(expr)) { \
      return val; \
    } \
  } while(0)


#if defined(__GNUC__)

#define __always_inline__   static __attribute__((always_inline))
#define __pack__            __attribute__((aligned(1), packed))
#define __used__            __attribute__((used))
#define __unused__          __attribute__((unused))

#define likely(x)           __builtin_expect((x),1)
#define unlikely(x)         __builtin_expect((x),0)

/* deprecated */
#define zl_nbyte_pack(n)    __attribute__((aligned(n), packed))
#define zl_1byte_pack       zl_nbyte_pack(1)

#else /* !defined(__GNUC__) */

#define __always_inline__   static
#define __pack__
#define __used__
#define __unused__

#define likely(x)           x
#define unlikely(x)         x

/* deprecated */
#define zl_nbyte_pack(n)
#define zl_1byte_pack

#endif /* defined(__GNUC__) */


/* -- Assert Macros -- */
#define zl_assert(expr) assert(expr)


/* -- Utils -- */
#define GET_VOID(ptr) ((void *)str)


#endif
