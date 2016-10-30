/*
 * DESCRIPCION: El siguiente programa calcula las raices de un 
 *              polinomio de segundo grado p(x) = Ax^2 + Bx + C = 0
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "hoare.h"

int main()
 {
  float a = 1.0, b = 0.0, c = 1.0, d = 0.0, r = 0.0; // Entradas 
  float raiz1 = 0.0,  raiz2 = 0.0;                   // raices reales
  float preal = 0.0,  pimag = 0.0;                   // raices complejas (parte real y parte imaginaria)
  int imag = 0;
  
  printf("\nObtener raices de polinomios de segundo grado p(x) = Ax^2 + Bx + C = 0");
  printf("\nIntroduzca el valor de 'A' (real): ");
  scanf ("%f", &a);   
  printf("\nIntroduzca el valor de 'B' (real): ");
  scanf ("%f", &b);   
  printf("\nIntroduzca el valor de 'C' (real): ");
  scanf ("%f", &c);   

  printf("\nSe leyo A = %f, B = %f, C = %f\n\n", a, b, c);

  _pre( a != 0.0);     //precondicion modificada

  d = b*b - 4*a*c;   // discriminante
  
  imag = (d < 0.0);  // Si es negativo, raices complejas

  printf("\nDiscriminante D = %f, imag = %d\n\n", d, imag);

  r = sqrt(fabs(d)); // sacar raiz cuadrada del valor absoluto del discriminante
  
  if (imag) {
	 preal = -b/(2*a);
	 pimag =  r/(2*a);
	 printf("\nRaices complejas %f +%fi y   %f %fi\n\n ", preal, pimag, preal, -pimag);
  } else {
	 raiz1 = (-b + r)/(2*a);
	 raiz2 = (-b - r)/(2*a);
	 printf("\nRaices reales %f y  %f\n\n", raiz1, raiz2);
  }

  _post( ((      raiz1*raiz2       == c/a) && (raiz1+raiz2 == -b/a)) ||
         ((preal*preal+pimag*pimag == c/a) && (preal+preal == -b/a))    );     //precondicion modificada
   //system("PAUSE");
     
  return 0;
 
} /* end main */
