#include <zl-mem.h>
#include <zl-log.h>

void *
zl_malloc (size_t size)
{
  return malloc (size);
}

void *
zl_calloc (size_t nmemb, size_t size)
{
  return calloc (nmemb, size);
}

void *
zl_realloc (void *ptr, size_t size)
{
  return realloc (ptr, size);
}

void
zl_free (void *ptr)
{
  if (ptr)
    free (ptr);
  else
    zl_log_warn ("Free required pointer points to NULL!");
}
