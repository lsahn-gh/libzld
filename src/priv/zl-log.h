/* zl-log.h
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

#ifndef __ZL_LOG_H__
#define __ZL_LOG_H__

#include <stdio.h>

#define ZL_INFO  "INFO"
#define ZL_DBG   "DBG"
#define ZL_WARN  "WARN"
#define ZL_ERR   "ERR"

#define zl_log_fmt(lvl, fmt, ...) fprintf(stderr, "%s():%d " lvl fmt "\n", __func__, __LINE__,  ##__VA_ARGS__)

#define zl_log_info(fmt, ...)  zl_log_fmt(ZL_INFO, fmt, ##__VA_ARGS__)
#define zl_log_dbg(fmt, ...)   zl_log_fmt(ZL_DBG, fmt, ##__VA_ARGS__)
#define zl_log_warn(fmt, ...)  zl_log_fmt(ZL_WARN, fmt, ##__VA_ARGS__)
#define zl_log_err(fmt, ...)   zl_log_fmt(ZL_ERR, fmt, ##__VA_ARGS__)

#endif
