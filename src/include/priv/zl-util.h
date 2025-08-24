/* zl-util.h
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

#ifndef ZL_UTIL_H
#define ZL_UTIL_H

#include "zl-compiler.h"

ZL_BEGIN_DECLS

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

/* -- Assert Macros -- */
#define zl_assert(expr) assert(expr)

/* -- Utils -- */
#define GET_VOID(ptr) ((void *)ptr)

ZL_END_DECLS

#endif /* ZL_UTIL_H */
