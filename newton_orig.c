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

D_FPTR_t fp (D_FPTR_t f)
{
    const double d = 0.001;
    return lambda(double, (double x), return (f(x+d)-f(x-d))/(2.0*d));
}

double nraux(D_FPTR_t f, D_FPTR_t fp, double xi, double xn)
{
    const double eps = 0.001;
    if (ABS(xn-xi)<eps)
        return xn;
    return nraux(f, fp, xi - f(xi)/fp(xi), xi);
}

double nr (D_FPTR_t f, double xi)
{
    return nraux(f, fp(f), xi+1, xi);
}


int main()
 {
  double a, x, xn, epsilon, diferencia; // Entradas para la raiz cuadrada

  printf("\nIntroduzca el valor 'a' (real): ");
  scanf ("%lf", &a);    // %lf es el formato para double
  printf("\nIntroduzca el valor 'x' inicial (real): ");
  scanf ("%lf", &x);
  printf("\nIntroduzca el valor 'epsilon' de tolerancia (real): ");
  scanf ("%lf", &epsilon);

  printf("\nSe leyeron los valores a = %10.7lf,  x = %10.7lf,  epsilon = %10.8lf\n",a,x,epsilon);
  // %10.7lf = double, en 10 espacios, con 7 decimales (+ punto + 2 parte entera = 10 espacios)

 _pre( a>=0 );     //precondicion modificada

  diferencia = epsilon + 1.0;

  while (diferencia > epsilon)
   {
     xn = x - (x*x - a)/(2.0*x);      // raiz cuadrada
     // xn = x - (x*x*x - a)/(3.0*x*x);  // raiz cubica, tambien
     diferencia = fabs(xn -x);
     x = xn;
     printf("\nLa función tiene un zero en %10.7lf, con diferencia %10.8lf\n", x, diferencia);
	 _inv(TRUE);
   }

  printf("\nLa función tiene un zero en %10.7lf con precision %10.8lf\n", x, epsilon);

   //system("PAUSE");
  return 0;
} /* end main */
