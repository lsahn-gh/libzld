/* zl-tlv-dot1ab.h
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

#ifndef ZL_TLV_DOT1AB_H
#define ZL_TLV_DOT1AB_H

#include "priv/zl-compiler.h"

ZL_BEGIN_DECLS

#include "priv/zl-util.h"

#include "zl-tlv-header.h"

#include <stdint.h>

/**
 * @brief Represents an End of LLDPDU TLV payload.
 */
typedef struct __packed__
{
  zl_tlv_hdr_t  header;
} zl_tlv_end_lldpdu_t;

/**
 * @brief Casts a generic pointer to a zl_tlv_end_lldpdu_t pointer.
 *
 * @param obj Pointer to an object (const void *).
 * @return zl_tlv_end_lldpdu_t* Converted End of LLDPDU TLV pointer.
 */
__forceinline__
zl_tlv_end_lldpdu_t * ZL_TLV_END_LLDPDU_TYPE (const void *obj)
{
  return (zl_tlv_end_lldpdu_t *)obj;
}

/**
 * @brief Allocates a new End of LLDPDU TLV object.
 *
 * @return zl_object_t* object pointer.
 */
zl_object_t * zl_tlv_end_lldpdu_new (void);

/* -- Chassis ID (Mandatory) -- */
/**
 * @brief Represents a Chassis ID TLV payload.
 */
typedef struct __packed__
{
  zl_tlv_hdr_t  header;

  /* 0: Reserved
   * 1: Chassis component
   * 2: Interface alias
   * 3: Port component
   * 4: MAC address
   * 5: Network address
   * 6: Interface name
   * 7: Locally assigned
   * 8-255: Reserved
   */
  uint8_t       subtype;
  uint8_t       value[256];
} zl_tlv_chassis_id_t;

/**
 * @brief Casts a generic pointer to a zl_tlv_chassis_id_t pointer.
 *
 * @param obj Pointer to an object (const void *).
 * @return zl_tlv_chassis_id_t* Converted Chassis ID TLV pointer.
 */
__forceinline__
zl_tlv_chassis_id_t * ZL_TLV_CHASSIS_ID_TYPE (const void *obj)
{
  return (zl_tlv_chassis_id_t *)obj;
}

/**
 * @brief Allocates a new Chassis ID TLV object.
 *
 * @param subtype Chassis ID subtype.
 * @param src Pointer to the Chassis ID value.
 * @param nbytes Length of the Chassis ID value in bytes.
 * @return zl_object_t* object pointer.
 */
zl_object_t * zl_tlv_chassis_id_new (uint8_t subtype,
                                     const uint8_t *src,
                                     const size_t nbytes);

/* -- Port ID (Mandatory) -- */
/**
 * @brief Represents a Port ID TLV payload.
 */
typedef struct __packed__
{
  zl_tlv_hdr_t  header;

  /* 0: Reserved
   * 1: Interface alias
   * 2: Port component
   * 3: MAC address
   * 4: Network address
   * 5: Interface name
   * 6: Agent circuit ID
   * 7: Locally assigned
   * 8-255: Reserved
   */
  uint8_t       subtype;
  uint8_t       value[256];
} zl_tlv_port_id_t;

/**
 * @brief Casts a generic pointer to a zl_tlv_port_id_t pointer.
 *
 * @param obj Pointer to an object (const void *).
 * @return zl_tlv_port_id_t* Converted Port ID TLV pointer.
 */
__forceinline__
zl_tlv_port_id_t * ZL_TLV_PORT_ID_TYPE (const void *obj)
{
  return (zl_tlv_port_id_t *)obj;
}

/**
 * @brief Allocates a new Port ID TLV object.
 *
 * @param subtype Port ID subtype.
 * @param src Pointer to the Port ID value.
 * @param nbytes Length of the Port ID value in bytes.
 * @return zl_object_t* object pointer.
 */
zl_object_t * zl_tlv_port_id_new (uint8_t subtype,
                                  const uint8_t *src,
                                  const size_t nbytes);

/* -- Time To Live (Mandatory) -- */
/**
 * @brief Represents a Time To Live TLV payload.
 */
typedef struct __packed__
{
  zl_tlv_hdr_t  header;

  uint16_t      value;
} zl_tlv_ttl_t;

/**
 * @brief Casts a generic pointer to a zl_tlv_ttl_t pointer.
 *
 * @param obj Pointer to an object (const void *).
 * @return zl_tlv_ttl_t* Converted Time To Live TLV pointer.
 */
__forceinline__
zl_tlv_ttl_t * ZL_TLV_TTL_TYPE (const void *obj)
{
  return (zl_tlv_ttl_t *)obj;
}

/**
 * @brief Allocates a new Time To Live TLV object.
 *
 * @param src Time To Live value in hops.
 * @return zl_object_t* object pointer.
 */
zl_object_t * zl_tlv_ttl_new (uint16_t src);

/* -- Port Description (Optional) -- */
/**
 * @brief Represents a Port Description TLV payload.
 */
typedef struct __packed__
{
  zl_tlv_hdr_t  header;

  uint8_t       value[256];
} zl_tlv_port_desc_t;

/**
 * @brief Casts a generic pointer to a zl_tlv_port_desc_t pointer.
 *
 * @param obj Pointer to an object (const void *).
 * @return zl_tlv_port_desc_t* Converted Port Description TLV pointer.
 */
__forceinline__
zl_tlv_port_desc_t * ZL_TLV_PORT_DESC_TYPE (const void *obj)
{
  return (zl_tlv_port_desc_t *)obj;
}

/**
 * @brief Allocates a new Port Description TLV object.
 *
 * @param src Pointer to the Port Description value.
 * @param nbytes Length of the Port Description value in bytes.
 * @return zl_object_t* object pointer.
 */
