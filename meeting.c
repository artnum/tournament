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
#include <stdio.h>
#include <stdlib.h>
#include "tournament.h"



Meeting * meeting_init(unsigned int id, Opponent * opp1, Opponent * opp2) {
    Meeting * meeting = NULL;

    assert(!is_null(opp1));
    assert(!is_null(opp2));

    if(!is_null($(meeting))) {
        meeting->_type = TOURNAMENT_TYPE_MEETING;
        meeting->id = id;
        meeting->planned = 0;
        meeting->opponents[0] = opp1;
        meeting->opponents[1] = opp2;
        meeting->white = random() % 2; 
        meeting->blue = ! meeting->white;
        meeting->winner = -1;
        meeting->any = NULL;
        meeting->next =NULL;
    }

    return meeting;
}

void meeting_dump(FILE * stream, Meeting * meeting) {
    assert(!is_null(meeting));

    if(is_null(stream)) {
        stream = stdout;
    }
    
    fprintf(stream, "%03d %s (white) vs %s (blue)\n", meeting->id, 
            meeting->opponents[meeting->white]->name, meeting->opponents[!meeting->white]->name);
}   

void * meeting_free(Meeting * meeting) {
    assert(!is_null(meeting));

    null(meeting);
    
    return NULL;
}

/* Make pool fight (everyone vs everyone) */
void meeting_make_pool(Pool * pool) {
    int meetings_number = 0;
    int i = 0, j = 0, c = 0;

    assert(!is_null(pool));

    /* Careful with that axe eugene ... divide by 2 will result in floating
       point number but the whole will always give an integer */
    meetings_number = (pool->opp_count - 1) * ((double)pool->opp_count / 2);
    printf("%d\n", meetings_number);
    if(meetings_number > 0) {
        if(!is_null($$(meetings_number, pool->meetings))) {
            pool->meet_count = meetings_number;
            c = 0;
            for(i = 0; i < pool->opp_count; i++) {
                for(j = i+1; j < pool->opp_count; j++) {
                    fprintf(stdout, "%d - %d, %d\n", i , j, c);
                    pool->meetings[c] = meeting_init(c, 
                            pool->opponents[i], pool->opponents[j]); 
                    c++; /* lol */
                }
            }          
        }
    }
}
