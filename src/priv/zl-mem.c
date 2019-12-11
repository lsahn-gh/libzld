#include <string.h>

#include <zl-mem.h>
#include <zl-log.h>
#include <zl-macro.h>

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
  zl_ret_if_param (ptr == NULL);

  free (ptr);
}

void *
zl_memcpy (void *dest, const void *src, size_t n)
{
  zl_ret_val_if_param (dest == NULL, NULL);
  zl_ret_val_if_param (src == NULL, NULL);
  zl_ret_val_if_param (n == 0, NULL);

  return memcpy (dest, src, n);
}

void *
zl_memdup (void *src, size_t nbytes)
{
  void *new_elem;

  zl_ret_val_if_param (src == NULL, NULL);
  zl_ret_val_if_param (nbytes == 0, NULL);

  new_elem = zl_calloc (1, nbytes);
  zl_ret_val_if (new_elem == NULL, NULL);

  zl_memcpy (new_elem, src, nbytes);

  return new_elem;
}
