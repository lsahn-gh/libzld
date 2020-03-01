/* zl-tlv-dot1q-org.h
 *
 * Copyright 2020 Leesoo Ahn <yisooan@fedoraproject.org>
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

#ifndef __ZL_TLV_DOT1Q_ORG_H__
#define __ZL_TLV_DOT1Q_ORG_H__

#include <stdint.h>

#include <priv/zl-macro.h>
#include <zl-tlv-common.h>

enum
{
  DOT1Q_SUB_RESERVED0 = 0,
  DOT1Q_SUB_PORT_VLAN_ID,
  DOT1Q_SUB_VLAN_NAME,
  DOT1Q_SUB_PROTO_IDENTITY,
  DOT1Q_SUB_VID_USAGE_DIGEST,
  DOT1Q_SUB_MANAGEMENT_VID,
  DOT1Q_SUB_RESERVED7, /* Annex F of IEEE Std 802.1AX-2014 [B12] */
  DOT1Q_SUB_CONGESTION_NOTIFICATION,
  DOT1Q_SUB_ETS_CONF_TLV,
  DOT1Q_SUB_ETS_RECOMMENDATION_TLV = 0x0A,
  DOT1Q_SUB_PRIORITY_BASED_FLOW_CONTROL_CONF_TLV = 0x0B,
  DOT1Q_SUB_APPLICATION_PRIORITY_TLV = 0x0C,
  DOT1Q_SUB_EVB_TLV = 0x0D,
  DOT1Q_SUB_CDCP_TLV = 0x0E,
  DOT1Q_SUB_APPLICATION_VLAN_TLV = 0x10
};

/* -- Port VLAN ID -- */
typedef struct _zl_tlv_port_vlan_id zl_tlv_port_vlan_id_t;
typedef struct _zl_tlv_port_vlan_id zl_tlv_pvid_t; /* alias */
struct _zl_tlv_port_vlan_id
{
  zl_tlv_org_spec_t parent;

  uint16_t          identifier; /* as PVID */
} zl_1byte_pack;

/* -- Port And Protocol VLAN ID -- */
typedef struct _zl_tlv_port_proto_vlan_id zl_tlv_port_proto_vlan_id_t;
typedef struct _zl_tlv_port_proto_vlan_id zl_tlv_ppvid_t; /* alias */
struct _zl_tlv_port_proto_vlan_id
{
  zl_tlv_org_spec_t parent;

  /* .... ..X. : Port and protocol VLAN supported
   * .... .X.. : Port and protocol VLAN enabled
   * XXXX X..X : Reserved for future Std */
  uint8_t           flags;
  uint16_t          identifier; /* as PPVID */
} zl_1byte_pack;

/* -- VLAN Name -- */
typedef struct _zl_tlv_vlan_name zl_tlv_vlan_name_t;
struct _zl_tlv_vlan_name
{
  zl_tlv_org_spec_t parent;

  uint16_t          vlan_id;
  uint8_t           name_len;
  uint8_t           name[32];
} zl_1byte_pack;

/* -- Protocol Identify -- */
typedef struct _zl_tlv_proto_identity zl_tlv_proto_identity_t;
typedef struct _zl_tlv_proto_identity zl_tlv_proto_id_t; /* alias */
struct _zl_tlv_proto_identity
{
  zl_tlv_org_spec_t parent;

  uint8_t           proto_id_len;
  uint16_t          proto_identity;
} zl_1byte_pack;

/* -- VID Usage Digest -- */
typedef struct _zl_tlv_vid_usage_digest zl_tlv_vid_usage_digest_t;
struct _zl_tlv_vid_usage_digest
{
  zl_tlv_org_spec_t parent;

  uint32_t          digest;
} zl_1byte_pack;

/* -- Management VID -- */
typedef struct _zl_tlv_management_vid zl_tlv_management_vid_t;
typedef struct _zl_tlv_management_vid zl_tlv_mgmt_vid_t; /* alias */
struct _zl_tlv_management_vid
{
  zl_tlv_org_spec_t parent;

  uint16_t          vid;
} zl_1byte_pack;

/* -- Congestion Notification -- */
typedef struct _zl_tlv_congestion_notif zl_tlv_congestion_notif_t;
struct _zl_tlv_congestion_notif
{
  zl_tlv_org_spec_t parent;

