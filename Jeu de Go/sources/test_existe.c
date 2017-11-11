#include <stdio.h>
#include <stdlib.h>
#include "macros.h"
#include "syst_jeu.h"


/*
  test exist() teste si un élement existe dans un tableau ou pas
*/
int testexist(int nb, int *tab, int cmp){
        //printf("nb dans texExist=  %d \n", nb);

    int trouve =FALSE;
    int *p1;
    p1=tab;
    int i=0;
   // printf("taille  %d \n", cmp);

  while(i<cmp && trouve==FALSE){
//printf("element i :  %d \n", *p1);
    if(*p1==nb){
        trouve=TRUE;
    }
    p1++;
    i++;
  }

  return trouve;
}
