/* main.c
 *
 * Copyright 2019-2020 Leesoo Ahn <yisooan@fedoraproject.org>
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "zl-list.h"
#include "zl-object.h"
#include "zl-tlv-type.h"
#include "zl-tlv-core.h"

const uint8_t macaddr[] = { 0xe4, 0x70, 0xb8, 0xee, 0xfa, 0x6b };

int
main (int argc,
      char *argv[])
{
  zl_list_t * lldp;
  void *ptr;
  char *str;

  lldp = zl_list_new ();

  ptr = zl_tlv_chassis_id_new (4, macaddr, sizeof(macaddr));
  zl_list_enqueue (lldp, ptr);

  str = "1/1";
  ptr = zl_tlv_port_id_new (5, GET_VOID(str), strlen(str));
  zl_list_enqueue (lldp, ptr);

  ptr = zl_tlv_ttl_new (120);
  zl_list_enqueue (lldp, ptr);

  str = "Summit300-48-Port 1001";
  ptr = zl_tlv_port_desc_new (GET_VOID(str), strlen(str) + 1/*NULL term*/);
  zl_list_enqueue (lldp, ptr);

  str = "Summit300-48";
  ptr = zl_tlv_sys_name_new (GET_VOID(str), strlen(str) + 1);
  zl_list_enqueue (lldp, ptr);

  str = "Summit300-48 - Version 7.4e.1 (Build 5) by Release_Master";
  ptr = zl_tlv_sys_desc_new (GET_VOID(str), strlen(str) + 1);
  zl_list_enqueue (lldp, ptr);

  ptr = zl_tlv_sys_capabilities_new (0x0014, 0x0014);
  zl_list_enqueue (lldp, ptr);

  uint8_t mgmt_addr[] = { 0x00, 0x01, 0x30, 0xf9, 0xad, 0xa0 };
  ptr = zl_tlv_mgmt_addr_new (7, 6, mgmt_addr, /* Management Address */
                              2, 1001, /* Interface */
                              0, NULL /* OID String */);
  zl_list_enqueue (lldp, ptr);

  ptr = zl_tlv_end_lldpdu_new ();
  zl_list_enqueue (lldp, ptr);

  return 0;
}
