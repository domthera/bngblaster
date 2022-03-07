/*
 * BNG Blaster (BBL) - TCP
 *
 * Christian Giese, February 2022
 *
 * Copyright (C) 2020-2021, RtBrick, Inc.
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __BBL_TCP_H__
#define __BBL_TCP_H__

#define BBL_TCP_BUF_SIZE 65000
#define BBL_TCP_INTERVAL 250*MSEC
#define BBL_TCP_HASHTABLE_SIZE 32771

typedef enum bbl_tcp_state_ {
    BBL_TCP_STATE_CONNECT,
    BBL_TCP_STATE_IDLE,
    BBL_TCP_STATE_SEND,
    BBL_TCP_STATE_RECEIVE,
    BBL_TCP_STATE_CLOSING,
    BBL_TCP_STATE_CLOSED,
} bbl_tcp_state_t;

typedef void (*bbl_tcp_receive_fn)(void *arg, uint8_t *buf, uint16_t len);
typedef void (*bbl_tcp_error_fn)(void *arg, err_t err);
typedef err_t (*bbl_tcp_poll_fn)(void *arg, struct tcp_pcb *tpcb);

typedef struct bbl_tcp_key_ {
    uint16_t local_port;
    uint16_t remote_port;
} __attribute__ ((__packed__)) bbl_tcp_key_t;

typedef struct bbl_tcp_ctx_
{
    bbl_interface_s *interface;

    uint8_t af; /* AF_INET or AF_INET6 */
    
    bbl_tcp_key_t key;

    ipv4addr_t local_ipv4;
    ipv6addr_t local_ipv6;
    ipv4addr_t remote_ipv4;
    ipv6addr_t remote_ipv6;
    
    struct tcp_pcb *pcb;
    
    bbl_tcp_receive_fn receive_cb; /* application receive callback */
    bbl_tcp_error_fn error_cb; /* application receive callback */

    bbl_tcp_poll_fn poll_cb; /* application poll callback */
    uint8_t poll_interval;

    void *arg; /* application callback argument */

    bbl_tcp_state_t state;
    
    struct {
        uint8_t *buf;
        size_t   len;
        size_t   offset;
    } tx;

    uint64_t packets_rx;
    uint64_t bytes_rx;
    uint64_t packets_tx;
    uint64_t bytes_tx;

} bbl_tcp_ctx_t;

bbl_tcp_ctx_t *
bbl_tcp_ipv4_connect(bbl_interface_s *interface, ipv4addr_t *src, ipv4addr_t *dst, uint16_t port);

void
bbl_tcp_ipv4_rx(bbl_interface_s *interface, bbl_ethernet_header_t *eth, bbl_ipv4_t *ipv4);

bbl_tcp_ctx_t *
bbl_tcp_ipv6_connect(bbl_interface_s *interface, ipv6addr_t *src, ipv6addr_t *dst, uint16_t port);

void
bbl_tcp_ipv6_rx(bbl_interface_s *interface, bbl_ethernet_header_t *eth, bbl_ipv6_t *ipv6);

err_t
bbl_tcp_send(bbl_tcp_ctx_t *tcpc, uint8_t *buf, uint16_t len);

bool
bbl_tcp_interface_init(bbl_interface_s *interface, bbl_network_config_s *network_config);

void
bbl_tcp_init(bbl_ctx_s *ctx);

#endif