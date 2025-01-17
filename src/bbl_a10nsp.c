/*
 * BNG Blaster (BBL) - A10NSP Functions
 *
 * Christian Giese, September 2021
 *
 * Copyright (C) 2020-2021, RtBrick, Inc.
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "bbl.h"
#include "bbl_stream.h"

void
bbl_a10nsp_session_free(bbl_session_s *session)
{
    if(session->a10nsp_session) {
        if(session->a10nsp_session->pppoe_aci) {
            free(session->a10nsp_session->pppoe_aci);
        }
        if(session->a10nsp_session->pppoe_ari) {
            free(session->a10nsp_session->pppoe_ari);
        }
        free(session->a10nsp_session);
        session->a10nsp_session = NULL;
    }
}

static void
bbl_a10nsp_pppoed_handler(bbl_interface_s *interface,
                          bbl_session_s *session,
                          bbl_ethernet_header_t *eth)
{
    bbl_a10nsp_session_t *a10nsp_session = session->a10nsp_session;
    bbl_pppoe_discovery_t *pppoed = (bbl_pppoe_discovery_t*)eth->next;
    uint8_t ac_cookie[16];
    uint8_t i;

    switch(pppoed->code) {
        case PPPOE_PADI:
            pppoed->code = PPPOE_PADO;
            /* Init random AC-Cookie */
            for(i = 0; i < sizeof(ac_cookie); i++) {
                ac_cookie[i] = rand();
            }
            pppoed->ac_cookie = ac_cookie;
            pppoed->ac_cookie_len = sizeof(ac_cookie);

            if(pppoed->access_line) {
                if(pppoed->access_line->aci) {
                    if(a10nsp_session->pppoe_aci) {
                        free(a10nsp_session->pppoe_aci);
                    }
                    a10nsp_session->pppoe_aci = strdup(pppoed->access_line->aci);
                }
                if(pppoed->access_line->ari) {
                    if(a10nsp_session->pppoe_ari) {
                        free(a10nsp_session->pppoe_ari);
                    }
                    a10nsp_session->pppoe_ari = strdup(pppoed->access_line->ari);
                }
            }
            break;
        case PPPOE_PADR:
            pppoed->code = PPPOE_PADS;
            pppoed->session_id = (uint16_t)session->session_id;
            break;
        default:
            return;
    }
    pppoed->access_line = NULL;
    pppoed->service_name = (uint8_t*)A10NSP_PPPOE_SERVICE_NAME;
    pppoed->service_name_len = sizeof(A10NSP_PPPOE_SERVICE_NAME)-1;
    pppoed->ac_name = (uint8_t*)A10NSP_PPPOE_AC_NAME;
    pppoed->ac_name_len = sizeof(A10NSP_PPPOE_AC_NAME)-1;
    if(bbl_send_to_buffer(interface, eth) == BBL_SEND_OK) {
        a10nsp_session->stats.packets_tx++;
    }
    return;
}

static void
bbl_a10nsp_lcp_handler(bbl_interface_s *interface,
                       bbl_session_s *session,
                       bbl_ethernet_header_t *eth)
{
    bbl_a10nsp_session_t *a10nsp_session = session->a10nsp_session;
    bbl_pppoe_session_t *pppoes = (bbl_pppoe_session_t*)eth->next;
    bbl_lcp_t *lcp = (bbl_lcp_t*)pppoes->next;
    bbl_lcp_t lcp_request = {0};

    switch(lcp->code) {
        case PPP_CODE_CONF_REQUEST:
            lcp->code = PPP_CODE_CONF_ACK;
            if(bbl_send_to_buffer(interface, eth) == BBL_SEND_OK) {
                a10nsp_session->stats.packets_tx++;
            }
            lcp_request.code = PPP_CODE_CONF_REQUEST;
            lcp_request.identifier = 1;
            lcp_request.auth = PROTOCOL_PAP;
            lcp_request.mru = PPPOE_DEFAULT_MRU;
            lcp_request.magic = lcp->magic+1;
            pppoes->next = &lcp_request;
            if(bbl_send_to_buffer(interface, eth) == BBL_SEND_OK) {
                a10nsp_session->stats.packets_tx++;
            }
            break;
        case PPP_CODE_ECHO_REQUEST:
            lcp->code = PPP_CODE_ECHO_REPLY;
            if(bbl_send_to_buffer(interface, eth) == BBL_SEND_OK) {
                a10nsp_session->stats.packets_tx++;
            }
            break;
        case PPP_CODE_TERM_REQUEST:
            lcp->code = PPP_CODE_TERM_ACK;
            if(bbl_send_to_buffer(interface, eth) == BBL_SEND_OK) {
                a10nsp_session->stats.packets_tx++;
            }
            break;
        default:
            break;
    }
}

