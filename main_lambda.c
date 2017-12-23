#include <stdio.h>
#include "hoare.h"
#include "lambda.h"

//extern void (*signal(int, void (*)(int)))(int);

int main()
{
    int xx = 64;
    int yy = 25;
    char aa[] = "0123456789";
    char bb[] = "abcdefghij";
    // CompilerAssert(1<2);
    printf("xx: %i,  yy: %i\n",xx,yy);
    SWAP(xx,yy);
    printf("xx: %i,  yy: %i\n",xx,yy);
    printf("aa: %s,  bb: %s\n",aa,bb);
    MEMSWAP(aa,bb);
    printf("aa: %s,  bb: %s\n",aa,bb);
    int (*i_componer_f_gx) (I_FPTR_t, I_FPTR_t, int); // Componer funciones enteras
    // O también hacer la declaración directamente de componer funciones floats
    float (*f_componer_f_gx) (float (*)(float), float (*)(float), float);

    int (*succ)(int)    = lambda( int, (int x), return x+1 );
    int (*pred)(int)   = lambda( int, (int x), return x-1 );
    int (*r)(int, int) = lambda( int, (int x, int y), _expects(y!=0); return x/y );

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

//                           (lambda( int, (int x), return x*x ), lambda( int, (int x), return x+x ) );

    I_FPTR_t (*ff)(I_FPTR_t) = lambda (I_FPTR_t,
                                       (I_FPTR_t h),
                                       return h );
//                                              (lambda( int, (int x), return x*x ) );
//    I_FPTR_t (*hh)(I_FPTR_t) = lambda (I_FPTR_t,
//                                       (I_FPTR_t h),
//                                       return h );
//
    printf("\na.\nz=%i\n",
    ({
        int z (int x)
        {
            return x+1;
        }
        z;
    }) (5));

//    int fun = ff(r)(3);
    printf( "call = %i (ints)\n",  call( ff(lambda( int, (int x), return 2*x)), 5) );
    printf( "apply = %i (ints)\n",  i_apply( ff( lambda( int, (int x), return 2*x) ), 3)(4) );
    printf( "val = %i (ints)\n", lambda( int, (int x), return 2*x )(1) );
    printf( "val = %i (ints)\n", lambda( int, (int x), return 2*x )(3) );
    printf( "val = %i (ints)\n", call(lambda( int, (int x), return 2*x), 3) );

    printf( "\nb.\ncn(x) = %i (ints)\n",   cn(succ,5,3));
    printf( "ff(x) = %i (ints)\n",   ff(succ)(3));
    printf( "ff(x) = %i (ints)\n", eval( ff(pred), 6));

    printf( "\nc.\ncomponer(x)  = %i (ints)\n", componer( lambda( int, (int x), return x*x ), lambda( int, (int x), return x+x ) ) (2) );
    printf( "componer(x)  = %i (ints)\n", componer( lambda( int, (int x), return x+1 ), lambda( int, (int x), return x-1 ) ) (6) );
    printf( "compose(x) = %i (ints)\n", i_compose( lambda( int, (int x), return x+x ), lambda( int, (int x), return x*x ) ) (2) );
    printf( "compose(x) = %i (ints)\n", i_compose( succ, succ) (3) );
    printf( "eval(x)     = %i (ints)\n", eval( i_compose( pred, pred), 3) );
    printf( "compose(x) = %i (ints)\n", i_compose( succ, succ) (3) );
    printf( "eval(x)     = %i (ints)\n", eval( componer( pred, succ), 3) );

    printf( "\nd.\ncn(x)  = %i (ints)\n", cn( succ, 2, 3) );
    printf( "cn(x)  = %i (ints)\n", cn( succ, 0, 3) );
    printf( "cn(x)  = %i (ints)\n", cn( succ, 7, 3) );
    printf( "aplicar(x) = %i (ints)\n", aplicar( succ, 2 ) (3));
    printf( "aplicar(x) = %i (ints)\n", aplicar( lambda( int, (int x), return x*x ), 2 ) (3) );
    printf( "aplicar(x) = %i (ints)\n", aplicar( lambda( int, (int x), return 3*x ), 4 ) (1) );

    int (*max) (int, int) = lambda1 (int, (int x, int y) { return x > y ? x : y;} );
    printf( "\ne.\nlambda1(x) = %s --> QUOTE\n", QUOTE( lambda1( int, (int x) { return x; } ) ) );
    printf( "lambda1(x) = %s --> VERBATIM\n", VERBATIM( lambda1( int, (int x) { return x; } ) ) );
    printf( "lambda1(x) = %i (ints)\n", max (1, 2));
    printf( "lambda1(x) = %i (ints)\n", max (3, 5));

    I_FPTR_t ident = lambda2( int, (int x), {return x;} );
    printf( "\nf.\nlambda2(x) = %s --> QUOTE\n", QUOTE( lambda2( int, (int x), {return x;} ) ) );
    printf( "lambda2(x) = %s --> VERBATIM\n", VERBATIM( lambda2( int, (int x), {return x;} )));
    printf( "lambda2(x) = %i (ints)\n", ident(4) );
    printf( "lambda2(x) = %i (ints)\n", ident(-7) );
    printf( "lambda2(x) = %i (ints)\n", lambda2( int, (int x), {return x;} )(3) );
    printf( "lambda2(x) = %li (ints)\n", aplicar(lambda2( int, (int x), {return x;} ), 0)(3) );
    printf( "lambda2(x) = %li (ints)\n", aplicar(lambda2( int, (int x), {return x;} ), 0)(-4) );
    printf( "lambda2(x) = %li (ints)\n", aplicar(ident, 0)(2 ) );
    printf( "lambda2(x) = %li (ints)\n", aplicar(ident, 1)(2 ) );
    printf( "lambda2(x) = %li (ints)\n", aplicar(ident, 4)(2 ) );
    L_FPTR_t cuad  = lambda2( long, (long x), {return x*x;} );
    printf( "\ng.\nlambda2(x) = %li (ints)\n", cuad(4) );
    printf( "lambda2(x) = %li (ints)\n", cuad(-7) );
    printf( "lambda2(x) = %li (ints)\n", aplicar(cuad, 2) (3) );
    printf( "lambda2(x) = %li (ints)\n", aplicar(cuad, 4) (3) );


//    int val = exam(1);
//    printf( "exam = f(g(x)) = %i (ints)\n", val);
//    val = exam(2);
//    printf( "exam = f(g(x)) = %i (ints)\n", val);
//    val = exam(1);
//    printf( "exam = f(g(x)) = %i (ints)\n", val);

//    return lambda( int, (int x), return x )(0);  // La función Identidad
    int (*cero)(void)  = lambda( int, (void), return 0 );
    return cero();  // La función Cero
}
