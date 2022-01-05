/*
 * Protocol Encode/Decode Functions
 *
 * Christian Giese, July 2020
 *
 * Copyright (C) 2020-2021, RtBrick, Inc.
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __BBL_PROTOCOLS_H__
#define __BBL_PROTOCOLS_H__

#include <endian.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <netinet/if_ether.h>
#include <netinet/ip.h>

#define BROADBAND_FORUM                 3561
#define RTBRICK                         50058

#define BBL_MAGIC_NUMBER                0x5274427269636b21
#define BBL_UDP_PORT                    65056
#define BBL_HEADER_LEN                  48
#define BBL_TYPE_UNICAST_SESSION        1
#define BBL_TYPE_MULTICAST              2
#define BBL_SUB_TYPE_IPV4               1
#define BBL_SUB_TYPE_IPV6               2
#define BBL_SUB_TYPE_IPV6PD             3
#define BBL_DIRECTION_UP                1
#define BBL_DIRECTION_DOWN              2

#define BROADBAND_FORUM_VENDOR_ID       3561

#define ETH_TYPE_VLAN                   0x8100
#define ETH_TYPE_QINQ                   0x88A8
#define ETH_TYPE_PPPOE_DISCOVERY        0x8863
#define ETH_TYPE_PPPOE_SESSION          0x8864
#define ETH_TYPE_ARP                    0x0806
#define ETH_TYPE_IPV4                   0x0800
#define ETH_TYPE_IPV6                   0x86dd
#define ETH_TYPE_CFM                    0x8902

#define ETH_ADDR_LEN                    6
#define ETH_VLAN_ID_MAX                 4095
#define ETH_VLAN_PBIT_MAX               7

#define OUI_LEN                         3

#define IPV4_RF                         0x8000 /* reserved fragment flag */
#define IPV4_DF                         0x4000 /* dont fragment flag */
#define IPV4_MF                         0x2000 /* more fragments flag */
#define IPV4_OFFMASK                    0x1fff /* mask for fragmenting bits */

#define IPV6_ADDR_LEN                   16
#define IPV6_IDENTIFER_LEN              8

#define PPPOE_TAG_SERVICE_NAME          0x0101
#define PPPOE_TAG_HOST_UNIQ             0x0103
#define PPPOE_TAG_AC_COOKIE             0x0104
#define PPPOE_TAG_VENDOR                0x0105

#define PPPOE_PADI                      0x09
#define PPPOE_PADO                      0x07
#define PPPOE_PADR                      0x19
#define PPPOE_PADS                      0x65
#define PPPOE_PADT                      0xa7

#define PPPOE_DEFAULT_MRU               1492

#define PROTOCOL_LCP                    0xc021
#define PROTOCOL_IPCP                   0x8021
#define PROTOCOL_IP6CP                  0x8057
#define PROTOCOL_IPV4                   0x0021
#define PROTOCOL_IPV6                   0x0057
#define PROTOCOL_PAP                    0xc023 /* Password Authentication Protocol */
#define PROTOCOL_CHAP                   0xc223 /* Challenge Handshake Authentication Protocol */
#define PROTOCOL_IPV4_ICMP              0x01
#define PROTOCOL_IPV4_IGMP              0x02
#define PROTOCOL_IPV4_TCP               0x06
#define PROTOCOL_IPV4_UDP               0x11
#define PROTOCOL_IPV4_INTERNAL          0x3D

#define ICMP_TYPE_ECHO_REPLY            0x00
#define ICMP_TYPE_ECHO_REQUEST          0x08

#define PPP_CODE_VENDOR_SPECIFIC        0
#define PPP_CODE_CONF_REQUEST           1
#define PPP_CODE_CONF_ACK               2
#define PPP_CODE_CONF_NAK               3
#define PPP_CODE_CONF_REJECT            4
#define PPP_CODE_TERM_REQUEST           5
#define PPP_CODE_TERM_ACK               6
#define PPP_CODE_CODE_REJECT            7
#define PPP_CODE_PROT_REJECT            8
#define PPP_CODE_ECHO_REQUEST           9
#define PPP_CODE_ECHO_REPLY             10
#define PPP_CODE_DISCARD_REQUEST        11

#define PPP_MAX_OPTIONS                 8

#define PAP_CODE_REQUEST                1
#define PAP_CODE_ACK                    2
#define PAP_CODE_NAK                    3

#define CHAP_CODE_CHALLENGE             1
#define CHAP_CODE_RESPONSE              2
#define CHAP_CODE_SUCCESS               3
#define CHAP_CODE_FAILURE               4

#define PPP_OPTIONS_BUFFER              64

#define PPP_LCP_OPTION_MRU              1
#define PPP_LCP_OPTION_AUTH             3
#define PPP_LCP_OPTION_MAGIC            5

