/* zl-tlv-core.c
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

#include <string.h>
#include <arpa/inet.h>

#include <zl-mem.h>
#include <zl-object.h>
#include <zl-tlv-dot1ab.h>

/* -- Common Serializer -- */
static int
tlv_serialize_ng (char *dst_buf,
                  const void *src_tlv)
{
  int size;
  static char stack[512]; /* internal buffer */
  zl_tlv_cmn_t *common;

  zl_ret_val_if_fail (dst_buf != NULL, 0);
  zl_ret_val_if_fail (src_tlv != NULL, 0);

  common = ZL_GET_TLV_COMMON_OBJ(src_tlv);
  size = sizeof(*common) + common->length;

  zl_memcpy (stack, src_tlv, size);

  common = ZL_GET_TLV_COMMON_OBJ(stack);
  zl_tlv_common_serialize (common);

  zl_memcpy (dst_buf, stack, size);

  return size;
}

static void
tlv_free_ng (void *tlv)
{
  zl_ret_if_fail (tlv != NULL);

  zl_free (tlv);
}

/* -- End Of LLDPDU -- */
static inline int
zl_tlv_end_lldpdu_serialize (char *dst_buf,
                             const void *src_tlv)
{
  return tlv_serialize_ng (dst_buf, src_tlv);
}

static inline void
zl_tlv_end_lldpdu_free (void *tlv)
{
  tlv_free_ng (tlv);
}

zl_object_t *
zl_tlv_end_lldpdu_new (void)
{
  zl_object_t *object = NULL;
  zl_tlv_cmn_t *common = NULL;
  zl_tlv_end_lldpdu_t *new_tlv = NULL;
  zl_picky_t picky[N_FUNCTIONS];

  new_tlv = zl_calloc (1, sizeof(*new_tlv));
  if ( unlikely(!new_tlv) )
    goto error;

  common = (zl_tlv_cmn_t *)new_tlv;
  common->type = TLV_END_OF_LLDPDU;
  common->length = 0;

  picky[SERIALIZE_FN].serialize = zl_tlv_end_lldpdu_serialize;
  picky[FREE_FN].free = zl_tlv_end_lldpdu_free;

  object = zl_object_new_with_tlv_params (common,
                                          picky[SERIALIZE_FN].pointer,
                                          picky[FREE_FN].pointer);
  if ( likely(object != NULL) )
    return object;

  zl_free (new_tlv);

error:
  return NULL;
}


/* -- Chassis ID -- */
static inline int
zl_tlv_chassis_id_serialize (char *dst_buf,
                             const void *src_tlv)
{
  return tlv_serialize_ng (dst_buf, src_tlv);
}

static inline void
zl_tlv_chassis_id_free (void *tlv)
{
  tlv_free_ng (tlv);
}

zl_object_t *
zl_tlv_chassis_id_new (uint8_t subtype,
                       const uint8_t *src,
                       const size_t nbytes)
{
  zl_object_t *object = NULL;
  zl_tlv_cmn_t *common = NULL;
  zl_tlv_chassis_id_t *new_tlv = NULL;
  zl_picky_t picky[N_FUNCTIONS];

  zl_ret_val_if_fail (src != NULL, NULL);
  zl_ret_val_if_fail (0 < nbytes && nbytes < 256, NULL);

  new_tlv = zl_calloc (1, sizeof(*new_tlv));
  if ( unlikely(!new_tlv) )
    goto error;

  common = (zl_tlv_cmn_t *)new_tlv;
  common->type = TLV_CHASSIS_ID;
  common->length = 1 + nbytes;

  new_tlv->subtype = subtype;
  zl_memcpy (new_tlv->value, src, nbytes);

  picky[SERIALIZE_FN].serialize = zl_tlv_chassis_id_serialize;
  picky[FREE_FN].free = zl_tlv_chassis_id_free;

  object = zl_object_new_with_tlv_params (common,
                                          picky[SERIALIZE_FN].pointer,
                                          picky[FREE_FN].pointer);
  if ( likely(object != NULL) )
    return object;

  zl_free (new_tlv);

error:
  return NULL;
}


/* -- Port ID -- */
static inline int
zl_tlv_port_id_serialize (char *dst_buf,
                          const void *src_tlv)
{
  return tlv_serialize_ng (dst_buf, src_tlv);
}

static inline void
zl_tlv_port_id_free (void *tlv)
{
  tlv_free_ng (tlv);
}

