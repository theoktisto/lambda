#include <stdio.h>
#include "hoare.h"
#include "lambda.h"

/*
 * http://stackoverflow.com/questions/10758811/c-syntax-for-functions-returning-function-pointers
 * http://cdecl.ridiculousfish.com/
 */


int cn (I_FPTR_t f, int ntimes, int x)
{
    if (ntimes==0)
        return x;
    return cn(f, ntimes-1, f(x));
}

//I_FPTR_t componer(I_FPTR_t f, I_FPTR_t g)
I_FPTR_t i_componer (I_FPTR_t f, I_FPTR_t g)
{
   return lambda (int, (int x), return f(g(x)) );
}

//I_FPTR_t componer(I_FPTR_t f, I_FPTR_t g)
L_FPTR_t componer (L_FPTR_t f, L_FPTR_t g)
{
   return lambda (long, (long x), return f(g(x)) );
}

// int (*f) (int)
//int (*compose( int (*f)(int), int (*g)(int) ) ) (int)
int (*i_compose( int (*f)(int), int (*g)(int) ) ) (int)
{
   return lambda (int, (int x), return f(g(x)) );
}

// f(f(f(f(...(f(x))...)))), f aplicado n veces

L_FPTR_t _PURE autocall (L_FPTR_t f)
{
    return componer(f, f);
}


// f(f(f(f(...(f(x))...)))), f aplicado n veces
L_FPTR_t aplicar (L_FPTR_t f, int nveces)
{
    if (nveces==0)
        return lambda(int, (int x), return x); // Identidad
    if (nveces==1)
        return f;
    return componer(f, aplicar(f, nveces-1));
}

// f(f(f(f(...(f(x))...)))), f aplicado n veces
I_FPTR_t i_aplicar (I_FPTR_t f, int nveces)
{
    if (nveces==0)
        return lambda(int, (int x), {return x;} ); // Identidad
    if (nveces==1)
        return f;
    return i_componer(f, aplicar(f, nveces-1));
}

// f(f(f(f(...(f(x))...)))), f aplicado n veces
L_FPTR_t l_aplicar (L_FPTR_t f, int nveces)
{
    if (nveces==0)
        return lambda(long, (long x), {return x;} ); // Identidad
    if (nveces==1)
        return f;
    return componer(f, aplicar(f, nveces-1));
}

int ( *i_apply (int (*f)(int), int ntimes) ) (int)
{
    if (ntimes==0)
        return lambda(int, (int x), return x);
    if (ntimes==1)
        return f;
    return i_compose(f, i_apply(f, ntimes-1));
}

//extern void (*signal(int, void (*)(int)))(int);
/*
 * To declare a function returning a pointer to a function, first write
 * the declaration of the function type to be returned. For example,
 * the type of a function accepting two int and returning an int is:

 int function(int, int)
 * Now, make it a pointer to a function by inserting *. Since the precedence
 * gets in the way (the parenthesized function parameters will bind more
 * tightly to the identifier than the * does), we have to insert parentheses too:

 int (*function)(int, int)
 * Finally, replace the identifier with the declarator of the factory function.
 * (For this purpose, the declarator is the function identifier and the parameter
 * list.) In this case, we replace function with factory(int). This gives:

 int (*factory(int))(int, int)
 * This declares a function, factory(int), that returns something that fits
 * the spot where xxx is in int (*xxx)(int, int). What fits in that spot is
 * a pointer to a function taking two int and returning an int.
 */

