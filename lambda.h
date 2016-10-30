#ifndef LAMBDA_INCLUDED_H
#define LAMBDA_INCLUDED_H

//static int lcount=0;
  /* Expresión lambda que retorna una función */
#define lambda(FUNCTYPE, PARAMS, ...) \
  ( {FUNCTYPE __Lambda__ PARAMS { __VA_ARGS__; } \
  __Lambda__;} )

#define lambda1(FUNCTYPE, PARAMS, ...) \
  ( {FUNCTYPE __Lambda__ PARAMS { __VA_ARGS__; } \
  __Lambda__;} )

#define lambda2(FUNCTYPE, PARAMS, ...) \
  ( {FUNCTYPE __Lambda__ PARAMS { __VA_ARGS__; } \
  __Lambda__;} )

#define call(FUNCNAME, ...) \
  ((*apply)(FUNCNAME, 1)(__VA_ARGS__))

#define eval(FUNCNAME, ...) \
  ((*FUNCNAME)(__VA_ARGS__))

    // Podemos definir un tipo para la función y declararla
typedef char   (*C_FPTR_t)(char);
typedef short  (*S_FPTR_t)(short);
typedef int    (*I_FPTR_t)(int);
typedef long   (*L_FPTR_t)(long);
typedef float  (*F_FPTR_t)(float);
typedef double (*D_FPTR_t)(double);

#endif