#define PPP_IPCP_OPTION_ADDRESS         3
#define PPP_IPCP_OPTION_DNS1            129
#define PPP_IPCP_OPTION_DNS2            131

#define PPP_IP6CP_OPTION_IDENTIFIER     1

#define IGMP_VERSION_1                  1
#define IGMP_VERSION_2                  2
#define IGMP_VERSION_3                  3

#define IGMP_TYPE_QUERY                 0x11
#define IGMP_TYPE_REPORT_V1             0x12
#define IGMP_TYPE_REPORT_V2             0x16
#define IGMP_TYPE_REPORT_V3             0x22
#define IGMP_TYPE_LEAVE                 0x17

#define IGMP_INCLUDE                    1
#define IGMP_EXCLUDE                    2
#define IGMP_CHANGE_TO_INCLUDE          3
#define IGMP_CHANGE_TO_EXCLUDE          4
#define IGMP_ALLOW_NEW_SOURCES          5
#define IGMP_BLOCK_OLD_SOURCES          6

#define IGMP_MAX_SOURCES                3
#define IGMP_MAX_GROUPS                 8

#define IPV4_BROADCAST                  0xffffffff /* 255.255.255.255 */
#define IPV4_MC_ALL_HOSTS               0x010000e0 /* 224.0.0.1 */
#define IPV4_MC_ALL_ROUTERS             0x020000e0 /* 224.0.0.2 */
#define IPV4_MC_IGMP                    0x160000e0 /* 224.0.0.22 */

#define ARP_REQUEST                     1
#define ARP_REPLY                       2

#define UDP_PROTOCOL_DHCPV6             1
#define UDP_PROTOCOL_BBL                2
#define UDP_PROTOCOL_L2TP               3
#define UDP_PROTOCOL_QMX_LI             4
#define UDP_PROTOCOL_DHCP               5

#define IPV6_NEXT_HEADER_TCP            6
#define IPV6_NEXT_HEADER_UDP            17
#define IPV6_NEXT_HEADER_ICMPV6         58
#define IPV6_NEXT_HEADER_NO             59
#define IPV6_NEXT_HEADER_INTERNAL       61

#define ICMPV6_FLAGS_OTHER_CONFIG       0x40
#define ICMPV6_OPTION_PREFIX            3
#define ICMPV6_OPTION_DNS               25

#define BOOTREQUEST                     1
#define BOOTREPLY                       2
#define DHCP_UDP_CLIENT                 68
#define DHCP_UDP_SERVER                 67
#define DHCP_MAGIC_COOKIE               htobe32(0x63825363)
#define DHCP_RELAY_AGENT_VENDOR_SUBOPT  9

#define DHCPV6_TRANS_ID_LEN             3
#define DHCPV6_TYPE_MASK                0x00ffffff
#define DHCPV6_DUID_LEN_MIN             3
#define DHCPV6_DUID_LEN_MAX             130
#define DHCPV6_HDR_LEN                  4
#define DHCPV6_OPTION_HDR_LEN           4
#define DHCPV6_STATUS_CODE_LEN          2
#define DHCPV6_IA_ADDRESS_OPTION_LEN    24
#define DHCPV6_IA_PREFIX_OPTION_LEN     25
#define DHCPV6_ORO_OPTION_LEN           2
#define DHCPV6_UDP_CLIENT               546
#define DHCPV6_UDP_SERVER               547

#define L2TP_UDP_PORT                   1701
#define L2TP_HDR_VERSION_MASK           0x0f
#define L2TP_HDR_CTRL_BIT_MASK          0x80
#define L2TP_HDR_LEN_BIT_MASK           0x40
#define L2TP_HDR_SEQ_BIT_MASK           0x08
#define L2TP_HDR_OFFSET_BIT_MASK        0x02
#define L2TP_HDR_PRIORITY_BIT_MASK      0x01
#define L2TP_HDR_LEN_MIN_WITH_LEN       8
#define L2TP_AVP_M_BIT_SHIFT            15
#define L2TP_AVP_H_BIT_SHIFT            14
#define L2TP_AVP_LEN_MASK               0x03FF
#define L2TP_AVP_HDR_LEN                6
#define L2TP_AVP_M_BIT_MASK             0x8000
#define L2TP_AVP_H_BIT_MASK             0x4000
#define L2TP_AVP_TYPE_LEN               2
#define L2TP_AVP_TYPE_LEN               2
#define L2TP_AVP_HIDDEN_FIXED_LEN       2
#define L2TP_AVP_MAX_LEN                1024

#define L2TP_NH_TYPE_VALUE              18

#define QMX_LI_UDP_PORT                 49152

#define CFM_TYPE_CCM                    1
#define CMF_MD_NAME_FORMAT_NONE         1
#define CMF_MD_NAME_FORMAT_STRING       4
#define CMF_MA_NAME_FORMAT_STRING       2