zl_object_t * zl_tlv_port_desc_new (const uint8_t *src,
                                    const size_t nbytes);

/* -- System Name (Optional) -- */
/**
 * @brief Represents a System Name TLV payload.
 */
typedef struct __packed__
{
  zl_tlv_hdr_t  header;

  uint8_t       value[256];
} zl_tlv_sys_name_t;

/**
 * @brief Casts a generic pointer to a zl_tlv_sys_name_t pointer.
 *
 * @param obj Pointer to an object (const void *).
 * @return zl_tlv_sys_name_t* Converted System Name TLV pointer.
 */
__forceinline__
zl_tlv_sys_name_t * ZL_TLV_SYS_NAME_TYPE (const void *obj)
{
  return (zl_tlv_sys_name_t *)obj;
}

/**
 * @brief Allocates a new System Name TLV object.
 *
 * @param src Pointer to the System Name value.
 * @param nbytes Length of the System Name value in bytes.
 * @return zl_object_t* object pointer.
 */
zl_object_t * zl_tlv_sys_name_new (const uint8_t *src,
                                   const size_t nbytes);

/* -- System Description (Optional) -- */
/**
 * @brief Represents a System Description TLV payload.
 */
typedef struct __packed__
{
  zl_tlv_hdr_t  header;

  uint8_t       value[256];
} zl_tlv_sys_desc_t;

/**
 * @brief Casts a generic pointer to a zl_tlv_sys_desc_t pointer.
 *
 * @param obj Pointer to an object (const void *).
 * @return zl_tlv_sys_desc_t* Converted System Description TLV pointer.
 */
__forceinline__
zl_tlv_sys_desc_t * ZL_TLV_SYS_DESC_TYPE (const void *obj)
{
  return (zl_tlv_sys_desc_t *)obj;
}

/**
 * @brief Allocates a new System Description TLV object.
 *
 * @param src Pointer to the System Description value.
 * @param nbytes Length of the System Description value in bytes.
 * @return zl_object_t* object pointer.
 */
zl_object_t * zl_tlv_sys_desc_new (const uint8_t *src,
                                   const size_t nbytes);

/* -- System Capabilities (Optional) -- */
/**
 * @brief Represents a System Capabilities TLV payload.
 */
typedef struct __packed__
{
  zl_tlv_hdr_t  header;

  /* .... .... .... ...X : Other
   * .... .... .... ..X. : Repeater
   * .... .... .... .X.. : Bridge
   * .... .... .... X... : WLAN Access Point
   * .... .... ...X .... : Router
   * .... .... ..X. .... : Telephone
   * .... .... .X.. .... : DOCSIS cable device
   * .... .... X... .... : Station Only
   * XXXX XXXX .... .... : Reserved */
  uint16_t      sys_caps;
  /* Functionalities of each bits are the same as system capabilities */
  uint16_t      enabled_caps;
} zl_tlv_sys_cap_t;

/**
 * @brief Casts a generic pointer to a zl_tlv_sys_cap_t pointer.
 *
 * @param obj Pointer to an object (const void *).
 * @return zl_tlv_sys_cap_t* Converted System Capabilities TLV pointer.
 */
__forceinline__
zl_tlv_sys_cap_t * ZL_TLV_SYS_CAP_TYPE (const void *obj)
{
  return (zl_tlv_sys_cap_t *)obj;
}

/**
 * @brief Allocates a new System Capabilities TLV object.
 *
 * @param sys_caps System Capabilities value.
 * @param enabled_caps Enabled Capabilities value.
 * @return zl_object_t* object pointer.
 */
zl_object_t * zl_tlv_sys_caps_new (uint16_t sys_caps,
                                   uint16_t enabled_caps);

/* -- Management Address (Optional) -- */
/**
 * @brief Represents a Management Address TLV payload.
 */
typedef struct __packed__
{
  zl_tlv_hdr_t  header;

  uint8_t       addr_len;
  /* Management Address String */
  uint8_t       addr_subtype;
  uint8_t       addr_value[31];

  uint8_t       iface_subtype;
  uint32_t      iface_number;

  uint8_t       oid_len;
  uint8_t       oid_value[128];
} zl_tlv_mgmt_addr_t;

/**
 * @brief Casts a generic pointer to a zl_tlv_mgmt_addr_t pointer.
 *
 * @param obj Pointer to an object (const void *).
 * @return zl_tlv_mgmt_addr_t* Converted Management Address TLV pointer.
 */
__forceinline__
zl_tlv_mgmt_addr_t * ZL_TLV_MGMT_ADDR_TYPE (const void *obj)
{
  return (zl_tlv_mgmt_addr_t *)obj;
}

/**
 * @brief Allocates a new Management Address TLV object.
 *
 * @param mgmt_addr_len Length of the Management Address value in bytes.
 * @param mgmt_addr_subtype Management Address subtype.
 * @param mgmt_addr_val Pointer to the Management Address value.
 * @param iface_subtype Interface Numbering subtype.
 * @param iface_number Interface Number.
 * @param oid_str_len Length of the OID String value in bytes.
 * @param oid_str_val Pointer to the OID String value.
 * @return zl_object_t* object pointer.
 */
zl_object_t * zl_tlv_mgmt_addr_new (uint8_t mgmt_addr_len,
                                    uint8_t mgmt_addr_subtype,
                                    uint8_t *mgmt_addr_val,
                                    uint8_t iface_subtype,
                                    uint32_t iface_number,
                                    uint8_t oid_str_len,
                                    uint8_t *oid_str_val);

ZL_END_DECLS

#endif /* ZL_TLV_DOT1AB_H */
