/*- 
 * Copyright (c) 2017 Etienne Bagnoud <etienne@artisan-numerique.ch>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tournament.h"

Opponent * opponent_init(unsigned int id, char * name) {
    Opponent * opp = NULL;
    size_t name_len = 0;

    assert(!is_null(name));

    if(!is_null($(opp))) {
        opp->_type = TOURNAMENT_TYPE_OPPONENT;
        opp->id = id;
        opp->weight = 0;
        opp->any = NULL;
        name_len = strlen(name) + 1;
        if(MAX_OPPONENT_NAME > 0 && name_len > MAX_OPPONENT_NAME) {
            name_len = MAX_OPPONENT_NAME;
        }
        if(is_null($$(name_len, opp->name))) {
            null(opp);
        } else {
            strncpy(opp->name, name, name_len);
            opp->name[name_len - 1] = '\0';
        }
    }

    return opp;
}

void opponent_dump(FILE * stream, Opponent * opp) {
    assert(!is_null(opp));

    if(is_null(stream)) {
        stream = stdout;
    }

    fprintf(stream, "Opponent %d : %s - %d\n", opp->id, opp->name, opp->weight);
    
    return;
}

/* Return always NULL */
void * opponent_free(Opponent * opp) {
    assert(!is_null(opp));

    if(!is_null(opp->name)) {
        null(opp->name);
    }
    null(opp);

    return NULL;
}
