/*
 * BNG Blaster (BBL) - IS-IS Main
 *
 * Christian Giese, January 2022
 *
 * Copyright (C) 2020-2022, RtBrick, Inc.
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef __BBL_ISIS_H__
#define __BBL_ISIS_H__

#include "../bbl.h"
#include "isis_def.h"
#include "isis_utils.h"
#include "isis_checksum.h"
#include "isis_pdu.h"
#include "isis_adjacency.h"
#include "isis_p2p_hello.h"
#include "isis_csnp.h"
#include "isis_psnp.h"
#include "isis_lsp.h"
#include "isis_ctrl.h"

extern uint8_t g_isis_mac_p2p_hello[];
extern uint8_t g_isis_mac_all_l1[];
extern uint8_t g_isis_mac_all_l2[];

int
isis_lsp_id_compare(void *id1, void *id2);

void
isis_flood_entry_free(void *key, void *ptr);

void
isis_psnp_free(void *key, void *ptr);

bool
isis_init(bbl_ctx_s *ctx);

void
isis_handler_rx(bbl_ethernet_header_t *eth, bbl_interface_s *interface);

#endif