zl_object_t *
zl_tlv_port_id_new (uint8_t subtype,
                    const uint8_t *src,
                    const size_t nbytes)
{
  zl_object_t *object = NULL;
  zl_tlv_cmn_t *common = NULL;
  zl_tlv_port_id_t *new_tlv = NULL;
  zl_picky_t picky[N_FUNCTIONS];

  zl_ret_val_if_fail (src != NULL, NULL);
  zl_ret_val_if_fail (0 < nbytes && nbytes < 256, NULL);

  new_tlv = zl_calloc (1, sizeof(*new_tlv));
  if ( unlikely(!new_tlv) )
    goto error;

  common = (zl_tlv_cmn_t *)new_tlv;
  common->type = TLV_PORT_ID;
  common->length = 1 + nbytes;

  new_tlv->subtype = subtype;
  zl_memcpy (new_tlv->value, src, nbytes);

  picky[SERIALIZE_FN].serialize = zl_tlv_port_id_serialize;
  picky[FREE_FN].free = zl_tlv_port_id_free;

  object = zl_object_new_with_tlv_params (common,
                                          picky[SERIALIZE_FN].pointer,
                                          picky[FREE_FN].pointer);
  if ( likely(object != NULL) )
    return object;

  zl_free (new_tlv);

error:
  return NULL;
}


/* -- Time To Live -- */
static int
zl_tlv_ttl_serialize (char *dst_buf,
                      const void *src_tlv)
{
  int size;
  zl_tlv_cmn_t *common;
  zl_tlv_ttl_t *obj,
               ibuf;

  zl_ret_val_if_fail (dst_buf != NULL, 0);
  zl_ret_val_if_fail (src_tlv != NULL, 0);

  zl_memcpy (&ibuf, src_tlv, sizeof(ibuf));

  common = (zl_tlv_cmn_t *)&ibuf;
  obj = (zl_tlv_ttl_t *)&ibuf;

  size = sizeof(*common) + common->length;

  zl_tlv_common_serialize (common);

  obj->value = htons (obj->value);

  zl_memcpy (dst_buf, obj, size);

  return size;
}

static inline void
zl_tlv_ttl_free (void *tlv)
{
  tlv_free_ng (tlv);
}

zl_object_t *
zl_tlv_ttl_new (const uint16_t src)
{
  zl_object_t *object = NULL;
  zl_tlv_cmn_t *common = NULL;
  zl_tlv_ttl_t *new_tlv = NULL;
  zl_picky_t picky[N_FUNCTIONS];

  new_tlv = zl_calloc (1, sizeof(*new_tlv));
  if ( unlikely(!new_tlv) )
    goto error;

  common = (zl_tlv_cmn_t *)new_tlv;
  common->type = TLV_TIME_TO_LIVE;
  common->length = 2;

  new_tlv->value = src;

  picky[SERIALIZE_FN].serialize = zl_tlv_ttl_serialize;
  picky[FREE_FN].free = zl_tlv_ttl_free;

  object = zl_object_new_with_tlv_params (common,
                                          picky[SERIALIZE_FN].pointer,
                                          picky[FREE_FN].pointer);
  if ( likely(object != NULL) )
    return object;

  zl_free (new_tlv);

error:
  return NULL;
}


/* -- Port Description -- */
static inline int
zl_tlv_port_desc_serialize (char *dst_buf,
                            const void *src_tlv)
{
  return tlv_serialize_ng (dst_buf, src_tlv);
}

static inline void
zl_tlv_port_desc_free (void *tlv)
{
  tlv_free_ng (tlv);
}

zl_object_t *
zl_tlv_port_desc_new (const uint8_t *src,
                      const size_t nbytes)
{
  zl_object_t *object = NULL;
  zl_tlv_cmn_t *common = NULL;
  zl_tlv_port_desc_t *new_tlv = NULL;
  zl_picky_t picky[N_FUNCTIONS];

  zl_ret_val_if_fail (src != NULL, NULL);
  zl_ret_val_if_fail (0 < nbytes && nbytes < 256, NULL);

  new_tlv = zl_calloc (1, sizeof(*new_tlv));
  if ( unlikely(!new_tlv) )
    goto error;

  common = (zl_tlv_cmn_t *)new_tlv;
  common->type = TLV_PORT_DESCRIPTION;
  common->length = nbytes;

  zl_memcpy (new_tlv->value, src, nbytes);

  picky[SERIALIZE_FN].serialize = zl_tlv_port_desc_serialize;
  picky[FREE_FN].free = zl_tlv_port_desc_free;

  object = zl_object_new_with_tlv_params (common,
                                          picky[SERIALIZE_FN].pointer,
                                          picky[FREE_FN].pointer);
  if ( likely(object != NULL) )
    return object;

  zl_free (new_tlv);

error:
  return NULL;
}


/* -- System Name -- */
static inline int
zl_tlv_sys_name_serialize (char *dst_buf,
                           const void *src_tlv)
{
  return tlv_serialize_ng (dst_buf, src_tlv);
}

