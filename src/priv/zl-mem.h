#ifndef __ZL_MEM_H__
#define __ZL_MEM_H__

#include <stdlib.h>

void *  zl_malloc    (size_t size);
void *  zl_calloc    (size_t nmemb, size_t size); 
void *  zl_realloc   (void *ptr, size_t size); 
void    zl_free      (void *ptr);

#endif
