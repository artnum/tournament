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
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tournament.h"

#define CMP_OPP(A, B) ( \
         ((A)[0]->id == (B)[0]->id)   ||\
         ((A)[0]->id == (B)[1]->id)   ||\
         ((A)[1]->id == (B)[0]->id)   ||\
         ((A)[1]->id == (B)[1]->id)   \
        )

void unplan_meetings(Pool * pool) {
    int i = 0;
    assert(! is_null(pool));
    
    for(i = 0; i < pool->meet_count; i++) {
        pool->meetings[i]->planned = 0;
    }

    return;
}

void randomize_meetings(Pool * pool) {
    int i = 0, j = 0, r = 0;
    Meeting * current = NULL;

    assert(!is_null(pool));

    for(r = random() % pool->meet_count; r >= 0; r--) {
        for(i = 0; i < pool->meet_count; i++) {
            j = random() % pool->meet_count;
            current = pool->meetings[i];
            pool->meetings[i] = pool->meetings[j];
            pool->meetings[j] = current;
        }  
    }
}

/* This is the most simple, just try to avoid having a fighter fighting twice in a row */
void order_norow(Pool * pool) {
    int i = 0, must = 0, ordered = 0;
    Meeting * current = NULL;

    assert(!is_null(pool));
   
    unplan_meetings(pool); 
    if(pool->randomize) { randomize_meetings(pool); }

    if(!is_null($$(pool->meet_count, pool->ordered))) {
        do {
            for(i = 0; i < pool->meet_count; i++) {
                current = pool->meetings[i];
                if(!current->planned) {
                    if(ordered == 0 || must || !CMP_OPP(current->opponents,
                                pool->ordered[ordered - 1]->opponents)) {
                        pool->ordered[ordered] = current;
                        current->planned = 1;
                        ordered++;
                        must = 0;
                        break;
                    }
                }
            }
            if(i >= pool->meet_count) { must = 1; }
        } while(ordered < pool->meet_count);
    }
}

/* Sort in a way that there's no meeting twice in a row but try to limit waiting time
   by making series of meetings so everyone will have done, at least, one meeting 
   after the first round of meeting (a round is NUMBER_OF_OPPONENTS / 2). i
 */
void order_serie(Pool * pool) {
    int i = 0, serie = 0, ordered = 0, j = 0;
    unsigned int * meet_counter;
    Meeting * current = NULL;
    Meeting ** series = NULL;

    assert(!is_null(pool));

    if(is_null($$(pool->opp_count, meet_counter))) {
        return;
    }

    if(is_null($$(pool->meet_count, pool->ordered))) {
        null(meet_counter); 
        return;
    }

    if(is_null($$(pool->meet_count, series))) {
        null(meet_counter);
        return;
    }

    unplan_meetings(pool); 
    if(pool->randomize) { randomize_meetings(pool); }

    for(i = 0; i < pool->opp_count; i++) {
        pool->opponents[i]->sort = meet_counter + i;
        *((int *)pool->opponents[i]->sort) = 0;
    }

    do {
        j = 0;
        memset(series, 0, pool->meet_count);
        for(i = 0; i < pool->meet_count; i++) {
            current = pool->meetings[i];
            if(!current->planned) {
                if((*((int *)current->opponents[0]->sort) == serie || 
                    *((int *)current->opponents[1]->sort) == serie)) {
                    series[j] = current;
                    j++;
                }
            }
        }
        if(j == 0) {
            serie++;
        }
        current = NULL;
        for(i = 0; i < j; i++) {
            current = series[i];
            if(ordered == 0 || j < 2 || !CMP_OPP(current->opponents,
                        pool->ordered[ordered - 1]->opponents)) {
                pool->ordered[ordered] = current;
                current->planned = 1;
                (*(int *)current->opponents[0]->sort)++;
                (*(int *)current->opponents[1]->sort)++;
                ordered++;
                break;
            }
        }
    } while(ordered < pool->meet_count);

    null(series);
    null(meet_counter);

    for(i = 0; i < pool->opp_count; i++) {
        pool->opponents[i]->sort = NULL;
    }
    return;
}
