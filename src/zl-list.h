#ifndef __ZL_LIST_H__
#define __ZL_LIST_H__

#include <zl-tlv-type.h>

#include <stdio.h>

typedef struct _zl_list_t zl_list_t;
typedef struct _zl_elem_t zl_elem_t;

struct _zl_list_t
{
  size_t length;
  zl_elem_t *head;
  zl_elem_t *tail;
};

struct _zl_elem_t
{
  zl_elem_t *next;
};

zl_list_t * zl_list_new         (void);
zl_list_t * zl_list_insert_head (zl_list_t *object, zl_tlv_t *tlv);
zl_list_t * zl_list_insert_tail (zl_list_t *object, zl_tlv_t *tlv);
zl_list_t * zl_list_enqueue     (zl_list_t *object, zl_tlv_t *tlv);
zl_elem_t * zl_list_dequeue     (zl_list_t *object);
int         zl_list_is_empty    (zl_list_t *object);

#endif
