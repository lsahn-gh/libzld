#ifndef __ZL_MACRO_H__
#define __ZL_MACRO_H__

#include <assert.h>

#include <zl-log.h>

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


/* -- Platform Dependency Macros -- */
#define zl_nbyte_pack(n) __attribute((aligned(n), packed))
#define zl_1byte_pack zl_nbyte_pack(1)

#define likely(x)    __builtin_expect((x),1)
#define unlikely(x)  __builtin_expect((x),0)


/* -- Assert Macros -- */
#define zl_assert(expr) assert(expr)

#endif