#define MAX_VLANS                       3

#define BUMP_BUFFER(_buf, _len, _size) \
    (_buf) += _size; \
    _len -= _size

#define BUMP_WRITE_BUFFER(_buf, _len, _size) \
    (_buf) += _size; \
    *(uint16_t*)(_len) += _size

typedef uint8_t ipv6addr_t[IPV6_ADDR_LEN];

typedef struct ipv6_prefix_ {
    uint8_t         len;
    ipv6addr_t      address;
} ipv6_prefix;

/* IPv6 Addresses */
static const ipv6addr_t ipv6_link_local_prefix = {0xFE, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
static const ipv6addr_t ipv6_multicast_all_nodes = {0xFF, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01};
static const ipv6addr_t ipv6_multicast_all_routers = {0xFF, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02};
static const ipv6addr_t ipv6_multicast_all_dhcp = {0xFF, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x02};
static const ipv6addr_t ipv6_solicited_node_multicast = {0xFF, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 0x00, 0x00, 0x00};

/* MAC Addresses */
static const uint8_t broadcast_mac[ETH_ADDR_LEN] =  { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};


typedef enum protocol_error_ {
    PROTOCOL_SUCCESS = 0,
    SEND_ERROR,
    DECODE_ERROR,
    ENCODE_ERROR,
    UNKNOWN_PROTOCOL,
    WRONG_PROTOCOL_STATE,
    IGNORED,
    EMPTY
} protocol_error_t;

typedef enum icmpv6_message_type_ {
    IPV6_ICMPV6_ECHO_REQUEST           = 128,
    IPV6_ICMPV6_ECHO_REPLY             = 129,
    IPV6_ICMPV6_ROUTER_SOLICITATION    = 133,
    IPV6_ICMPV6_ROUTER_ADVERTISEMENT   = 134,
    IPV6_ICMPV6_NEIGHBOR_SOLICITATION  = 135,
    IPV6_ICMPV6_NEIGHBOR_ADVERTISEMENT = 136
} icmpv6_message_type;

typedef enum dhcpv6_message_type_ {
    DHCPV6_MESSAGE_SOLICIT              = 1,
    DHCPV6_MESSAGE_ADVERTISE            = 2,
    DHCPV6_MESSAGE_REQUEST              = 3,
    DHCPV6_MESSAGE_CONFIRM              = 4,
    DHCPV6_MESSAGE_RENEW                = 5,
    DHCPV6_MESSAGE_REBIND               = 6,
    DHCPV6_MESSAGE_REPLY                = 7,
    DHCPV6_MESSAGE_RELEASE              = 8,
    DHCPV6_MESSAGE_DECLINE              = 9,
    DHCPV6_MESSAGE_RECONFIGURE          = 10,
    DHCPV6_MESSAGE_INFORMATION_REQUEST  = 11,
    DHCPV6_MESSAGE_RELAY_FORW           = 12,
    DHCPV6_MESSAGE_RELAY_REPL           = 13,
    DHCPV6_MESSAGE_MAX,
} dhcpv6_message_type;

typedef enum l2tp_message_type_ {
    L2TP_MESSAGE_DATA          = 0,
    L2TP_MESSAGE_SCCRQ         = 1,
    L2TP_MESSAGE_SCCRP         = 2,
    L2TP_MESSAGE_SCCCN         = 3,
    L2TP_MESSAGE_STOPCCN       = 4,
    L2TP_MESSAGE_HELLO         = 6,
    L2TP_MESSAGE_OCRQ          = 7,
    L2TP_MESSAGE_OCRP          = 8,
    L2TP_MESSAGE_OCCN          = 9,
    L2TP_MESSAGE_ICRQ          = 10,
    L2TP_MESSAGE_ICRP          = 11,
    L2TP_MESSAGE_ICCN          = 12,
    L2TP_MESSAGE_CDN           = 14,
    L2TP_MESSAGE_WEN           = 15,
    L2TP_MESSAGE_CSUN          = 28,
    L2TP_MESSAGE_CSURQ         = 29,
    L2TP_MESSAGE_ZLB           = 32767,
    L2TP_MESSAGE_MAX,
} l2tp_message_type;

typedef enum dhcpv6_option_code_ {
    DHCPV6_OPTION_CLIENTID              = 1,
    DHCPV6_OPTION_SERVERID              = 2,
    DHCPV6_OPTION_IA_NA                 = 3,
    DHCPV6_OPTION_IA_TA                 = 4,
    DHCPV6_OPTION_IAADDR                = 5,
    DHCPV6_OPTION_ORO                   = 6,
    DHCPV6_OPTION_PREFERENCE            = 7,
    DHCPV6_OPTION_ELAPSED_TIME          = 8,
    DHCPV6_OPTION_RELAY_MSG             = 9,
    DHCPV6_OPTION_AUTH                  = 11,
    DHCPV6_OPTION_UNICAST               = 12,
    DHCPV6_OPTION_STATUS_CODE           = 13,
    DHCPV6_OPTION_RAPID_COMMIT          = 14,
    DHCPV6_OPTION_USER_CLASS            = 15,
    DHCPV6_OPTION_VENDOR_CLASS          = 16,
    DHCPV6_OPTION_VENDOR_OPTS           = 17,
    DHCPV6_OPTION_INTERFACE_ID          = 18,
    DHCPV6_OPTION_DNS_SERVERS           = 23,
    DHCPV6_OPTION_DOMAIN_LIST           = 24,
    DHCPV6_OPTION_IA_PD                 = 25,
    DHCPV6_OPTION_IAPREFIX              = 26,
    DHCPV6_OPTION_REMOTE_ID             = 37,
    DHCPV6_OPTION_MAX,
} dhcpv6_option_code;

typedef enum dhcp_message_type_ {
    DHCP_MESSAGE_DISCOVER              = 1,
    DHCP_MESSAGE_OFFER                 = 2,
    DHCP_MESSAGE_REQUEST               = 3,
    DHCP_MESSAGE_DECLINE               = 4,
    DHCP_MESSAGE_ACK                   = 5,
    DHCP_MESSAGE_NAK                   = 6,
    DHCP_MESSAGE_RELEASE               = 7,
    DHCP_MESSAGE_INFORM                = 8,
    DHCP_MESSAGE_MAX
} dhcp_message_type;

typedef enum dhcp_option_code_ {
    DHCP_OPTION_PAD                          = 0,
    DHCP_OPTION_SUBNET_MASK                  = 1,
    DHCP_OPTION_TIME_OFFSET                  = 2,
    DHCP_OPTION_ROUTER                       = 3,
    DHCP_OPTION_TIME_SERVER                  = 4,
    DHCP_OPTION_NAME_SERVER                  = 5,
    DHCP_OPTION_DNS_SERVER                   = 6,
    DHCP_OPTION_LOG_SERVER                   = 7,
    DHCP_OPTION_COOKIE_SERVER                = 8,
    DHCP_OPTION_LPR_SERVER                   = 9,
    DHCP_OPTION_IMPRESS_SERVER               = 10,
    DHCP_OPTION_RESOURCE_LOCATION_SERVER     = 11,
    DHCP_OPTION_HOST_NAME                    = 12,
    DHCP_OPTION_BOOT_FILE_SIZE               = 13,
    DHCP_OPTION_MERIT_DUMP_FILE              = 14,
    DHCP_OPTION_DOMAIN_NAME                  = 15,
    DHCP_OPTION_SWAP_SERVER                  = 16,
    DHCP_OPTION_ROOT_PATH                    = 17,
    DHCP_OPTION_EXTENSIONS_PATH              = 18,
    DHCP_OPTION_IP_FORWARDING                = 19,
    DHCP_OPTION_NON_LOCAL_SOURCE_ROUTING     = 20,
    DHCP_OPTION_POLICY_FILTER                = 21,
    DHCP_OPTION_MAX_DATAGRAM_REASSEMBLY_SIZE = 22,
    DHCP_OPTION_DEFAULT_IP_TTL               = 23,
    DHCP_OPTION_PATH_MTU_AGING_TIMEOUT       = 24,
    DHCP_OPTION_PATH_MTU_PLATEAU_TABLE       = 25,
    DHCP_OPTION_INTERFACE_MTU                = 26,
    DHCP_OPTION_ALL_SUBNETS_ARE_LOCAL        = 27,
    DHCP_OPTION_BROADCAST_ADDRESS            = 28,
    DHCP_OPTION_PERFORM_MASK_DISCOVERY       = 29,
    DHCP_OPTION_MASK_SUPPLIER                = 30,
    DHCP_OPTION_PERFORM_ROUTER_DISCOVERY     = 31,
    DHCP_OPTION_ROUTER_SOLICITATION_ADDRESS  = 32,
    DHCP_OPTION_STATIC_ROUTE                 = 33,
    DHCP_OPTION_TRAILER_ENCAPSULATION        = 34,
    DHCP_OPTION_ARP_CACHE_TIMEOUT            = 35,
    DHCP_OPTION_ETHERNET_ENCAPSULATION       = 36,
    DHCP_OPTION_TCP_DEFAULT_TTL              = 37,
    DHCP_OPTION_TCP_KEEPALIVE_INTERVAL       = 38,
    DHCP_OPTION_TCP_KEEPALIVE_GARBAGE        = 39,
    DHCP_OPTION_NIS_DOMAIN                   = 40,
    DHCP_OPTION_NIS_SERVER                   = 41,
    DHCP_OPTION_NTP_SERVER                   = 42,
    DHCP_OPTION_VENDOR_SPECIFIC_INFO         = 43,
    DHCP_OPTION_NETBIOS_NBNS_SERVER          = 44,
    DHCP_OPTION_NETBIOS_NBDD_SERVER          = 45,
    DHCP_OPTION_NETBIOS_NODE_TYPE            = 46,
    DHCP_OPTION_NETBIOS_SCOPE                = 47,
    DHCP_OPTION_X11_FONT_SERVER              = 48,
    DHCP_OPTION_X11_DISPLAY_MANAGER          = 49,
    DHCP_OPTION_REQUESTED_IP_ADDRESS         = 50,
    DHCP_OPTION_IP_ADDRESS_LEASE_TIME        = 51,
    DHCP_OPTION_OPTION_OVERLOAD              = 52,
    DHCP_OPTION_DHCP_MESSAGE_TYPE            = 53,
    DHCP_OPTION_SERVER_IDENTIFIER            = 54,
    DHCP_OPTION_PARAM_REQUEST_LIST           = 55,
    DHCP_OPTION_MESSAGE                      = 56,
    DHCP_OPTION_MAX_DHCP_MESSAGE_SIZE        = 57,
    DHCP_OPTION_RENEWAL_TIME_VALUE           = 58,
    DHCP_OPTION_REBINDING_TIME_VALUE         = 59,
    DHCP_OPTION_VENDOR_CLASS_IDENTIFIER      = 60,
    DHCP_OPTION_CLIENT_IDENTIFIER            = 61,
    DHCP_OPTION_NISP_DOMAIN                  = 64,
    DHCP_OPTION_NISP_SERVER                  = 65,
    DHCP_OPTION_TFTP_SERVER_NAME             = 66,
    DHCP_OPTION_BOOTFILE_NAME                = 67,
    DHCP_OPTION_MOBILE_IP_HOME_AGENT         = 68,
    DHCP_OPTION_SMTP_SERVER                  = 69,
    DHCP_OPTION_POP3_SERVER                  = 70,
    DHCP_OPTION_NNTP_SERVER                  = 71,
    DHCP_OPTION_DEFAULT_WWW_SERVER           = 72,
    DHCP_OPTION_DEFAULT_FINGER_SERVER        = 73,
    DHCP_OPTION_DEFAULT_IRC_SERVER           = 74,
    DHCP_OPTION_STREETTALK_SERVER            = 75,
    DHCP_OPTION_STDA_SERVER                  = 76,
    DHCP_OPTION_RAPID_COMMIT                 = 80,
    DHCP_OPTION_RELAY_AGENT_INFORMATION      = 82,
    DHCP_OPTION_CAPTIVE_PORTAL               = 160,
    DHCP_OPTION_END                          = 255
} dhcp_option_code;

typedef enum access_line_codes_ {
    /* broadband forum tr101 */

    ACCESS_LINE_ACI                      = 0x01,  /* Agent Circuit ID */
    ACCESS_LINE_ARI                      = 0x02,  /* Agent Remote ID */
    ACCESS_LINE_AGG_ACC_CIRCUIT_ID_ASCII = 0x03,  /* Access-Aggregation-Circuit-ID-ASCII */
    ACCESS_LINE_AGG_ACC_CIRCUIT_ID_BIN   = 0x06,  /* Access-Aggregation-Circuit-ID-BINARY */
    ACCESS_LINE_ACT_UP                   = 0x81,  /* Actual Data Rate Upstream */
    ACCESS_LINE_ACT_DOWN                 = 0x82,  /* Actual Data Rate Downstream */
    ACCESS_LINE_MIN_UP                   = 0x83,  /* Minimum Data Rate Upstream */
    ACCESS_LINE_MIN_DOWN                 = 0x84,  /* Minimum Data Rate Downstream */
    ACCESS_LINE_ATT_UP                   = 0x85,  /* Attainable DataRate Upstream */
    ACCESS_LINE_ATT_DOWN                 = 0x86,  /* Attainable DataRate Downstream */
    ACCESS_LINE_MAX_UP                   = 0x87,  /* Maximum Data Rate Upstream */
    ACCESS_LINE_MAX_DOWN                 = 0x88,  /* Maximum Data Rate Downstream */
    ACCESS_LINE_MIN_UP_LOW               = 0x89,  /* Min Data Rate Upstream in low power state */
    ACCESS_LINE_MIN_DOWN_LOW             = 0x8a,  /* Min Data Rate Downstream in low power state */
    ACCESS_LINE_MAX_INTERL_DELAY_UP      = 0x8b,  /* Max Interleaving Delay Upstream */
    ACCESS_LINE_ACT_INTERL_DELAY_UP      = 0x8c,  /* Actual Interleaving Delay Upstream */
    ACCESS_LINE_MAX_INTERL_DELAY_DOWN    = 0x8d,  /* Max Interleaving Delay Downstream */
    ACCESS_LINE_ACT_INTERL_DELAY_DOWN    = 0x8e,  /* Actual Interleaving Delay Downstream */
    ACCESS_LINE_DATA_LINK_ENCAPS         = 0x90,  /* Data Link Encapsulation */
    ACCESS_LINE_DSL_TYPE                 = 0x91,  /* DSL Type */

    /* draft-lihawi-ancp-protocol-access-extension-04 */

    ACCESS_LINE_PON_TYPE                 = 0x97,  /* PON-Access-Type */
    ACCESS_LINE_ETR_UP                   = 0x9b,  /* Expected Throughput (ETR) Upstream */
    ACCESS_LINE_ETR_DOWN                 = 0x9c,  /* Expected Throughput (ETR) Downstream */
    ACCESS_LINE_ATTETR_UP                = 0x9d,  /* Attainable Expected Throughput (ATTETR) Upstream */
    ACCESS_LINE_ATTETR_DOWN              = 0x9e,  /* Attainable Expected Throughput (ATTETR) Downstream */
    ACCESS_LINE_GDR_UP                   = 0x9f,  /* Gamma Data Rate (GDR) Upstream */
    ACCESS_LINE_GDR_DOWN                 = 0xa0,  /* Gamma Data Rate (GDR) Downstream */
    ACCESS_LINE_ATTGDR_UP                = 0xa1,  /* Attainable Gamma Data Rate (ATTGDR) Upstream */
    ACCESS_LINE_ATTGDR_DOWN              = 0xa2,  /* Attainable Gamma Data Rate (ATTGDR) Downstream */
    ACCESS_LINE_ONT_ONU_AVG_DOWN         = 0xb0,  /* ONT/ONU-Average-Data-Rate-Downstream */
    ACCESS_LINE_ONT_ONU_PEAK_DOWN        = 0xb1,  /* ONT/ONU-Peak-Data-Rate-Downstream */
    ACCESS_LINE_ONT_ONU_MAX_UP           = 0xb2,  /* ONT/ONU-Maximum-Data-Rate-Upstream */
    ACCESS_LINE_ONT_ONU_ASS_UP           = 0xb3,  /* ONT/ONU-Assured-Data-Rate-Upstream */
    ACCESS_LINE_PON_MAX_UP               = 0xb4,  /* PON-Tree-Maximum-Data-Rate-Upstream */
    ACCESS_LINE_PON_MAX_DOWN             = 0xb5,  /* PON-Tree-Maximum-Data-Rate-Downstream */
} access_line_codes;

typedef struct access_line_ {
    char    *aci;       /* Agent Circuit ID */
    char    *ari;       /* Agent Remote ID */
    uint32_t up;        /* Actual Data Rate Upstream */
    uint32_t down;      /* Actual Data Rate Downstream */
    uint32_t dsl_type;  /* DSL Type */
    void    *profile;
} access_line_t;

/*
 * Ethernet Header Structure
 */
typedef struct bbl_ethernet_header_ {
    uint8_t  *dst; /* destination MAC address */
    uint8_t  *src; /* source MAC address */
    bool      qinq; /* ethertype 0x88a8 */
    uint16_t  vlan_outer; /* outer VLAN identifier */
    uint16_t  vlan_inner; /* inner VLAN identifier */
    uint16_t  vlan_three; /* third VLAN */
    uint16_t  type; /* ethertype */
    uint8_t   vlan_outer_priority;
    uint8_t   vlan_inner_priority;
    void     *next; /* next header */
    uint16_t  length;
    struct timespec timestamp;
} bbl_ethernet_header_t;

/*
 * PPPoE Discovery Structure
 */
typedef struct bbl_pppoe_discovery_ {
    uint8_t        code;
    uint16_t       session_id;
    uint8_t       *service_name;
    uint16_t       service_name_len;
    uint8_t       *ac_name;
    uint16_t       ac_name_len;
    uint8_t       *ac_cookie;
    uint16_t       ac_cookie_len;
    uint8_t       *host_uniq;
    uint16_t       host_uniq_len;
    access_line_t *access_line;
} bbl_pppoe_discovery_t;

/*
 * PPPoE Session Structure
 *
 * Combined structure for 6 byte PPPoE
 * session and 2 byte PPP header.
 */
typedef struct bbl_pppoe_session_ {
    uint16_t  session_id;
    uint16_t  protocol;
    void     *next; /* next header */
    void     *payload; /* PPP payload */
    uint16_t  payload_len; /* PPP payload length */
} bbl_pppoe_session_t;


struct pppoe_ppp_session_header {
    uint8_t   version_type;
    uint8_t   code;
    uint16_t  session_id;
    uint16_t  len;
    uint16_t  protocol;
} __attribute__ ((__packed__));

/*
 * PPP LCP Structure
 */
typedef struct bbl_lcp_ {
    uint8_t     code;
    uint8_t     identifier;
    uint8_t    *options;
    uint8_t     options_len;
    uint16_t    mru;
    uint16_t    auth;
    uint32_t    magic;
    uint8_t     vendor_oui[OUI_LEN];
    uint8_t     vendor_kind;
    uint8_t    *vendor_value;
    uint16_t    vendor_value_len;
    uint8_t    *start;
    uint16_t    len;
    uint8_t    *option[PPP_MAX_OPTIONS];
    bool        unknown_options;
} bbl_lcp_t;

/*
 * PPP IPCP Structure
 */
typedef struct bbl_ipcp_ {
    uint8_t     code;
    uint8_t     identifier;
    uint8_t    *options;
    uint8_t     options_len;
    uint32_t    address;
    uint32_t    dns1;
    uint32_t    dns2;
    bool        option_address;
    bool        option_dns1;
    bool        option_dns2;
    uint8_t    *option[PPP_MAX_OPTIONS];
    bool        unknown_options;
} bbl_ipcp_t;

/*
 * PPP IP6CP Structure
 */
typedef struct bbl_ip6cp_ {
    uint8_t     code;
    uint8_t     identifier;
    uint8_t    *options;
    uint8_t     options_len;
    uint64_t    ipv6_identifier;
    uint8_t    *option[PPP_MAX_OPTIONS];
    bool        unknown_options;
} bbl_ip6cp_t;

/*
 * PPP PAP Structure
 */
typedef struct bbl_ppp_pap_ {
    uint8_t     code;
    uint8_t     identifier;
    char       *username;
    uint8_t     username_len;
    char       *password;
    uint8_t     password_len;
    char       *reply_message;
    uint8_t     reply_message_len;
} bbl_pap_t;

/*
 * PPP CHAP Structure
 */
typedef struct bbl_ppp_chap_ {
    uint8_t     code;
    uint8_t     identifier;
    char       *name;
    uint8_t     name_len;
    uint8_t    *challenge;
    uint8_t     challenge_len;
    char       *reply_message;
    uint8_t     reply_message_len;
} bbl_chap_t;

/*
 * IPv4 Structure
 */
typedef struct bbl_ipv4_ {
    uint32_t    src;
    uint32_t    dst;
    uint8_t     tos;
    uint16_t    offset;
    uint8_t     ttl;
    uint8_t     protocol;
    void       *next; /* next header */
    void       *payload; /* IPv4 payload */
    uint16_t    payload_len; /* IPv4 payload length */
    bool        router_alert_option; /* add router alert option if true */
} bbl_ipv4_t;

/*
 * IPv6 Structure
 */
typedef struct bbl_ipv6_ {
    uint8_t    *src;
    uint8_t    *dst;
    uint8_t     tos;
    uint8_t     ttl;
    uint8_t     protocol;
    void       *next; /* next header */
    void       *payload; /* IPv6 payload */
    uint16_t    payload_len; /* IPv6 payload length */
} bbl_ipv6_t;

/*
 * UDP Structure
 */
typedef struct bbl_udp_ {
    uint16_t    src;
    uint16_t    dst;
    uint8_t     protocol;
    void       *next; /* next header */
    void       *payload; /* UDP payload */
    uint16_t    payload_len; /* UDP payload length */
} bbl_udp_t;

/*
 * IGMP Structure
 */
typedef struct bbl_igmp_group_record_ {
    uint8_t     type;
    uint32_t    group;
    uint8_t     sources;
    uint32_t    source[IGMP_MAX_SOURCES];
} bbl_igmp_group_record_t;

typedef struct bbl_igmp_ {
    uint8_t     version;
    uint8_t     type;
    uint8_t     robustness;
    uint32_t    group;
    uint32_t    source;
    uint8_t     group_records;
    bbl_igmp_group_record_t group_record[IGMP_MAX_GROUPS];
} bbl_igmp_t;

typedef struct bbl_icmp_ {
    uint8_t     type;
    uint8_t     code;
    uint8_t    *data;
    uint16_t    data_len;
} bbl_icmp_t;

typedef struct bbl_arp_ {
    uint16_t    code;
    uint8_t    *sender;
    uint32_t    sender_ip;
    uint8_t    *target;
    uint32_t    target_ip;
} bbl_arp_t;

typedef struct bbl_icmpv6_ {
    uint8_t      type;
    uint8_t      code;
    bool         other;
    ipv6_prefix  prefix;
    uint8_t     *mac;
    uint8_t     *data;
    uint16_t     data_len;
    ipv6addr_t  *dns1;
    ipv6addr_t  *dns2;
} bbl_icmpv6_t;

typedef struct bbl_dhcpv6_ {
    uint8_t        type;
    uint32_t       xid;
    uint8_t       *client_duid;
    uint8_t        client_duid_len;
    uint8_t       *server_duid;
    uint8_t        server_duid_len;
    ipv6addr_t    *dns1;
    ipv6addr_t    *dns2;
    bool           rapid;
    bool           oro;
    uint8_t       *ia_na_option;
    uint8_t        ia_na_option_len;
    uint32_t       ia_na_iaid;
    ipv6addr_t    *ia_na_address;
    uint32_t       ia_na_t1;
    uint32_t       ia_na_t2;
    uint32_t       ia_na_preferred_lifetime;
    uint32_t       ia_na_valid_lifetime;
    uint8_t       *ia_pd_option;
    uint8_t        ia_pd_option_len;
    uint32_t       ia_pd_iaid;
    ipv6_prefix   *ia_pd_prefix;
    uint32_t       ia_pd_t1;
    uint32_t       ia_pd_t2;
    uint32_t       ia_pd_preferred_lifetime;
    uint32_t       ia_pd_valid_lifetime;
    access_line_t *access_line;
} bbl_dhcpv6_t;

struct dhcp_header {
    uint8_t     op;
    uint8_t     htype;
    uint8_t     hlen;
    uint8_t     hops;
    uint32_t    xid;
    uint16_t    secs;
    uint16_t    flags;
    uint32_t    ciaddr;
    uint32_t    yiaddr;
    uint32_t    siaddr;
    uint32_t    giaddr;
    char        chaddr[16];
    char        sname[64];
    char        file[128];
} __attribute__ ((__packed__));

typedef struct bbl_dhcp_ {
    struct dhcp_header *header;
    uint8_t      type;

    uint32_t     server_identifier;
    uint32_t     lease_time;
    uint32_t     address;
    uint32_t     netmask;
    uint32_t     dns1;
    uint32_t     dns2;
    uint32_t     router;
    uint16_t     mtu;
    char        *host_name;
    uint8_t      host_name_len;
    char        *domain_name;
    uint8_t      domain_name_len;

    bool         parameter_request_list;
    bool         option_server_identifier;
    bool         option_lease_time;
    bool         option_address;
    bool         option_netmask;
    bool         option_dns1;
    bool         option_dns2;
    bool         option_router;
    bool         option_mtu;
    bool         option_host_name;
    bool         option_domain_name;

    access_line_t *access_line;
    uint8_t *client_identifier;
    uint8_t client_identifier_len;
} bbl_dhcp_t;

typedef struct bbl_l2tp_ {
    bool        with_length;     /* L Bit */
    bool        with_sequence;   /* S Bit */
    bool        with_offset;     /* O Bit */
    bool        with_priority;   /* P Bit */
    uint16_t    type;
    uint16_t    length;
    uint16_t    tunnel_id;
    uint16_t    session_id;
    uint16_t    ns;
    uint16_t    nr;
    uint16_t    offset;
    uint16_t    protocol;
    void       *next; /* next header */
    void       *payload; /* l2tp payload */
    uint16_t    payload_len; /* l2tp payload length */
} bbl_l2tp_t;

typedef struct bbl_bbl_ {
    uint16_t     padding;
    uint8_t      type;
    uint8_t      sub_type;
    uint8_t      direction;
    uint8_t      tos;
    uint32_t     session_id;
    uint32_t     ifindex;
    uint16_t     outer_vlan_id;
    uint16_t     inner_vlan_id;
    uint32_t     mc_source;
    uint32_t     mc_group;
    uint64_t     flow_id;
    uint64_t     flow_seq;
    struct timespec timestamp;
} bbl_bbl_t;

typedef struct bbl_qmx_li_ {
    uint32_t     header;
    uint8_t      direction;
    uint8_t      packet_type;
    uint8_t      sub_packet_type;
    uint32_t     liid;
    void        *next; /* next header */
    void        *payload; /* LI payload */
    uint16_t     payload_len; /* LI payload length */
} bbl_qmx_li_t;

typedef struct bbl_cfm_ {
    uint8_t     type;
    uint32_t    seq;
    bool        rdi;
    uint8_t     md_level;
    uint8_t     md_name_format;
    uint8_t     md_name_len;
    uint8_t    *md_name;
    uint16_t    ma_id;
    uint8_t     ma_name_format;
    uint8_t     ma_name_len;
    uint8_t    *ma_name;
} bbl_cfm_t;

/*
 * decode_ethernet
 */
protocol_error_t
decode_ethernet(uint8_t *buf, uint16_t len,
                uint8_t *sp, uint16_t sp_len,
                bbl_ethernet_header_t **ethernet);

/*
 * encode_ethernet
 */
protocol_error_t
encode_ethernet(uint8_t *buf, uint16_t *len,
                bbl_ethernet_header_t *eth);

#endif