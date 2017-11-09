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
#include <string.h>
#include <time.h>
#include "tournament.h"

int main(int argc, char * argv[]) {
    int i = 0;
    const char * names[] = { "A", "B", "C", "D", "E", NULL, "F", "G",  "H", "I",   NULL };
    Tournament * T;
    Opponent * opp;
    Pool * pool;

    T = tournament_init("Tournament", 5);

    pool = pool_init(0);
/*    pool->randomize = 1;*/
    if(! is_null(pool)) {
        for(i = 0; !is_null(names[i]); i++) {
            opp = opponent_init(i, (char *)names[i]);
            if(!is_null(opp)) {
                printf("Add %s\n", opp->name);
                pool_add(pool, opp);
            }
        }

        /* Random must be initialize to give random white/blue position */
        srandom(time(NULL));

        meeting_make_pool(pool);
       
        order_serie(pool);
        any_dump(NULL, pool);
        
        order_norow(pool);
        any_dump(NULL, T);
        any_dump(NULL, pool);
        any_free(pool);
        any_free(T);   
    }

    return 0;
}
