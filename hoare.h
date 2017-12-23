/* Para ser usado en Computación I y II.
** Version 1.3 20/12/2017, Elaborado por: Victor Theoktisto
** -- specific C macro (needed for preprocessing!)
** https://www.gnu.org/licenses/gpl-3.0.en.html
** Copyright 2014-2017 Victor Theoktisto   */

#pragma once
#ifndef _HOARE_H_INCLUDED_
#define _HOARE_H_INCLUDED_
// #if defined(__GNUC__)

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Global macros
 * #define _Output(A)    ' '<<#A<<": "<<(A)<<", "
 * #define _Outputnl(A)  ' '<<#A<<": "<<(A)<<";\n"

 * --- Assert during compiling (not run-time) ---
 * CompilerAssert(exp) is designed to provide error checking at
 * compile-time for assumptions made by the programmer at design-time
 * and yet does not produce any run-time code.
 * Example: if (CompilerAssert(sizeof(int)==4)) ... */
#define CompilerAssert(__Predicate) \
  do{ \
    extern char _CompilerAssert[(__Predicate) ? 1 : -1]; \
  }while(0)

    /* Useful definitions */
enum bool {false=0, FALSE=0, true=~0, TRUE=~0};
#define and &&
#define or  ||
#define not !
#define xor ^
#define AND &&
#define OR  ||
#define NOT !
#define XOR ^
#define GLUE(a,b) a##b
#define XPREFIX(s) s
#define PREFIX(a,b) XPREFIX(a)b
#define SUFIX(a,b)  bXPREFIX(a)

#define VERBATIM(s) QUOTE(s)
#define QUOTE(s) #s

    /*--- Compiler warns when the types of x and y are not compatible ---*/
#define ABS(a) \
    ({__auto_type __a = (a); (__a < 0) ? -__a : __a;})
#define MAX(x, y) \
    ({ __auto_type __x=(x); __auto_type __y=(y); \
       (void)(&__x == &__y); (__x > __y) ? __x : __y; })
#define MIN(x, y) \
    ({ __auto_type __x=(x); __auto_type __y=(y); \
       (void)(&__x == &__y); (__x < __y) ? __x : __y; })
#define ODD(n)  ((n)&1)
#define EVEN(n) (!((n)&1))

    /*--- SWAP failsafe for any size ---*/
#define SWAP(__A,__B) \
    do{ \
        __auto_type __T=(__A); (__A)=(__B); (__B)=__T; \
    }while(0)

    /*--- SWAP failsafe for any size memory blocks
     * If sizes are not equal, compiler warns   ---*/
#define MEMSWAP(__A,__B) \
    do{ \
        unsigned char __T[sizeof(__A)==sizeof(__B)? (signed)sizeof(__A): -1]; \
        memcpy( __T, &__B, sizeof(__A)); \
        memcpy(&__B, &__A, sizeof(__A)); \
        memcpy(&__A,  __T, sizeof(__A)); \
    }while(0)

    /*--- Is a number a power of two ---*/
#define ISPOWEROF2(x) (!((x)&((x)-1)))
    /* _NUMCELLS() macro */
#define NUMCELLS(__Arraytype) (sizeof(__Arraytype)/sizeof(*__Arraytype))
    /* Two's complement negation as a macro */
#define ONESCOMPLEMENT(x) ((x)^(~0)))
    /* Two's complement negation as a macro */
#define TWOSCOMPLEMENT(x) (((x)^(~0))+1)
    /* SQUARE() macro, final form */
#define SQUARE(x) (__auto_type __T=(x); __T*__T)
    /* CUBE() macro, final form */
#define CUBE(x) (__auto_type __T=(x); __T*__T*__T)
    /* Fills an integer value with all bits set as 1's, independent of type size */
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
#define pointer(__T)  __typeof__(__T *)
#define array(__T, __N) __typeof__(__T [__N])
#define CREATE(__Storage) (GC_MALLOC(sizeof(__Storage)))
#define NEW(__StoragePtr) (__StoragePtr = GC_MALLOC(sizeof(*__StoragePtr)))
#define NEWARRAY(__DataType, __Dim) (GC_MALLOC(__Dim*sizeof(__DataType)))
#define DELETE(__StoragePtr) (NULL)
#define DESTROY(__StoragePtr) (NULL)

    /*--- General assertion (__Predicate) ---*/
#define _assert(__Predicate) \
     check_assert("Assertion does not hold for", __Predicate)
    /*--- Precondition (__Predicate) ---*/
#define _expects(__Predicate) \
    check_assert("Precondition does not hold for", __Predicate)
    /*--- Postcondition (__Predicate) ---*/
#define _ensures(__Predicate) \
    check_assert("Postcondition does not hold for", __Predicate)
    /*--- Invariant (__Predicate) ---*/
#define _invariant(__Predicate) \
    check_assert("Invariant does not hold for", __Predicate)
    /*--- Precondition (integer expression) ---*/
#define _bounded(__IntExpression) \
    check_assert("Bound does not hold for", (__IntExpression)>=0)

#ifdef NDEBUG
    #define check_assert(__Message, __Predicate) ((void)0)
#else /*--- Not NDEBUG.  ---*/
    #define __check_assert(__Message, __Predicate, __File, __Line)  \
        ((void)printf (">>> At %s:%u:  %s '%s'\n<<< Assertion failed. " \
        "Execution will stop now.\n", __File, __Line, __Message, __Predicate), exit(1), 0)
    #define check_assert(__Message, __Predicate)  \
        ((void)((__Predicate)? 0: __check_assert(__Message, QUOTE(__Predicate), __FILE__, __LINE__)))
#endif /*---  ifdef NDEBUG  ---*/

#endif /*---  ifndef _HOARE_H_INCLUDED_  ---*/
