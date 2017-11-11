#include <stdio.h>
#include <stdlib.h>
#include "macros.h"
#include "syst_jeu.h"

/*
  fonction qui calcule  à partie de l'indice de l'élement dans le ableau (sa  position) un couple
  i, J qui correspondent à ses  cordonnées dans le gabon
*/

int * correspondanceIndice(int n)
{
        int j=n%maxSize;
        int i=(n-j)/maxSize;
        int *p1;
        p1 = (int *)malloc(2*sizeof(int)); // Allocation de la mémoire
        *p1=j;
        *(p1+1)=i;
        return p1;
}
