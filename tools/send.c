/* send.c
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
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <linux/if_ether.h>

#include <zl-dlist.h>
#include <zl-object.h>
#include <zl-tlv-type.h>

#define ETH_P_LLDP  0x88CC

const uint8_t broadcast_addr[] = { 0x01, 0x80, 0xc2, 0x00, 0x00, 0x0e };
const uint8_t macaddr[] = { 0xe4, 0x70, 0xb8, 0xee, 0xfa, 0x6b };
char *iface;

#define BUFSZ 1500

static int
send_packet (char *buf, int size)
{
  struct sockaddr addr;
  int sock,
      ret;

  sock = socket (AF_PACKET, SOCK_PACKET, htons(ETH_P_LLDP));
  if (sock == -1) {
    fprintf(stderr, "Error on newing socket\n");
    return EXIT_FAILURE;
  }

  memset (&addr, 0, sizeof(struct sockaddr));
  memcpy (addr.sa_data, iface, sizeof(addr.sa_data));

  ret = sendto (sock, buf, size, 0, &addr, sizeof(addr));
  if (ret == -1) {
    fprintf (stderr, "Error on sending eth frame\n");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

int
main (int argc,
      char *argv[])
{
  uint8_t buf[BUFSZ] = { 0, };
  zl_dlist_t lldp = ZL_DLIST_HEAD_INIT(lldp),
             *cursor = NULL,
             *n = NULL;
  void *ptr = NULL;
  char *str = NULL;
  int size = 0;

  if (argc != 2) {
    fprintf (stderr, "Usage: %s <interface>\n", argv[0]);
    return EXIT_FAILURE;
  }

  iface = argv[1];

  {
    /* Init ether hdr */
    struct ethhdr hdr;

    hdr.h_proto = htons(ETH_P_LLDP);
    memcpy (hdr.h_dest, broadcast_addr, ETH_ALEN);
    memcpy (hdr.h_source, macaddr, ETH_ALEN);

    memcpy (buf, &hdr, sizeof(hdr));
    size += sizeof(hdr);
  }

  ptr = zl_tlv_chassis_id_new (4, macaddr, sizeof(macaddr));
  zl_dlist_enqueue (&lldp, ptr);

  str = "1/1";
  ptr = zl_tlv_port_id_new (5, GET_VOID(str), strlen(str));
  zl_dlist_enqueue (&lldp, ptr);

  ptr = zl_tlv_ttl_new (120);
  zl_dlist_enqueue (&lldp, ptr);

  str = "Summit300-48-Port 1001";
  ptr = zl_tlv_port_desc_new (GET_VOID(str), strlen(str) + 1/*NULL term*/);
  zl_dlist_enqueue (&lldp, ptr);

  str = "Summit300-48";
  ptr = zl_tlv_sys_name_new (GET_VOID(str), strlen(str) + 1);
  zl_dlist_enqueue (&lldp, ptr);

  str = "Summit300-48 - Version 7.4e.1 (Build 5) by Release_Master";
  ptr = zl_tlv_sys_desc_new (GET_VOID(str), strlen(str) + 1);
  zl_dlist_enqueue (&lldp, ptr);

  ptr = zl_tlv_sys_capabilities_new (0x0014, 0x0014);
  zl_dlist_enqueue (&lldp, ptr);

  uint8_t mgmt_addr[] = { 0x00, 0x01, 0x30, 0xf9, 0xad, 0xa0 };
  ptr = zl_tlv_mgmt_addr_new (7, 6, mgmt_addr, /* Management Address */
                              2, 1001, /* Interface */
                              0, NULL /* OID String */);
  zl_dlist_enqueue (&lldp, ptr);

  ptr = zl_tlv_end_lldpdu_new ();
  zl_dlist_enqueue (&lldp, ptr);

  /* Serialize all the objects */
  zl_dlist_foreach_safe (cursor, n, &lldp) {
    int ret;
    zl_object_t *obj = ZL_GET_OBJECT (cursor);

    ret = zl_object_serialize_tlv (obj, buf+size);
    if (ret != -1) {
      size += ret;
    }

    /* Free */
    zl_dlist_remove (cursor);
    zl_object_free (obj);
  }

  return send_packet (buf, size);
}
