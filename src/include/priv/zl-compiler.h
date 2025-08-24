/* zl-compiler.h
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

/**
 * @brief A set of compiler depended macros.
 *
 * Note. Please DO NOT define language depended macros, or wrap them up.
 */

#ifndef ZL_COMPILER_H
#define ZL_COMPILER_H

#if defined(__cplusplus)
# define ZL_BEGIN_DECLS     extern "C" {
# define ZL_END_DECLS       }
#else /* !__cplusplus */
# define ZL_BEGIN_DECLS
# define ZL_END_DECLS
#endif /* __cplusplus */

#if defined(__GNUC__)

#if defined(__cplusplus)
# define __forceinline__    inline __attribute__((always_inline))
#else /* !__cplusplus */
# define __forceinline__    static inline __attribute__((always_inline))
#endif /* __cplusplus */

#define __packed__          __attribute__((aligned(1), packed))
#define __barrier__()       __asm__ volatile("" ::: "memory")

#define likely(x)           __builtin_expect((x),1)
#define unlikely(x)         __builtin_expect((x),0)

#else /* !defined(__GNUC__) */

#if defined(__cplusplus)
# define __forceinline__    inline
#else /* !__cplusplus */
# define __forceinline__    static inline
#endif /* __cplusplus */

#define __packed__
#define __barrier__()

#define likely(x)           (x)
#define unlikely(x)         (x)

#endif /* defined(__GNUC__) */

#endif /* ZL_COMPILER_H */
