/*
 * BNG Blaster (BBL) - IS-IS P2P Hello
 *
 * Christian Giese, February 2022
 *
 * Copyright (C) 2020-2022, RtBrick, Inc.
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef __BBL_ISIS_P2P_HELLO_H__
#define __BBL_ISIS_P2P_HELLO_H__

protocol_error_t
isis_p2p_hello_encode(bbl_interface_s *interface, 
                      uint8_t *buf, uint16_t *len, 
                      bbl_ethernet_header_t *eth);

void
isis_p2p_hello_handler_rx(bbl_interface_s *interface,
                          isis_pdu_t *pdu);
                    
#endif