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
#include <stdlib.h>
#include "tournament.h"

/* Return always NULL */
void * any_free(void * any) {
  assert(!is_null(any));

  switch(*(unsigned short *)any) {
    case TOURNAMENT_TYPE_OPPONENT: opponent_free(any); break;
    case TOURNAMENT_TYPE_POOL: pool_free(any); break;
    case TOURNAMENT_TYPE_MEETING: meeting_free(any); break;
    default: null(any); break;
  }

  return NULL; 
}

void any_dump(FILE * stream, void * any) {
    assert(!is_null(any));

    if(is_null(stream)) {
        stream = stdout;
    }

    switch(*(unsigned short *)any) {
        case TOURNAMENT_TYPE_OPPONENT: opponent_dump(stream, any); break;
        case TOURNAMENT_TYPE_POOL: pool_dump(stream, any); break;
        case TOURNAMENT_TYPE_MEETING: meeting_dump(stream, any); break;
        default: printf("%p\n", any); break;
    }
}
