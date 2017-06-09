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
#ifndef TOURNAMENT_H__
#define TOURNAMENT_H__

#define MAX_OPPONENT_NAME    50

#define TOURNAMENT_TYPE_POOL        0xA001
#define TOURNAMENT_TYPE_OPPONENT    0xA002

#ifndef is_null
#define is_null(A)  ((A) == NULL)
#endif /* is_null */

#ifndef null
#define null(A) free(A); (A) = NULL;
#endif /* null */


#include <stdio.h>

typedef struct {
    unsigned short _type; /* must be first in struct */
    unsigned int id;
    unsigned int count;
    char * name;
    void * any;
} Opponent;

typedef struct {
    unsigned short _type; /* must be first in struct */
    unsigned int id;
    Opponent * white;
    Opponent * blue;
    void * any;

    void * next;
} Meeting;

typedef struct {
    unsigned short _type; /* must be first in struct */
    unsigned int id;
    Meeting * meetings;
    Opponent ** opponents;
    size_t opp_count;
} Pool;

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

#endif /* TOURNAMENT_H__ */
