/* Para ser usado en Computación I y II.
** Version 1.24 29/10/2016, Elaborado por: Victor Theoktisto
** -- specific C macro (needed for preprocessing!) */

/* https://www.gnu.org/licenses/gpl-3.0.en.html */

/* Copyright 2014-2016 Victor Theoktisto */

#ifndef _HOARE_H_INCLUDED_
#define _HOARE_H_INCLUDED_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Global macros
#define _Output(A)    ' '<<#A<<": "<<(A)<<", "
#define _Outputnl(A)  ' '<<#A<<": "<<(A)<<";\n"

/* --- Assert during compiling (not run-time) ---
 * CompilerAssert(exp) is designed to provide error checking at
 * compile-time for assumptions made by the programmer at design-time
 * and yet does not produce any run-time code.
 * Example: if (CompilerAssert(sizeof(int)==4)) ... */
#define CompilerAssert(Predicate) extern char _CompilerAssert[(Predicate)?1:-1]

    /* Useful definitions */
enum bool {false=0, FALSE=0, true=~0, TRUE=~0};
#define and &&
#define  or ||
#define not !
#define xor ^
#define AND &&
#define  OR ||
#define NOT !
#define XOR ^
#define GLUE(a,b) a##b
#define XPREFIX(s) s
#define PREFIX(a,b) XPREFIX(a)b

#define PURE __attribute__((pure))
#define VERBATIM(s) QUOTE(s)
#define QUOTE(s) #s

#define ABS(a) ({__auto_type __a = (a); __a < 0 ? -__a : __a;})
// Compiler warns when the types of x and y are not compatible
#define MAX(x, y) ({ \
    __auto_type __x = (x); __auto_type __y = (y);  \
    (void) (&__x == &__y); __x > __y ? __x : __y; })
#define MIN(x, y) ({ \
    __auto_type __x = (x); __auto_type __y = (y);  \
    (void) (&__x == &__y); __x < __y ? __x : __y; })
#define ODD(n) ((n)&1)
#define EVEN(n) (!((n)&1))

    /*--- SWAP failsafe for any size ---*/
#define SWAP(A,B) \
    do{ \
        __auto_type t=A; A=B; B=t; \
    }while(0)

#define SWAPMEM(A,B) \
    do{ \
        unsigned char tt[sizeof(A)==sizeof(B)?(signed)sizeof(A):-1]; \
        memcpy(tt, &B, sizeof(A)); \
        memcpy(&B, &A, sizeof(A)); \
        memcpy(&A, tt, sizeof(A)); \
    }while(0)

    /*--- Is a number a power of two ---*/
#define ISPOWEROF2(x) (!((x)&((x)-1)))
    /* _NUMCELLS() macro */
#define NUMCELLS(_arraytype) (sizeof(_arraytype)/sizeof(*_arraytype))
    /* Two's complement negation as a macro */
#define ONESCOMPLEMENT(x) ((x)^(~0)))
    /* Two's complement negation as a macro */
#define TWOSCOMPLEMENT(x) (((x)^(~0))+1)
    /* SQUARE() macro, final form */
#define SQUARE(x) (__auto_type t=(x); t*t)
    /* fills an integer value with ONES independent of type size */
#define ALLONES ~0

    /* Distinguishing between ascii chars and wchar chars:  */
#if UNICODE
    #define dchar wchar_t
    #define TEXT(s) L##s
#else
    #define dchar char
    #define TEXT(s) s
#endif

    /* Defining macros for memory allocation */
    /* redefine malloc(sizeof(Storage)) as CREATE(Storage) using GC_MALLOC */
    /* free is optional */
#define CREATE(__Storage) (GC_MALLOC(sizeof(__Storage)))
#define NEW(__PointerVar) (__PointerVar=GC_MALLOC(sizeof(*__PointerVar)))
#define NEWARRAY(__Dim,__DataType) (GC_MALLOC(__Dim*sizeof(__DataType)))
#define DELETE(__PointerVar) (NULL)
#define DESTROY(__ReservedStoragePtr) (NULL)

    /* General assertion (Predicate) */
#define _assert(Predicate) \
     check_assert("Assertion does not hold for",Predicate)
    /* Precondition (Predicate) */
#define _pre(Predicate) \
    check_assert("Precondition does not hold for",Predicate)
    /* Postcondition (Predicate) */
#define _post(Predicate) \
    check_assert("Postcondition does not hold for",Predicate)
    /* Invariant (Predicate) */
#define _inv(Predicate) \
    check_assert("Invariant does not hold for",Predicate)
    /* Precondition (integer expression) */
#define _bound(IntExpression) \
    check_assert("Bound does not hold for",(IntExpression)>=0)

#ifdef NDEBUG
    #define check_assert(Message,Predicate) ((void)0)
#else /* Not NDEBUG.  */
    #define check_assert(Message,Predicate)  \
    ((void)((Predicate)?0:__check_assert(Message,QUOTE(Predicate),__FILE__,__LINE__)))
//    ((void)((Predicate)?0:__check_assert(Message,#Predicate,__FILE__,__LINE__)))
    #define __check_assert(Message,Predicate,File,Line) \
    ((void)printf (">>> At %s:%u:  %s '%s'\n<<< Assertion failed. " \
    "Execution will stop now.\n",File,Line,Message,Predicate),exit(1),0)

#endif  /* NDEBUG */
#endif /* ifndef _HOARE_H_INCLUDED_ */
