/**
 * \file src/filter/scanner.h
 * \author Michal Sedlak <xsedla0v@stud.fit.vutbr.cz>
 * \brief Scanner header file
 * \date 2020
 */

/* 
 * Copyright (C) 2020 CESNET, z.s.p.o.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name of the Company nor the names of its contributors
 *    may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * ALTERNATIVELY, provided that this notice is retained in full, this
 * product may be distributed under the terms of the GNU General Public
 * License (GPL) version 2 or later, in which case the provisions
 * of the GPL apply INSTEAD OF those given above.
 *
 * This software is provided ``as is'', and any express or implied
 * warranties, including, but not limited to, the implied warranties of
 * merchantability and fitness for a particular purpose are disclaimed.
 * In no event shall the company or contributors be liable for any
 * direct, indirect, incidental, special, exemplary, or consequential
 * damages (including, but not limited to, procurement of substitute
 * goods or services; loss of use, data, or profits; or business
 * interruption) however caused and on any theory of liability, whether
 * in contract, strict liability, or tort (including negligence or
 * otherwise) arising in any way out of the use of this software, even
 * if advised of the possibility of such damage.
 *
 */

#ifndef FDS_FILTER_SCANNER_H
#define FDS_FILTER_SCANNER_H

#include <stdio.h>
#include <stdbool.h>

#include "common.h"
#include "values.h"
#include "error.h"

enum token_kind_e {
    TK_NONE = 0,
    TK_LITERAL,
    TK_SYMBOL,
    TK_NAME,
    TK_END
};

struct token_s {
    enum token_kind_e kind;
    union {
        struct {
            int data_type;
            fds_filter_value_u value;
        } literal;
        const char *symbol;
        char *name;
    };
    const char *cursor_begin;
    const char *cursor_end;
};

struct scanner_s {
    const char *input;
    const char *cursor;
    struct token_s token;
    bool token_ready;
};

void
init_scanner(struct scanner_s *scanner, const char *input);

error_t
next_token(struct scanner_s *scanner, struct token_s *token);

void
consume_token(struct scanner_s *scanner);

bool
token_is(struct token_s token, enum token_kind_e kind);

bool
token_is_symbol(struct token_s token, const char *symbol);

void
destroy_token(struct token_s token);

void
print_token(FILE *out, struct token_s *token);

#endif