static void
bbl_a10nsp_pap_handler(bbl_interface_s *interface,
                       bbl_session_s *session,
                       bbl_ethernet_header_t *eth)
{
    bbl_a10nsp_session_t *a10nsp_session = session->a10nsp_session;
    bbl_pppoe_session_t *pppoes = (bbl_pppoe_session_t*)eth->next;
    bbl_pap_t *pap = (bbl_pap_t*)pppoes->next;
    bbl_pap_t pap_response = {0};

    pap_response.code = PAP_CODE_ACK;
    pap_response.identifier = pap->identifier;
    pap_response.reply_message = A10NSP_REPLY_MESSAGE;
    pap_response.reply_message_len = sizeof(A10NSP_REPLY_MESSAGE)-1;
    pppoes->next = &pap_response;
    if(bbl_send_to_buffer(interface, eth) == BBL_SEND_OK) {
        a10nsp_session->stats.packets_tx++;
    }
}

static void
bbl_a10nsp_ipcp_handler(bbl_interface_s *interface,
                        bbl_session_s *session,
                        bbl_ethernet_header_t *eth)
{
    bbl_a10nsp_session_t *a10nsp_session = session->a10nsp_session;
    bbl_pppoe_session_t *pppoes = (bbl_pppoe_session_t*)eth->next;
    bbl_ipcp_t *ipcp = (bbl_ipcp_t*)pppoes->next;
    bbl_ipcp_t ipcp_request = {0};

    UNUSED(session);

    switch(ipcp->code) {
        case PPP_CODE_CONF_REQUEST:
            if(ipcp->address == A10NSP_IP_REMOTE) {
                ipcp->code = PPP_CODE_CONF_ACK;
            } else {
                ipcp->options = NULL;
                ipcp->options_len = 0;
                ipcp->code = PPP_CODE_CONF_NAK;
                ipcp->address = L2TP_IPCP_IP_REMOTE;
                ipcp->option_address = true;
                if(ipcp->option_dns1) {
                    ipcp->dns1 = L2TP_IPCP_DNS1;
                }
                if(ipcp->option_dns2) {
                    ipcp->dns2 = L2TP_IPCP_DNS2;
                }
            }
            if(bbl_send_to_buffer(interface, eth) == BBL_SEND_OK) {
                a10nsp_session->stats.packets_tx++;
            }
            ipcp_request.code = PPP_CODE_CONF_REQUEST;
            ipcp_request.identifier = 1;
            ipcp_request.address = L2TP_IPCP_IP_LOCAL;
            ipcp_request.option_address = true;
            pppoes->next = &ipcp_request;
            if(bbl_send_to_buffer(interface, eth) == BBL_SEND_OK) {
                a10nsp_session->stats.packets_tx++;
            }
            break;
        case PPP_CODE_TERM_REQUEST:
            ipcp->code = PPP_CODE_TERM_ACK;
            if(bbl_send_to_buffer(interface, eth) == BBL_SEND_OK) {
                a10nsp_session->stats.packets_tx++;
            }
            break;
        default:
            break;
    }
}

static void
bbl_a10nsp_ip6cp_handler(bbl_interface_s *interface,
                         bbl_session_s *session,
                         bbl_ethernet_header_t *eth)
{
    bbl_a10nsp_session_t *a10nsp_session = session->a10nsp_session;
    bbl_pppoe_session_t *pppoes = (bbl_pppoe_session_t*)eth->next;
    bbl_ip6cp_t *ip6cp = (bbl_ip6cp_t*)pppoes->next;
    bbl_ip6cp_t ip6cp_request = {0};

    UNUSED(session);

    switch(ip6cp->code) {
        case PPP_CODE_CONF_REQUEST:
            ip6cp->code = PPP_CODE_CONF_ACK;
            if(bbl_send_to_buffer(interface, eth) == BBL_SEND_OK) {
                a10nsp_session->stats.packets_tx++;
            }
            ip6cp_request.code = PPP_CODE_CONF_REQUEST;
            ip6cp_request.identifier = 1;
            ip6cp_request.ipv6_identifier = 1;
            pppoes->next = &ip6cp_request;
            if(bbl_send_to_buffer(interface, eth) == BBL_SEND_OK) {
                a10nsp_session->stats.packets_tx++;
            }
            break;
        case PPP_CODE_TERM_REQUEST:
            ip6cp->code = PPP_CODE_TERM_ACK;
            if(bbl_send_to_buffer(interface, eth) == BBL_SEND_OK) {
                a10nsp_session->stats.packets_tx++;
            }
            break;
        default:
            break;
    }
}

