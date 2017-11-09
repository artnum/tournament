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
#include <string.h>
#include "tournament.h"

Tournament  * tournament_init(char * name, unsigned int weight_gap) {
    Tournament * t = NULL;
    size_t name_len = 0;

    assert(!is_null(name));
    
    if(!is_null($(t))) {
        t->_type = TOURNAMENT_TYPE_TOURNAMENT;
        t->opponents = NULL;
        t->pools = NULL;
        t->weight_gap = weight_gap;
        name_len = strlen(name) + 1;
        if(MAX_OPPONENT_NAME > 0 && name_len > MAX_OPPONENT_NAME) {
            name_len = MAX_OPPONENT_NAME;
        }
        if(is_null($$(name_len, t->name))) {
            null(t);
        } else {
            strncpy(t->name, name, name_len);
            t->name[name_len - 1] = '\0';
        }
    }

    return t;
}

int tournament_add_opp(Tournament * t, void * any) {
}

int tournament_add_pool(Tournament * t, void * any) {
}

int tournament_add(Tournament * t, void * any) {
  assert(!is_null(any));

  switch(*(unsigned short *)any) {
      case TOURNAMENT_TYPE_OPPONENT: return tournament_add_opp(t, any);
      case TOURNAMENT_TYPE_POOL:  return tournament_add_pool(t, any);
  }

  return 0;
}

void * tournament_free(Tournament * t) {
    assert(!is_null(t));

    if(!is_null(t->name)) {
        null(t->name);
    }
    null(t);

    return NULL;
}

void tournament_dump(FILE * stream, Tournament * t) {
    assert(!is_null(t));

    if(is_null(stream)) {
        stream = stdout;
    }

    fprintf(stream, "<TOURNAMENT \"%s\">\n", t->name);
    fprintf(stream, "Weight gap : %d kg\n", t->weight_gap);
    fprintf(stream, "</TOURNAMENT>\n");

    return;
}

/* Return always NULL */
void * any_free(void * any) {
  assert(!is_null(any));

  switch(*(unsigned short *)any) {
    case TOURNAMENT_TYPE_TOURNAMENT: tournament_free(any); break;
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
        case TOURNAMENT_TYPE_TOURNAMENT: tournament_dump(stream, any); break;
        case TOURNAMENT_TYPE_OPPONENT: opponent_dump(stream, any); break;
        case TOURNAMENT_TYPE_POOL: pool_dump(stream, any); break;
        case TOURNAMENT_TYPE_MEETING: meeting_dump(stream, any); break;
        default: printf("%p\n", any); break;
    }
}