static inline void
zl_tlv_sys_name_free (void *tlv)
{
  tlv_free_ng (tlv);
}

zl_object_t *
zl_tlv_sys_name_new (const uint8_t *src,
                     const size_t nbytes)
{
  zl_object_t *object = NULL;
  zl_tlv_cmn_t *common = NULL;
  zl_tlv_sys_name_t *new_tlv = NULL;
  zl_picky_t picky[N_FUNCTIONS];

  zl_ret_val_if_fail (src != NULL, NULL);
  zl_ret_val_if_fail (0 < nbytes && nbytes < 256, NULL);

  new_tlv = zl_calloc (1, sizeof(*new_tlv));
  if ( unlikely(!new_tlv) )
    goto error;

  common = (zl_tlv_cmn_t *)new_tlv;
  common->type = TLV_SYSTEM_NAME;
  common->length = nbytes;

  zl_memcpy (new_tlv->value, src, nbytes);

  picky[SERIALIZE_FN].serialize = zl_tlv_sys_name_serialize;
  picky[FREE_FN].free = zl_tlv_sys_name_free;

  object = zl_object_new_with_tlv_params (common,
                                          picky[SERIALIZE_FN].pointer,
                                          picky[FREE_FN].pointer);
  if ( likely(object != NULL) )
    return object;

  zl_free (new_tlv);

error:
  return NULL;
}


/* -- System Description -- */
static inline int
zl_tlv_sys_desc_serialize (char *dst_buf,
                           const void *src_tlv)
{
  return tlv_serialize_ng (dst_buf, src_tlv);
}

static inline void
zl_tlv_sys_desc_free (void *tlv)
{
  tlv_free_ng (tlv);
}

zl_object_t *
zl_tlv_sys_desc_new (const uint8_t *src,
                     const size_t nbytes)
{
  zl_object_t *object = NULL;
  zl_tlv_cmn_t *common = NULL;
  zl_tlv_sys_desc_t *new_tlv = NULL;
  zl_picky_t picky[N_FUNCTIONS];

  zl_ret_val_if_fail (src != NULL, NULL);
  zl_ret_val_if_fail (0 < nbytes && nbytes < 256, NULL);

  new_tlv = zl_calloc (1, sizeof(*new_tlv));
  if ( unlikely(!new_tlv) )
    goto error;

  common = (zl_tlv_cmn_t *)new_tlv;
  common->type = TLV_SYSTEM_DESCRIPTION;
  common->length = nbytes;

  zl_memcpy (new_tlv->value, src, nbytes);

  picky[SERIALIZE_FN].serialize = zl_tlv_sys_desc_serialize;
  picky[FREE_FN].free = zl_tlv_sys_desc_free;

  object = zl_object_new_with_tlv_params (common,
                                          picky[SERIALIZE_FN].pointer,
                                          picky[FREE_FN].pointer);
  if ( likely(object != NULL) )
    return object;

  zl_free (new_tlv);

error:
  return NULL;
}


/* -- System Capabilities -- */
static int
zl_tlv_sys_capabilities_serialize (char *dst_buf,
                                   const void *src_tlv)
{
  int size;
  uint16_t sys_val,
           enabled_val;
  zl_tlv_cmn_t *common;
  zl_tlv_sys_cap_t *obj,
                   ibuf;

  zl_ret_val_if_fail (dst_buf != NULL, 0);
  zl_ret_val_if_fail (src_tlv != NULL, 0);

  zl_memcpy (&ibuf, src_tlv, sizeof(ibuf));

  common = (zl_tlv_cmn_t *)&ibuf;
  obj = (zl_tlv_sys_cap_t *)&ibuf;

  size = sizeof(*common) + common->length;

  zl_tlv_common_serialize (common);

  sys_val = obj->sys_caps;
  enabled_val = obj->enabled_caps;

  obj->sys_caps = htons (sys_val);
  obj->enabled_caps = htons (enabled_val);
  zl_memcpy (dst_buf, obj, size);

  return size;
}

static inline void
zl_tlv_sys_capabilities_free (void *tlv)
{
  tlv_free_ng (tlv);
}

