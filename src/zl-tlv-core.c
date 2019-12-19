/* zl-tlv-core.c
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

#include <string.h>

#include <priv/zl-mem.h>
#include <zl-tlv-core.h>

zl_tlv_end_lldpdu_t *
zl_tlv_end_lldpdu_new (void)
{
  zl_tlv_cmn_t *common;
  zl_tlv_end_lldpdu_t *new_tlv;

  new_tlv = zl_calloc (1, sizeof(*new_tlv));
  zl_ret_val_if (new_tlv == NULL, NULL);

  common = (zl_tlv_cmn_t *)new_tlv;
  common->type = TLV_END_OF_LLDPDU;
  common->length = 0;

  return new_tlv;
}

void
zl_tlv_end_lldpdu_free (zl_tlv_end_lldpdu_t *tlv)
{
  zl_ret_if_fail (tlv != NULL);

  zl_free (tlv);
}

zl_tlv_chassis_id_t *
zl_tlv_chassis_id_new (uint8_t subtype, uint8_t *src, size_t nbytes)
{
  zl_tlv_cmn_t *common;
  zl_tlv_chassis_id_t *new_tlv;

  zl_ret_val_if_fail (src != NULL, NULL);
  zl_ret_val_if_fail (0 < nbytes && nbytes < 256, NULL);

  new_tlv = zl_calloc (1, sizeof(*new_tlv));
  zl_ret_val_if (new_tlv == NULL, NULL);

  common = (zl_tlv_cmn_t *)new_tlv;
  common->type = TLV_CHASSIS_ID;
  common->length = 1 + nbytes;

  new_tlv->subtype = subtype;
  new_tlv->value = zl_memdup (src, nbytes);

  return new_tlv;
}

void
zl_tlv_chassis_id_free (zl_tlv_chassis_id_t *tlv)
{
  zl_ret_if_fail (tlv != NULL);

  if (tlv->value)
    zl_free (tlv->value);

  zl_free (tlv);
}

zl_tlv_port_id_t *
zl_tlv_port_id_new (uint8_t subtype, uint8_t *src, size_t nbytes)
{
  zl_tlv_cmn_t *common;
  zl_tlv_port_id_t *new_tlv;

  zl_ret_val_if_fail (src != NULL, NULL);
  zl_ret_val_if_fail (0 < nbytes && nbytes < 256, NULL);

  new_tlv = zl_calloc (1, sizeof(*new_tlv));
  zl_ret_val_if (new_tlv == NULL, NULL);

  common = (zl_tlv_cmn_t *)new_tlv;
  common->type = TLV_PORT_ID;
  common->length = 1 + nbytes;

  new_tlv->subtype = subtype;
  new_tlv->value = zl_memdup (src, nbytes);

  return new_tlv;
}

void
zl_tlv_port_id_free (zl_tlv_port_id_t *tlv)
{
  zl_ret_if_fail (tlv != NULL);

  if (tlv->value)
    zl_free (tlv->value);

  zl_free (tlv);
}

zl_tlv_ttl_t *
zl_tlv_ttl_new (uint16_t src)
{
  zl_tlv_cmn_t *common;
  zl_tlv_ttl_t *new_tlv;

  new_tlv = zl_calloc (1, sizeof(*new_tlv));
  zl_ret_val_if (new_tlv == NULL, NULL);

  common = (zl_tlv_cmn_t *)new_tlv;
  common->type = TLV_TIME_TO_LIVE;
  common->length = 2;

  new_tlv->value = src;

  return new_tlv;
}

void
zl_tlv_ttl_free (zl_tlv_ttl_t *tlv)
{
  zl_ret_if_fail (tlv != NULL);

  zl_free (tlv);
}

zl_tlv_port_desc_t *
zl_tlv_port_desc_new (uint8_t *src, size_t nbytes)
{
  zl_tlv_cmn_t *common;
  zl_tlv_port_desc_t *new_tlv;

  zl_ret_val_if_fail (src != NULL, NULL);
  zl_ret_val_if_fail (0 < nbytes && nbytes < 256, NULL);

  new_tlv = zl_calloc (1, sizeof(*new_tlv));
  zl_ret_val_if (new_tlv == NULL, NULL);

  common = (zl_tlv_cmn_t *)new_tlv;
  common->type = TLV_PORT_DESCRIPTION;
  common->length = nbytes;

  new_tlv->value = zl_memdup (src, nbytes);

  return new_tlv;
}

void
zl_tlv_port_desc_free (zl_tlv_port_desc_t *tlv)
{
  zl_ret_if_fail (tlv != NULL);

  if (tlv->value)
    zl_free (tlv->value);

  zl_free (tlv);
}

zl_tlv_sys_name_t *
zl_tlv_sys_name_new (uint8_t *src, size_t nbytes)
{
  zl_tlv_cmn_t *common;
  zl_tlv_sys_name_t *new_tlv;

  zl_ret_val_if_fail (src != NULL, NULL);
  zl_ret_val_if_fail (0 < nbytes && nbytes < 256, NULL);

  new_tlv = zl_calloc (1, sizeof(*new_tlv));
  zl_ret_val_if (new_tlv == NULL, NULL);

  common = (zl_tlv_cmn_t *)new_tlv;
  common->type = TLV_SYSTEM_NAME;
  common->length = nbytes;

  new_tlv->value = zl_memdup (src, nbytes);

  return new_tlv;
}

void
zl_tlv_sys_name_free (zl_tlv_sys_name_t *tlv)
{
  zl_ret_if_fail (tlv != NULL);

  if (tlv->value)
    zl_free (tlv->value);

  zl_free (tlv);
}

zl_tlv_sys_desc_t *
zl_tlv_sys_desc_new (uint8_t *src, size_t nbytes)
{
  zl_tlv_cmn_t *common;
  zl_tlv_sys_desc_t *new_tlv;

  zl_ret_val_if_fail (src != NULL, NULL);
  zl_ret_val_if_fail (0 < nbytes && nbytes < 256, NULL);

  new_tlv = zl_calloc (1, sizeof(*new_tlv));
  zl_ret_val_if (new_tlv == NULL, NULL);

  common = (zl_tlv_cmn_t *)new_tlv;
  common->type = TLV_SYSTEM_DESCRIPTION;
  common->length = nbytes;

  new_tlv->value = zl_memdup (src, nbytes);

  return new_tlv;
}

void
zl_tlv_sys_desc_free (zl_tlv_sys_desc_t *tlv)
{
  zl_ret_if_fail (tlv != NULL);

  if (tlv->value)
    zl_free (tlv->value);

  zl_free (tlv);
}

zl_tlv_sys_cap_t *
zl_tlv_sys_capabilities_new (uint16_t sys_caps, uint16_t enabled_caps)
{
  zl_tlv_cmn_t *common;
  zl_tlv_sys_cap_t *new_tlv;

  new_tlv = zl_calloc (1, sizeof(*new_tlv));
  zl_ret_val_if (new_tlv == NULL, NULL);

  common = (zl_tlv_cmn_t *)new_tlv;
  common->type = TLV_SYSTEM_CAPABILITIES;
  common->length = 4;

  new_tlv->sys_caps = sys_caps;
  new_tlv->enabled_caps = enabled_caps;

  return new_tlv;
}

void
zl_tlv_sys_capabilities_free (zl_tlv_sys_cap_t *tlv)
{
  zl_ret_if_fail (tlv != NULL);

  zl_free (tlv);
}

zl_tlv_mgmt_addr_t *
zl_tlv_mgmt_addr_new (uint8_t mgmt_addr_len,
                      uint8_t mgmt_addr_subtype,
                      uint8_t *mgmt_addr_val,
                      uint8_t iface_subtype,
                      uint32_t iface_number,
                      uint8_t oid_str_len,
                      uint8_t *oid_str_val)
{
  zl_tlv_cmn_t *common;
  zl_tlv_mgmt_addr_t *new_tlv;

  zl_ret_val_if_fail (mgmt_addr_val != NULL, NULL);
  zl_ret_val_if_fail (oid_str_val != NULL, NULL);
  zl_ret_val_if_fail (1 < mgmt_addr_len && mgmt_addr_len < 33, NULL);
  zl_ret_val_if_fail (oid_str_len < 129, NULL);

  new_tlv = zl_calloc (1, sizeof(*new_tlv));
  zl_ret_val_if (new_tlv == NULL, NULL);

  common = (zl_tlv_cmn_t *)new_tlv;
  common->type = TLV_MANAGEMENT_ADDRESS;
  common->length = (1 + mgmt_addr_len + 1 + 4 + 1 + oid_str_len);

  new_tlv->addr_len = mgmt_addr_len;
  new_tlv->addr_subtype = mgmt_addr_subtype;
  new_tlv->addr_value = zl_memdup (mgmt_addr_val, mgmt_addr_len - 1 /* Size of subtype */);
  new_tlv->iface_subtype = iface_subtype;
  new_tlv->iface_number = iface_number;
  new_tlv->oid_len = oid_str_len;
  new_tlv->oid_value = zl_memdup (oid_str_val, oid_str_len);

  return new_tlv;
}

void
zl_tlv_mgmt_addr_free (zl_tlv_mgmt_addr_t *tlv)
{
  zl_ret_if_fail (tlv != NULL);

  if (tlv->addr_value)
    zl_free (tlv->addr_value);

  if (tlv->oid_value)
    zl_free (tlv->oid_value);

  zl_free (tlv);
}
