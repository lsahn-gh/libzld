/* zl-tlv-core.h
 *
 * Copyright 2019 Leesoo Ahn <yisooan@fedoraproject.org>
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

#ifndef __ZL_TLV_CORE_H__
#define __ZL_TLV_CORE_H__

#include <stdint.h>

#include <priv/zl-macro.h>
#include <zl-tlv-common.h>

/* -- End Of LLDPDU (Mandatory) -- */
typedef zl_tlv_cmn_t zl_tlv_end_lldpdu_t;

/* -- Chassis ID (Mandatory) -- */
typedef struct _zl_tlv_chassis_id_t zl_tlv_chassis_id_t;
struct _zl_tlv_chassis_id_t
{
  zl_tlv_cmn_t  parent;

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
} zl_1byte_pack;

/* -- Port ID (Mandatory) -- */
typedef struct _zl_tlv_port_id_t zl_tlv_port_id_t;
struct _zl_tlv_port_id_t
{
  zl_tlv_cmn_t  parent;

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
} zl_1byte_pack;

/* -- Time To Live (Mandatory) -- */
typedef struct _zl_tlv_ttl_t zl_tlv_ttl_t;
struct _zl_tlv_ttl_t
{
  zl_tlv_cmn_t  parent;

  uint16_t      value;
} zl_1byte_pack;

/* -- Port Description (Optional) -- */
typedef struct _zl_tlv_port_desc_t zl_tlv_port_desc_t;
struct _zl_tlv_port_desc_t
{
  zl_tlv_cmn_t  parent;

  uint8_t       value[256];
} zl_1byte_pack;

/* -- System Name (Optional) -- */
typedef struct _zl_tlv_sys_name_t zl_tlv_sys_name_t;
struct _zl_tlv_sys_name_t
{
  zl_tlv_cmn_t  parent;

  uint8_t       value[256];
} zl_1byte_pack;

/* -- System Description (Optional) -- */
typedef struct _zl_tlv_sys_desc_t zl_tlv_sys_desc_t;
struct _zl_tlv_sys_desc_t
{
  zl_tlv_cmn_t  parent;

  uint8_t       value[256];
} zl_1byte_pack;

/* -- System Capabilities (Optional) -- */
typedef struct _zl_tlv_sys_cap_t zl_tlv_sys_cap_t;
struct _zl_tlv_sys_cap_t
{
  zl_tlv_cmn_t  parent;

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
} zl_1byte_pack;

/* -- Management Address (Optional) -- */
typedef struct _zl_tlv_mgmt_addr_t zl_tlv_mgmt_addr_t;
struct _zl_tlv_mgmt_addr_t
{
  zl_tlv_cmn_t  parent;

  uint8_t       addr_len;
  /* Management Address String */
  uint8_t       addr_subtype;
  uint8_t       addr_value[31];

  uint8_t       iface_subtype;
  uint32_t      iface_number;

  uint8_t       oid_len;
  uint8_t       oid_value[128];
} zl_1byte_pack;

zl_object_t * zl_tlv_end_lldpdu_new       (void);
zl_object_t * zl_tlv_chassis_id_new       (uint8_t subtype,
                                           const uint8_t *src,
                                           const size_t nbytes);
zl_object_t * zl_tlv_port_id_new          (uint8_t subtype,
                                           const uint8_t *src,
                                           const size_t nbytes);
zl_object_t * zl_tlv_ttl_new              (uint16_t src);
zl_object_t * zl_tlv_port_desc_new        (const uint8_t *src,
                                           const size_t nbytes);
zl_object_t * zl_tlv_sys_name_new         (const uint8_t *src,
                                           const size_t nbytes);
zl_object_t * zl_tlv_sys_desc_new         (const uint8_t *src,
                                           const size_t nbytes);
zl_object_t * zl_tlv_sys_capabilities_new (uint16_t sys_caps,
                                           uint16_t enabled_caps);
zl_object_t * zl_tlv_mgmt_addr_new        (uint8_t mgmt_addr_len,
                                           uint8_t mgmt_addr_subtype,
                                           uint8_t *mgmt_addr_val,
                                           uint8_t iface_subtype,
                                           uint32_t iface_number,
                                           uint8_t oid_str_len,
                                           uint8_t *oid_str_val);

#endif
