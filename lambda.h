#pragma once
#ifndef LAMBDA_INCLUDED_H
#define LAMBDA_INCLUDED_H

#if defined(__GNUC__)
#define _PURE __attribute__((pure))

  /* Expresión lambda que retorna una función */
#define lambda(_RETURN_TYPE, _PARAMS, ...) \
  __extension__ ( {_RETURN_TYPE _PURE _LAMBDA  _PARAMS { __VA_ARGS__; } \
  _LAMBDA; } )

#define lambda1(_RETURN_TYPE, _PARAMS, ...) \
  __extension__ ( {_RETURN_TYPE _PURE _LAMBDA1 _PARAMS { __VA_ARGS__; }  \
  _LAMBDA1;} )

#define lambda2(_RETURN_TYPE, _PARAMS, ...) \
  __extension__ ( {_RETURN_TYPE _PURE _LAMBDA2 _PARAMS { __VA_ARGS__; }  \
  _LAMBDA2;} )

    // Podemos definir un tipo para cada función y declararla
typedef char   (*C_FPTR_t)(char);
typedef short  (*S_FPTR_t)(short);
typedef int    (*I_FPTR_t)(int);
typedef long   (*L_FPTR_t)(long);
typedef long long   (*LL_FPTR_t)(long long);
typedef float  (*F_FPTR_t)(float);
typedef double (*D_FPTR_t)(double);
typedef long double (*LD_FPTR_t)(long double);

/* ver si usando __type__of__  __auto__type se puede hacer compse genérico */
int cn (I_FPTR_t f, int ntimes, int x);
//I_FPTR_t componer(I_FPTR_t f, I_FPTR_t g)
L_FPTR_t componer (L_FPTR_t f, L_FPTR_t g);

I_FPTR_t _PURE i_componer (I_FPTR_t f, I_FPTR_t g);

//int (*compose( int (*f)(int), int (*g)(int) ) ) (int)
int _PURE ( *i_compose( int (*f)(int), int (*g)(int) ) ) (int);

// f(f(f(f(...(f(x))...)))), f aplicado n veces
L_FPTR_t _PURE autocall (L_FPTR_t f);

// f(f(f(f(...(f(x))...)))), f aplicado n veces
I_FPTR_t _PURE i_aplicar (I_FPTR_t f, int ntimes);

// f(f(f(f(...(f(x))...)))), f aplicado n veces
L_FPTR_t _PURE aplicar (L_FPTR_t f, int ntimes);

int _PURE ( *i_apply (int (*f)(int), int ntimes) ) (int);

#define eval(_FUNCNAME, ...) \
  ((*_FUNCNAME)(__VA_ARGS__))

#define call(_FUNCNAME, ...) \
  ((*i_apply)(_FUNCNAME, 1)(__VA_ARGS__))

#endif  // __GNUC__

#endif
