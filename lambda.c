#include <stdio.h>
#include "hoare.h"
#include "lambda.h"

/*
 * http://stackoverflow.com/questions/10758811/c-syntax-for-functions-returning-function-pointers
 * http://cdecl.ridiculousfish.com/
 *                                                  */

int cn (I_FPTR_t f, int n, int x)
{
    if (n==0) return x;
    return cn(f, n-1, f(x));
}

//I_FPTR_t componer(I_FPTR_t f, I_FPTR_t g)
I_FPTR_t PURE componer (I_FPTR_t f, I_FPTR_t g)
{
   return lambda (int, (int x), return f(g(x)) );
}

// int (*f) (int)
//int (*compose( int (*f)(int), int (*g)(int) ) ) (int)
int PURE ( *compose( int (*f)(int), int (*g)(int) ) ) (int)
{
   return lambda (int, (int x), return f(g(x)) );
}

// f(f(f(f(...(f(x))...)))), f aplicado n veces
I_FPTR_t PURE aplicar (I_FPTR_t f, int nveces)
{
    if (nveces==0)
        return lambda(int, (int x), return x); // Identidad
    if (nveces==1)
        return f;
    return componer(f, aplicar(f, nveces-1));
}

int PURE ( *apply (int (*f)(int), int ntimes) ) (int)
{
    if (ntimes==0)
        return lambda(int, (int x), return x);
    if (ntimes==1)
        return f;
    return compose(f, apply(f, ntimes-1));
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

int main()
{
    int xx = 5;
    int yy = 13;
    char aa[] = "0123456789";
    char bb[] = "abcdefghij";
    SWAP(xx,yy);
    printf("xx %i, yy %i\n",xx,yy);
    SWAPMEM(aa,bb);
    printf("aa %s, bb %s\n",aa,bb);
    int (*i_componer_f_gx) (I_FPTR_t, I_FPTR_t, int); // Componer funciones enteras
        // O también hacer la declaración directamente de componer funciones floats
    float (*f_componer_f_gx) (float (*)(float), float (*)(float), float);

    int (*succ)(int)    = lambda( int, (int x), return x+1 );
    int (*pred) (int)   = lambda( int, (int x), return x-1 );
    int (*r)(int, int) = lambda( int, (int x, int y), _pre(y!=0); return x/y );
    int (*cero)(void)  = lambda2(int, (void), return 0);

    printf( "result  = %i\n", r( succ(7), pred(3) ) );

        // Definimos la composición de funciones (f.g)(x) = f(g(x)) [enteras]
    i_componer_f_gx = lambda( int,
                              ( I_FPTR_t f, I_FPTR_t g, int x ),
                              return f(g(x)) );
    printf( "f(g(x)) = %i (ints)\n",
            i_componer_f_gx( lambda( int, (int x), return x+x ),
                             lambda( int, (int x), return x*x ),
                             6) );
        // Definimos la composición de funciones (f.g)(x) = f(g(x)) [floats]
    f_componer_f_gx = lambda( float,
                              ( float (*f)(float), float (*g)(float), float x ),
                              return f(g(x)) );
    printf( "f(g(x)) = %f (floats)\n",
            f_componer_f_gx( lambda( float, (float x), return x*x ),
                             lambda( float, (float x), return x+x ),
                             4.0f) );
    printf( "f(g(x)) = %f (floats)\n",
            f_componer_f_gx( lambda( float, (float x), return x*x ),
                             lambda( float, (float x), return x+x ),
                             4.0f) );
    printf( "f(g(x)) = %f (floats)\n",
            f_componer_f_gx( lambda( float, (float x), return x+x ),
                             lambda( float, (float x), return x*x ),
                             2.0f) );

    I_FPTR_t (*componer)(I_FPTR_t, I_FPTR_t) = lambda( I_FPTR_t,
                                                (I_FPTR_t f, I_FPTR_t g),
                                                return lambda (int, (int x), return f(g(x)) ) );
 //                           (lambda( int, (int x), return x*x ), lambda( int, (int x), return x+x ) );

    I_FPTR_t (*ff)(I_FPTR_t) = lambda (I_FPTR_t,
                                       (I_FPTR_t h),
                                       return h );
 //                                              (lambda( int, (int x), return x*x ) );
    I_FPTR_t (*hh)(I_FPTR_t) = lambda (I_FPTR_t,
                                       (I_FPTR_t h),
                                       return h );

    printf("z=%i\n",({int z (int x) { return x+1;} z;})(5));

//    int fun = ff(r)(3);
    printf( "call = %i (ints)\n",  call( ff(lambda( int, (int x), return 2*x)), 5) );
    printf( "apply = %i (ints)\n",  apply( ff( lambda( int, (int x), return 2*x) ), 3)(4) );
    printf( "val = %i (ints)\n", lambda( int, (int x), return 2*x )(1) );
    printf( "val = %i (ints)\n", lambda( int, (int x), return 2*x )(3) );
    printf( "val = %i (ints)\n\n", eval(lambda( int, (int x), return 2*x), 3) );

    printf( "cn(x) = %i (ints)\n",   cn(succ,5,3));
    printf( "ff(x) = %i (ints)\n",   ff(succ)(3));
    printf( "ff(x) = %i (ints)\n\n", eval( ff(pred), 6));

    printf( "componer(x)  = %i (ints)\n", componer( lambda( int, (int x), return x*x ), lambda( int, (int x), return x+x ) ) (2) );
    printf( "componer(x)  = %i (ints)\n", componer( lambda( int, (int x), return x+1 ), lambda( int, (int x), return x-1 ) ) (6) );
    printf( "compose(x) = %i (ints)\n", compose( lambda( int, (int x), return x+x ), lambda( int, (int x), return x*x ) ) (2) );
    printf( "compose(x) = %i (ints)\n", compose( succ, succ) (3) );
    printf( "eval(x)     = %i (ints)\n", eval( compose( pred, pred), 3) );
    printf( "compose(x) = %i (ints)\n", compose( succ, succ) (3) );
    printf( "eval(x)     = %i (ints)\n", eval( componer( pred, succ), 3) );
    printf( "cn(x)  = %i (ints)\n", cn( succ, 2, 3) );
    printf( "cn(x)  = %i (ints)\n", cn( succ, 0, 3) );
    printf( "cn(x)  = %i (ints)\n", cn( succ, 7, 3) );
    printf( "aplicar(x) = %i (ints)\n", aplicar( succ, 2 ) (3));
    printf( "aplicar(x) = %i (ints)\n", aplicar( lambda( int, (int x), return x*x ), 2 ) (3) );
    printf( "aplicar(x) = %i (ints)\n", aplicar( lambda( int, (int x), return 3*x ), 4 ) (1) );

//    int val = exam(1);
//    printf( "exam = f(g(x)) = %i (ints)\n", val);
//    val = exam(2);
//    printf( "exam = f(g(x)) = %i (ints)\n", val);
//    val = exam(1);
//    printf( "exam = f(g(x)) = %i (ints)\n", val);

//    return lambda( int, (int x), return x )(0);  // La función Identidad
    return cero();  // La función Cero
}
