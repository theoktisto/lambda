#include <stdio.h>
#include "hoare.h"
#include "lambda.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef __GNUC__
    #include <setjmp.h>
    struct LOOP_T; typedef struct LOOP_T LOOP;
    struct LOOP_T {
        jmp_buf b; LOOP * p;
    } LOOP_base, *LOOP_V = &LOOP_base;
    #define FOR(I, C, A, ACT) (LOOP_V = &(LOOP){ .p = LOOP_V }, \
                               (I), setjmp(LOOP_V->b), \
                               ((C) ? ((ACT),(A), longjmp(LOOP_V->b, 1), 0) : 0), \
                               LOOP_V = LOOP_V->p, 0)
#else
    #define FOR(I, C, A, ACT) (({for(I;C;A){ACT;}}), 0)    // GNU version
#endif

typedef struct List {
    struct List * nx; char val[];
} List;

typedef struct {
    int _1, _2, _3;
} Triple;

#define SEQUENCE(OUT, SETS, PRED) (SEQUENCE_var=&(ITERATOR){.l=NULL,.p=SEQUENCE_var}, \
                              M_FFOLD(((PRED)?APPEND(OUT):0),M_ID SETS), \
                              SEQUENCE_var->p->old=SEQUENCE_var->l,SEQUENCE_var=SEQUENCE_var->p,SEQUENCE_var->old)

typedef struct ITERATOR {
    List *l, *old;
    struct ITERATOR *p;
} ITERATOR;

ITERATOR *FE_var, SEQUENCE_base, *SEQUENCE_var = &SEQUENCE_base;

#define FOR_EACH(V, T, L, ACT) (FE_var=&(ITERATOR){.l=(L),.p=FE_var}, \
                                FOR((V) = *(T*)&FE_var->l->val, FE_var->l?((V)=*(T*)&FE_var->l->val,1):0, \
                                FE_var->l=FE_var->l->nx, ACT), FE_var=FE_var->p)

#define M_FFOLD(ID, ...) M_ID(M_CONC(M_FFOLD_, M_NARGS(__VA_ARGS__)) (ID, __VA_ARGS__))
#define FORSET(V, T, L) V, T, L
#define APPEND(T, val) (SEQUENCE_var->l?listAppend(SEQUENCE_var->l,sizeof(T),&val):(SEQUENCE_var->l=listNew(sizeof(T),&val)))

#define M_FFOLD_1(ID, E) FOR_EACH M_IDP(FORSET E, ID)
#define M_FFOLD_2(ID, E, ...) FOR_EACH M_IDP(FORSET E, M_FFOLD_1(ID, __VA_ARGS__))
#define M_FFOLD_3(ID, E, ...) FOR_EACH M_IDP(FORSET E, M_FFOLD_2(ID, __VA_ARGS__))  //...

#define M_NARGS(...) M_NARGS_(__VA_ARGS__, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)
#define M_NARGS_(_10, _9, _8, _7, _6, _5, _4, _3, _2, _1, N, ...) N
#define M_CONC(A, B) M_CONC_(A, B)
#define M_CONC_(A, B) A##B
#define M_ID(...) __VA_ARGS__
#define M_IDP(...) (__VA_ARGS__)

#define INT_RANGE(f, t) int,intRangeList(f, t)
#define T(a, b, c) Triple,((Triple){(a),(b),(c)})

List * listNew(int sz, void *val) {
    List *l = malloc(sizeof(List) + sz);
    l->nx = NULL;
    memcpy(l->val, val, sz);
    return l;
}

List *listAppend(List *l, int sz, void *val) {
    while (l->nx)
        { l = l->nx; }
    l->nx = listNew(sz, val);
    return l;
}

List *intRangeList(int f, int t) {
    List *l = listNew(sizeof f, &f), *e = l;
    for (int i = f + 1; i <= t; i ++)
        { e = e->nx = listNew(sizeof i, &i); }
    return l;
}

int main(void) {
    volatile int x, y, z;
    const int n = 50;

    List * pTriples = SEQUENCE( T(x, y, z),
                                ( (x, INT_RANGE(1, n)),
                                  (y, INT_RANGE(x, n)),
                                  (z, INT_RANGE(y, n)) ),
                                (x*x + y*y == z*z)
                              );
    List * seq = SEQUENCE( T(x, y, z),
                                ( (x, INT_RANGE(1, n)),
                                  (y, INT_RANGE(x, x)),
                                  (z, INT_RANGE(y, y)) ),
                                (x*x & 1 == 1)
                              );

    volatile Triple t;
    FOR_EACH(t, Triple, pTriples,  printf("%d, %d, %d\n", t._1, t._2, t._3)  );
    volatile Triple tt;
    FOR_EACH(tt, Triple, seq,  printf("%d, %d, %d\n", tt._1, tt._2, tt._3)  );

    return 0;
}