static void
bbl_a10nsp_pppoes_handler(bbl_interface_s *interface,
                          bbl_session_s *session,
                          bbl_ethernet_header_t *eth)
{
    bbl_ctx_s *ctx = interface->ctx;
    bbl_pppoe_session_t *pppoes = (bbl_pppoe_session_t*)eth->next;

    bbl_ipv4_t  *ipv4;
    bbl_udp_t   *udp;
    bbl_bbl_t   *bbl;

    bbl_stream *stream;
    void **search = NULL;

    struct timespec delay;
    uint64_t delay_nsec;

    switch(pppoes->protocol) {
        case PROTOCOL_LCP:
            bbl_a10nsp_lcp_handler(interface, session, eth);
            break;
        case PROTOCOL_PAP:
            bbl_a10nsp_pap_handler(interface, session, eth);
            break;
        case PROTOCOL_IPCP:
            bbl_a10nsp_ipcp_handler(interface, session, eth);
            break;
        case PROTOCOL_IP6CP:
            bbl_a10nsp_ip6cp_handler(interface, session, eth);
            break;
        case PROTOCOL_IPV4:
            ipv4 = (bbl_ipv4_t*)pppoes->next;
            if(ipv4->protocol == PROTOCOL_IPV4_UDP) {
                udp = (bbl_udp_t*)ipv4->next;
                if(udp->protocol == UDP_PROTOCOL_BBL) {
                    bbl = (bbl_bbl_t*)udp->next;
                    search = dict_search(ctx->stream_flow_dict, &bbl->flow_id);
                    if(search) {
                        stream = *search;
                        stream->packets_rx++;
                        stream->rx_len = eth->length;
                        stream->rx_priority = ipv4->tos;
                        stream->rx_outer_vlan_pbit = eth->vlan_outer_priority;
                        stream->rx_inner_vlan_pbit = eth->vlan_inner_priority;
                        timespec_sub(&delay, &eth->timestamp, &bbl->timestamp);
                        delay_nsec = delay.tv_sec * 1e9 + delay.tv_nsec;
                        if(delay_nsec > stream->max_delay_ns) {
                            stream->max_delay_ns = delay_nsec;
                        }
                        if(stream->min_delay_ns) {
                            if(delay_nsec < stream->min_delay_ns) {
                                stream->min_delay_ns = delay_nsec;
                            }
                        } else {
                            stream->min_delay_ns = delay_nsec;
                        }
                        if(!stream->rx_first_seq) {
                            stream->rx_first_seq = bbl->flow_seq;
                            interface->ctx->stats.stream_traffic_flows_verified++;
                        } else {
                            if(stream->rx_last_seq +1 != bbl->flow_seq) {
                                stream->loss++;
                            }
                        }
                        stream->rx_last_seq = bbl->flow_seq;
                    } else {
                        if(bbl->flow_id == session->access_ipv4_tx_flow_id) {
                            interface->stats.session_ipv4_rx++;
                            session->stats.network_ipv4_rx++;
                            if(!session->network_ipv4_rx_first_seq) {
                                session->network_ipv4_rx_first_seq = bbl->flow_seq;
                                interface->ctx->stats.session_traffic_flows_verified++;
                            } else {
                                if(session->network_ipv4_rx_last_seq+1 != bbl->flow_seq) {
                                    interface->stats.session_ipv4_loss++;
                                    session->stats.network_ipv4_loss++;
                                    LOG(LOSS, "LOSS (ID: %u) flow: %lu seq: %lu last: %lu\n",
                                        session->session_id, bbl->flow_id, bbl->flow_seq, session->network_ipv4_rx_last_seq);
                                }
                            }
                            session->network_ipv4_rx_last_seq = bbl->flow_seq;
                        }
                    }
                }
            }
            break;
        default:
            break;
    }
}

/**
 * bbl_a10nsp_rx
 *
 * This function handles all received session
 * traffic on a10nsp interfaces.
 *
 * @param interface Receiving interface.
 * @param session Client session.
 * @param eth Received ethernet packet.
 */
void
bbl_a10nsp_rx(bbl_interface_s *interface,
              bbl_session_s *session,
              bbl_ethernet_header_t *eth)
{
    /* Create A10NSP session if not already present */
    if(!session->a10nsp_session) {
        LOG(DEBUG, "A10NSP (ID: %u) Session created on interface %s with S-VLAN %d\n",
            session->session_id, interface->name, eth->vlan_outer);
        session->a10nsp_session = calloc(1, sizeof(bbl_a10nsp_session_t));
        session->a10nsp_session->session = session;
        session->a10nsp_session->a10nsp_if = interface;
        session->a10nsp_session->s_vlan = eth->vlan_outer;
        session->a10nsp_session->qinq_received = eth->qinq;
        session->network_interface = interface;
    }
    session->a10nsp_session->stats.packets_rx++;

    /* Swap source/destination MAC addresses for response ... */
    eth->dst = eth->src;
    eth->src = interface->mac;
    eth->qinq = interface->qinq;
    switch(eth->type) {
        case ETH_TYPE_PPPOE_DISCOVERY:
            bbl_a10nsp_pppoed_handler(interface, session, eth);
            break;
        case ETH_TYPE_PPPOE_SESSION:
            bbl_a10nsp_pppoes_handler(interface, session, eth);
            break;
        default:
            break;
    }
    return;
}