  uint8_t           per_prio_cnpv_ind; /* Per-priority CNPV indicators */
  uint8_t           per_prio_ready_ind; /* Per-priority CNPV indicators */
} zl_1byte_pack;

/* -- ETS Configuration -- */
typedef struct _zl_tlv_ets_configuration zl_tlv_ets_configuration_t;
typedef struct _zl_tlv_ets_configuration zl_tlv_ets_conf_t; /* alias */
struct _zl_tlv_ets_configuration
{
  zl_tlv_org_spec_t parent;

  uint8_t           willing   : 1;
  uint8_t           cbs       : 1;
  uint8_t           reserved  : 3;
  uint8_t           max_tcs   : 3;
  uint32_t          prio_assign_tbl;
  uint64_t          tc_bandwidth_tbl;
  uint64_t          tsa_assign_tbl;
} zl_1byte_pack;

/* -- ETS Recommendation -- */
typedef struct _zl_tlv_ets_recommendation zl_tlv_ets_recommendation_t;
typedef struct _zl_tlv_ets_recommendation zl_tlv_ets_recomm_t; /* alias */
struct _zl_tlv_ets_recommendation
{
  zl_tlv_org_spec_t parent;

  uint8_t           reserved;
  uint32_t          prio_assign_tbl;
  uint64_t          tc_bandwidth_tbl;
  uint64_t          tsa_assign_tbl;
} zl_1byte_pack;

/* -- Priority-based Flow Control Configuration -- */
typedef struct _zl_tlv_prio_flow_ctrl_conf zl_tlv_prio_flow_ctrl_conf_t;
struct _zl_tlv_prio_flow_ctrl_conf
{
  zl_tlv_org_spec_t parent;

  uint8_t           willing : 1;
  uint8_t           mbc     : 1;
  uint8_t           reserved: 2;
  uint8_t           pfc_cap : 4;
  uint8_t           pfc_enable;
} zl_1byte_pack;

/* -- Application Priority -- */
typedef struct _zl_tlv_application_priority zl_tlv_application_priority_t;
typedef struct _zl_tlv_application_priority zl_tlv_app_prio_t; /* alias */
struct _zl_tlv_application_priority
{
  zl_tlv_org_spec_t parent;

  uint8_t           reserved;

  struct {
    uint8_t priority : 3;
    uint8_t reserved : 2;
    uint8_t sel      : 3;
    uint16_t proto_id;
  } prio_tbl;
} zl_1byte_pack;

/* -- EVB -- */
typedef struct _zl_tlv_evb zl_tlv_evb_t;
struct _zl_tlv_evb
{
  zl_tlv_org_spec_t parent;

  /* Refer to 802.1Q-2018 -- D.2.12 EVB TLV section */
  /* 7th octet */
  struct {
    uint8_t reserved: 5;
    uint8_t bgid    : 1;
    uint8_t rrcap   : 1;
    uint8_t rrctr   : 1;
  } br_stat;

  /* 8th octet */
  struct {
    uint8_t reserved: 4;
    uint8_t sgid    : 1;
    uint8_t rrreq   : 1;
    uint8_t rrstat  : 2;
  } sta_stat;

  /* 9th octet */
  uint8_t   r       : 3;
  uint8_t   rte     : 5;

  /* 10th octet */
  uint8_t   evb_mode: 2;
  uint8_t   rwd_rol : 1;
  uint8_t   rwd     : 5;

  /* 11th octet */
  uint8_t   reserved: 2;
  uint8_t   rka_rol : 1;
  uint8_t   rka     : 5;
} zl_1byte_pack;

/* -- CDCP -- */
typedef struct _zl_tlv_cdcp zl_tlv_cdcp_t;
struct _zl_tlv_cdcp
{
  zl_tlv_org_spec_t parent;

} zl_1byte_pack;

/* -- Application VLAN -- */
typedef struct _zl_tlv_application_vlan zl_tlv_application_vlan_t;
typedef struct _zl_tlv_application_vlan zl_tlv_app_vlan_t; /* alias */
struct _zl_tlv_application_vlan
{
  zl_tlv_org_spec_t parent;

} zl_1byte_pack;

#endif
