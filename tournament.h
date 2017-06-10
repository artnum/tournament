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
#ifndef TOURNAMENT_H__
#define TOURNAMENT_H__

#define MAX_OPPONENT_NAME    50

#define TOURNAMENT_TYPE_POOL        0xA001
#define TOURNAMENT_TYPE_OPPONENT    0xA002
#define TOURNAMENT_TYPE_MEETING     0xA003

#define TOURNAMENT_SORT_NOROW       1

#ifndef is_null
#define is_null(A)  ((A) == NULL)
#endif /* is_null */

#ifndef null
#define null(A)     free(A); (A) = NULL;
#endif /* null */

#ifndef $
#define $(A)        ((A) = calloc(1, sizeof(*(A))))
#endif /* $ */

#ifndef $$
#define $$(B, A)    ((A) = calloc((B), sizeof(*(A))))
#endif /* $$ */

#include <stdio.h>
#include <assert.h>

typedef struct {
    unsigned short _type; /* must be first in struct */
    unsigned int id;
    char * name;
    void * any;
    void * sort; /* hook for sorting function to attach data if needed */
} Opponent;

typedef struct {
    unsigned short _type; /* must be first in struct */
    unsigned int id;
    unsigned int planned;
    
    Opponent * opponents[2];
    int white;
    int blue;
    int winner;
    
    void * any;
    void * next;
} Meeting;

typedef struct {
    unsigned short _type; /* must be first in struct */
    unsigned int id;
    unsigned int sorting; /* which sort to apply */
    unsigned int randomize; /* randomize first */
    Meeting ** meetings;
    Meeting ** ordered;
    size_t meet_count;
    Opponent ** opponents;
    size_t opp_count;
} Pool;

typedef struct {
    unsigned short _type; /* Must be first */
    unsigned int id;
}

/* Free anything based on first unsigned int of the struct */
void * any_free(void *);
void any_dump(FILE * stream, void * any);


/* *** Pool function *** */
Pool * pool_init(unsigned int);
int pool_add(Pool *, Opponent *);
void * pool_free(Pool *);
void pool_dump(FILE *, Pool *);

/* *** Opponent function *** */
Opponent * opponent_init(unsigned int, char *);
void * opponent_free(Opponent *);
void opponent_dump(FILE *, Opponent *);

/* *** Meeting function *** */
Meeting * meeting_init(unsigned int, Opponent *, Opponent *);
void meeting_dump(FILE *, Meeting *);
void * meeting_free(Meeting *);
void meeting_make_pool(Pool *);

/* *** ordering function *** */
void order_norow(Pool *);
void order_serie(Pool *);

#endif /* TOURNAMENT_H__ */
