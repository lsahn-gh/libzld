/* zl-mem.h
 *
 * Copyright 2019-2023 Leesoo Ahn <lsahn@ooseel.net>
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

#ifndef __ZL_MEM_H__
#define __ZL_MEM_H__

#include <stdlib.h>

void *  zl_malloc   (size_t size);
void *  zl_calloc   (size_t nmemb, size_t size);
void *  zl_realloc  (void *ptr, size_t size);
void    zl_free     (void *ptr);
void *  zl_memcpy   (void *dest, const void *src, size_t n);
void *  zl_memdup   (void *src, size_t nbytes);

#endif