zl_object_t *
zl_tlv_sys_capabilities_new (uint16_t sys_caps,
                             uint16_t enabled_caps)
{
  zl_object_t *object = NULL;
  zl_tlv_cmn_t *common = NULL;
  zl_tlv_sys_cap_t *new_tlv = NULL;
  zl_picky_t picky[N_FUNCTIONS];

  new_tlv = zl_calloc (1, sizeof(*new_tlv));
  if ( unlikely(!new_tlv) )
    goto error;

  common = (zl_tlv_cmn_t *)new_tlv;
  common->type = TLV_SYSTEM_CAPABILITIES;
  common->length = 4;

  new_tlv->sys_caps = sys_caps;
  new_tlv->enabled_caps = enabled_caps;

  picky[SERIALIZE_FN].serialize = zl_tlv_sys_capabilities_serialize;
  picky[FREE_FN].free = zl_tlv_sys_capabilities_free;

  object = zl_object_new_with_tlv_params (common,
                                          picky[SERIALIZE_FN].pointer,
                                          picky[FREE_FN].pointer);
  if ( likely(object != NULL) )
    return object;

  zl_free (new_tlv);

error:
  return NULL;
}


/* -- Management Address -- */
static int
zl_tlv_mgmt_addr_serialize (char *dst_buf,
                            const void *src_tlv)
{
  int size;
  zl_tlv_cmn_t *common;
  zl_tlv_mgmt_addr_t *obj,
                     ibuf;
  /* Cal variables */
  uint8_t buf[256] = { 0, };
  size_t len = 0,
         cal_size = 0;

  zl_ret_val_if_fail (dst_buf != NULL, 0);
  zl_ret_val_if_fail (src_tlv != NULL, 0);

  zl_memcpy (&ibuf, src_tlv, sizeof(ibuf));

  common = (zl_tlv_cmn_t *)&ibuf;
  obj = (zl_tlv_mgmt_addr_t *)&ibuf;

  size = sizeof(*common) + common->length;

  zl_tlv_common_serialize (common);

  /* TLV header */
  len = size;
  /* Management Address String Length */
  len += sizeof(obj->addr_len);
  /* Management Address String */
  len += obj->addr_len;
  zl_memcpy (buf, obj, len);

  /* Interface Numbering Subtype */
  cal_size = sizeof(obj->iface_subtype);
  *(uint8_t *)(buf+len) = obj->iface_subtype;
  len += cal_size;
  /* Interface Number */
  cal_size = sizeof(obj->iface_number);
  *(uint32_t *)(buf+len) = htonl (obj->iface_number);
  len += cal_size;

  /* OID String Length */
  cal_size = sizeof(obj->oid_len);
  *(uint8_t *)(buf+len) = obj->oid_len;
  len += cal_size;
  /* Object Identifier */
  zl_memcpy (buf+len, obj->oid_value, obj->oid_len);
  len += obj->oid_len;

  zl_memcpy (dst_buf, buf, len);

  return len;
}

static inline void
zl_tlv_mgmt_addr_free (void *tlv)
{
  tlv_free_ng (tlv);
}

zl_object_t *
zl_tlv_mgmt_addr_new (uint8_t mgmt_addr_len,
                      uint8_t mgmt_addr_subtype,
                      uint8_t *mgmt_addr_val,
                      uint8_t iface_subtype,
                      uint32_t iface_number,
                      uint8_t oid_str_len,
                      uint8_t *oid_str_val)
{
  zl_object_t *object = NULL;
  zl_tlv_cmn_t *common = NULL;
  zl_tlv_mgmt_addr_t *new_tlv = NULL;
  zl_picky_t picky[N_FUNCTIONS];

  zl_ret_val_if_fail (mgmt_addr_val != NULL, NULL);
  zl_ret_val_if_fail (1 <= mgmt_addr_len && mgmt_addr_len <= 32, NULL);
  zl_ret_val_if_fail (oid_str_len <= 128, NULL);

  new_tlv = zl_calloc (1, sizeof(*new_tlv));
  if ( unlikely(!new_tlv) )
    goto error;

  common = (zl_tlv_cmn_t *)new_tlv;
  common->type = TLV_MANAGEMENT_ADDRESS;
  common->length = (1 + mgmt_addr_len + 1 + 4 + 1 + oid_str_len);

  new_tlv->addr_len = mgmt_addr_len;
  new_tlv->addr_subtype = mgmt_addr_subtype;
  zl_memcpy (new_tlv->addr_value, mgmt_addr_val, mgmt_addr_len - 1 /* Size of subtype */);

  new_tlv->iface_subtype = iface_subtype;
  new_tlv->iface_number = iface_number;
  new_tlv->oid_len = oid_str_len;
  zl_memcpy (new_tlv->oid_value, oid_str_val, oid_str_len);

  picky[SERIALIZE_FN].serialize = zl_tlv_mgmt_addr_serialize;
  picky[FREE_FN].free = zl_tlv_mgmt_addr_free;

  object = zl_object_new_with_tlv_params (common,
                                          picky[SERIALIZE_FN].pointer,
                                          picky[FREE_FN].pointer);
  if ( likely(object != NULL) )
    return object;

  zl_free (new_tlv);

error:
  return NULL;
}
