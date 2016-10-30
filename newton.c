/*
 * DESCRIPCION: El siguiente programa calcula la raiz cuadrada de un numero "a"
 *              por el metodo de Newton
 *              f(x) = x^2 - a = 0
 *              f(x) = x^3 - a = 0
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "hoare.h"
#include "lambda.h"

D_FPTR_t PURE fprima (D_FPTR_t f)
{
    #define d 0.001
    //const double d = 0.001;
    return lambda( double, (double x), return (f(x+d)-f(x-d))/(2.0*d) );
}

double nraux(D_FPTR_t f, double xi, double xn)
{
    const double eps = 0.000001;
    printf("\n2 La función %lf tiene un zero en %10.7lf, con diferencia %10.8lf\n", f(xi), xi, ABS(xn-xi));

    if (ABS(xn-xi)<eps)
        return xn;
    double fpval = fprima(f)(xi);
    _pre(ABS(fpval) > eps);
 //   return nraux(f, xi - f(xi)/fprima(f)(xi), xi);
    return nraux(f, xi - f(xi)/fpval, xi);
}

double nr (D_FPTR_t f, double x)
{
    return nraux(f, x, x+1);
}


int main()
{
    double x; // Entradas para la raiz cuadrada

    //  printf("\nIntroduzca el valor 'a' (real): ");
    //  scanf ("%lf", &a);    // %lf es el formato para double
    printf("\nIntroduzca el valor 'x' inicial (real): ");
    scanf ("%lf", &x);
    printf("\nPara el valor %s = %10.7lf\n", QUOTE(x), x);
    // %10.7lf = double, en 10 espacios, con 7 decimales (+ punto + 2 parte entera = 10 espacios)

    // _pre( a>=0 );     //precondicion modificada

    x = nr( lambda(double, (double x), return (x*x - 9.0)), x);
    printf("La función %s tiene un cero en x = %10.8lf\n\n", QUOTE(lambda(double, (double x), return (x*x - 9.0))), x);

    printf("\nIntroduzca el valor 'x' inicial (real): ");
    scanf ("%lf", &x);
    printf("\nPara el valor %s = %10.7lf\n", QUOTE(x), x);

    x = nr( lambda(double, (double x), return (sin(x))), x);
    printf("La función %s tiene un cero en x = %10.8lf\n\n", QUOTE(lambda(double, (double x), return (sin(x)))), x);

    printf("\nIntroduzca el valor 'x' inicial (real): ");
    scanf ("%lf", &x);
    printf("\nPara el valor %s = %10.7lf\n", QUOTE(x), x);

    x = nr( lambda(double, (double x), return (cos(x))), x);
    printf("La función %s tiene un cero en x = %10.8lf\n\n", QUOTE(lambda(double, (double x), return (cos(x)))), x);

    //system("PAUSE");
    return 0;
} /* end main */
