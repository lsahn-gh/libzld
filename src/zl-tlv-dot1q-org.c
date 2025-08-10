/** zl-tlv-dot1q-org.c
 *
 * Copyright 2025 Leesoo Ahn <lsahn@ooseel.net>
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

#include <priv/zl-mem.h>
#include <zl-object.h>
#include <zl-tlv-dot1q-org.h>

/* -- Port VLAN ID -- */
int
zl_dot1q_port_vlan_id_serialize (char *dst_buf,
                                 const void *src_tlv)
{
  int size;
  zl_tlv_cmn_t *common;
  zl_tlv_chassis_id_t *obj,
                      ibuf;

  zl_ret_val_if_fail (dst_buf != NULL, 0);
  zl_ret_val_if_fail (src_tlv != NULL, 0);

  zl_memcpy (&ibuf, src_tlv, sizeof(ibuf));

  common = (zl_tlv_cmn_t *)&ibuf;
  obj = (zl_tlv_chassis_id_t *)&ibuf;

  size = sizeof(*common) + common->length;

  zl_tlv_common_serialize (common);

  zl_memcpy (dst_buf, obj, size);

  return size;
}

void
zl_tlv_chassis_id_free (void *tlv)
{
  zl_tlv_chassis_id_t *obj;

  zl_ret_if_fail (tlv != NULL);

  obj = (zl_tlv_chassis_id_t *)tlv;

  zl_free (obj);
}

zl_object_t *
zl_tlv_1q_port_vlan_id_new (const uint16_t identifier)
{
  zl_object_t *object = NULL;
  zl_tlv_cmn_t *common = NULL;
  zl_tlv_org_spec_t *org = NULL;
  zl_tlv_port_vlan_id_t *new_tlv = NULL;
  zl_picky_t picky[N_FUNCTIONS];

  new_tlv = zl_calloc (1, sizeof(*new_tlv));
  if ( unlikely(!new_tlv) )
    goto error;

  zl_tlv_common_init (ZL_GET_TLV_COMMON_OBJ (new_tlv),
                      TLV_ORG_SPECIFIC,
                      6);

  zl_tlv_org_spec_init (ZL_TLV_ORG_SPEC_OBJ (new_tlv),
                        TLV_1Q_PORT_VLAN_ID);

  new_tlv->identifier = identifier;

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
