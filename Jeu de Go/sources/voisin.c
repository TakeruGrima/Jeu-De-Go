#include <stdio.h>
#include <stdlib.h>
#include "macros.h"
#include "syst_jeu.h"


// voisin
// cmp doit ^tre initialisé a 0 avant l'appel

int * voisin(int p,int *cmp){

   int* listVoisin= NULL;
   int *pontP;

 listVoisin = (int *)malloc(sizeof(int));  // Allocation de la mémoire


 //listVoisin = (int *)realloc(listVoisin,2*sizeof(int));  // Allocation de la mémoire
    if (listVoisin == NULL)
    {
        printf("allocation échouée");
        exit(0);
    }

    pontP=correspondanceIndice(p);

    if(*pontP>0)  {
        *(listVoisin+(*cmp)) = p-1;
        (*cmp)++;
    }
    if(*pontP<maxSize-1) {
        *(listVoisin+(*cmp)) = p+1;
        (*cmp)++;
    }
    if(*(pontP+1)>0) {
        *(listVoisin+(*cmp)) = p-maxSize;
        (*cmp)++;
    }


   if(*(pontP+1)<maxSize-1) {
        *(listVoisin+(*cmp)) = p+maxSize;
        (*cmp)++;
    }

  return listVoisin;

}
