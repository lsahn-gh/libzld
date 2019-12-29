/* zl-tlv-common.h
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

#ifndef __ZL_TLV_COMMON_H__
#define __ZL_TLV_COMMON_H__

#include <stdint.h>

#include <priv/zl-macro.h>
#include <zl-object.h>

enum
{
  /* -- Mandatory TLVs -- */
  TLV_END_OF_LLDPDU = 0,
  TLV_CHASSIS_ID,
  TLV_PORT_ID,
  TLV_TIME_TO_LIVE,

  /* -- Basic TLVs -- */
  TLV_PORT_DESCRIPTION = 4,
  TLV_SYSTEM_NAME,
  TLV_SYSTEM_DESCRIPTION,
  TLV_SYSTEM_CAPABILITIES,
  TLV_MANAGEMENT_ADDRESS,

  /* Elements between 9 and 126 are reserved */

  /* -- Organizationally Specific TLV -- */
  TLV_ORG_SPECIFIC = 127
};

/* -- Common Type -- */
typedef struct _zl_tlv_cmn_t zl_tlv_cmn_t;
struct _zl_tlv_cmn_t
{
  uint8_t    type : 7;
  uint16_t   length : 9;
} zl_1byte_pack;

#define GET_TLV_COMMON_INSTANCE(tlv) (zl_tlv_cmn_t *)tlv

/* -- Organizationally Specific TLV Type -- */
typedef struct _zl_tlv_org_t zl_tlv_org_t;
struct _zl_tlv_org_t
{
  zl_tlv_cmn_t  parent;

  uint8_t       oui[3];
  uint8_t       subtype;
} zl_1byte_pack;

#endif
