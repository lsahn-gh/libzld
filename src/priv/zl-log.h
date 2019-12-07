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
