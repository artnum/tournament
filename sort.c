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
#include <stdlib.h>
#include <stdio.h>
#include "tournament.h"

#define CMP_OPP(A, B) ( \
         ((A)[0]->id == (B)[0]->id)   ||\
         ((A)[0]->id == (B)[1]->id)   ||\
         ((A)[1]->id == (B)[0]->id)   ||\
         ((A)[1]->id == (B)[1]->id)   \
        )

/* This is the most simple, just try to avoid having a fighter fighting twice in a row */
void order_norow(Pool * pool) {
    int i = 0, must = 0, ordered = 0;
    Meeting * current = NULL;

    assert(!is_null(pool));

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
                        break;
                    }
                }
            }
            if(i >= pool->meet_count) { must = 1; }
        } while(ordered < pool->meet_count);
    }
}
