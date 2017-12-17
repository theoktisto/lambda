/*
 * DESCRIPCION: El siguiente programa calcula el factorial de N
 *              usando for
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "hoare.h"

int fact_aux(int n, int acum);
int factorial_rec(int n);
int factorial (int n);

int i_suma_aux( int* A, int li, int ls, int acum)
{
    if (li>ls)
        return acum;
    return i_suma_aux( A, li+1, ls, acum+li);
}

int i_suma_rec( int* A, int li, int ls)
{
    return i_suma_aux( A, li, ls, 0);
}

int i_prod_aux( int* A, int li, int ls, int acum)
{
    if (li>ls)
        return acum;
    return i_prod_aux( A, li+1, ls, acum*li);
}

int i_prod_rec( int* A, int li, int ls)
{
    return i_prod_aux( A, li, ls, 1);
}

int fact_aux(int n, int acum)
{
    if (n<2)
        return acum;
    return fact_aux(n-1, acum*n);
}

int factorial_rec(int n)
{
    _expects( n >= 0 );
    return fact_aux(n, 1);
}

int factorial (int n)
{
  int cont;
  int fact=1;
  _expects( n >= 0 );              //precondicion modificada
  for (cont = 1; cont <= n; cont++)
   {
     _bounded( cont );           //cota inferior modificada
     fact = cont*fact;
     printf("Para cont %3d el producto es %6d\n", cont, fact);
     _invariant( fact >= cont ); //invariante sencillo
   }
  _ensures( fact >= n );     //postcondicion modificada
    return fact;
}

int main()
 {
  int fact, N = 0; // Entradas para factorial
  char c;
  printf("\nIntroduzca el valor de 'N' (entero): ");
  scanf ("%d", &N);

  printf("\nSe leyó N = %d\n\n",N);

  _expects( N >= 0 );              //precondicion modificada

  fact = factorial(N);

  _ensures( fact >= N );     //postcondicion modificada
   printf("\nEl factorial de %d es %d\n\n", N, fact);

  //system("PAUSE");

  printf("\nSe leyó N = %d\n\n",N);
   fact = factorial_rec(N);
   printf("\nEl factorial de %d es %d\n\n", N, fact);

   return 0;

} /* end main */
