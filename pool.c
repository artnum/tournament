/*- 
 * Copyright (c) 2017 Artisan du Numérique <etienne@artisan-numerique.ch>
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
#include "tournament.h"


Pool * pool_init(unsigned int id) {
    Pool * pool = NULL;

    if(!is_null($(pool))) {
        pool->_type = TOURNAMENT_TYPE_POOL;
        pool->id = id;
        pool->meetings = NULL;
        pool->opponents = NULL;
        pool->opp_count = 0;
        pool->randomize = 0;
        pool->sorting = TOURNAMENT_SORT_NOROW;
    }

    return pool;
}

int pool_add(Pool * pool, Opponent * op) {
    void * tmp = NULL;

    assert(!is_null(pool));
    assert(!is_null(op));

    tmp = realloc(pool->opponents, sizeof(*(pool->opponents)) * (pool->opp_count + 1));
    if(!is_null(tmp)) {
        pool->opponents = (Opponent **)tmp;
        pool->opponents[pool->opp_count] = op;
        pool->opp_count++;
        return 1;
    }

    return 0;
}

void pool_dump(FILE * stream, Pool * pool) {
    int i = 0;
    assert(!is_null(pool));
    
    if(is_null(stream)) {
        stream = stdout;
    }

    fprintf(stream, "<POOL %d>\n", pool->id);
    fprintf(stream, "<Opponents %d>\n", pool->opp_count);
    for(i = 0; i < pool->opp_count; i++) {
        if(!is_null(pool->opponents[i])) {
            fprintf(stream, "\t");
            any_dump(stream, pool->opponents[i]);
        }
    }
    fprintf(stream, "</Opponents>\n");
    fprintf(stream, "<Meetings %d>\n", pool->meet_count);
    for(i = 0; i < pool->meet_count; i++) {
        if(!is_null(pool->ordered[i])) {
            fprintf(stream, "\t");
            any_dump(stream, pool->ordered[i]);
        }
    } 
    fprintf(stream, "</Meetings>\n");
    fprintf(stream, "</POOL>\n");

    return;
}

void * pool_free(Pool * pool) {
    int i = 0;

    assert(!is_null(pool));

    if(!is_null(pool->meetings)) {
        for(i = 0; i < pool->meet_count; i++) {
            if(!is_null(pool->meetings[i])) {
                pool->meetings[i] = any_free(pool->meetings[i]);
            }
        }

        pool->meet_count = 0;
        null(pool->meetings);
    }
    if(!is_null(pool->ordered)) {
        null(pool->ordered);
    }
    if(!is_null(pool->opponents)) {
        for(i = 0; i < pool->opp_count; i++) {
            if(!is_null(pool->opponents[i])) {
                pool->opponents[i] = any_free(pool->opponents[i]);
            }
        }
        pool->opp_count = 0;
        null(pool->opponents);
    }

    null(pool);
    return NULL;
}

