#pragma once
#ifndef LAMBDA_INCLUDED_H
#define LAMBDA_INCLUDED_H

#if defined(__GNUC__)

  /* Expresión lambda que retorna una función */
#define lambda(__RETURN_TYPE, __PARAMS, ...) \
  __extension__ ( {__RETURN_TYPE __attribute__((pure)) __LAMBDA __PARAMS { __VA_ARGS__; } \
  __LAMBDA;} )


#define lambda1(__RETURN_TYPE, ...) \
  __extension__ ( {__RETURN_TYPE __attribute__((pure)) __LAMBDA1__ __VA_ARGS__  \
  __LAMBDA1__;} )

#define lambda2(__RETURN_TYPE, PARAMS, ...) \
  __extension__ ( {__RETURN_TYPE __attribute__((pure)) __LAMBDA2__ PARAMS {__VA_ARGS__}  \
  __LAMBDA2__;} )


    // Podemos definir un tipo para cada función y declararla
typedef char   (*C_FPTR_t)(char);
typedef short  (*S_FPTR_t)(short);
typedef int    (*I_FPTR_t)(int);
typedef long   (*L_FPTR_t)(long);
typedef long long   (*VL_FPTR_t)(long long);
typedef float  (*F_FPTR_t)(float);
typedef double (*D_FPTR_t)(double);

/* ver si usando __type__of__  __auto__type se puede hacer compse genérico */
int cn (I_FPTR_t f, int n, int x);
//I_FPTR_t componer(I_FPTR_t f, I_FPTR_t g)
L_FPTR_t componer (L_FPTR_t f, L_FPTR_t g);

I_FPTR_t PURE i_componer (I_FPTR_t f, I_FPTR_t g);

//int (*compose( int (*f)(int), int (*g)(int) ) ) (int)
int PURE ( *i_compose( int (*f)(int), int (*g)(int) ) ) (int);

// f(f(f(f(...(f(x))...)))), f aplicado n veces
L_FPTR_t PURE autocall (L_FPTR_t f);

// f(f(f(f(...(f(x))...)))), f aplicado n veces
I_FPTR_t PURE i_aplicar (I_FPTR_t f, int nveces);

// f(f(f(f(...(f(x))...)))), f aplicado n veces
L_FPTR_t PURE aplicar (L_FPTR_t f, int nveces);


int PURE ( *i_apply (int (*f)(int), int ntimes) ) (int);

#define eval(FUNCNAME, ...) \
  ((*FUNCNAME)(__VA_ARGS__))

#define call(FUNCNAME, ...) \
  ((*i_apply)(FUNCNAME, 1)(__VA_ARGS__))

#endif  // __GNUC__

#endif
