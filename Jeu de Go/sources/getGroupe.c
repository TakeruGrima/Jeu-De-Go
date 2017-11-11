#include <stdio.h>
#include <stdlib.h>
#include "macros.h"
#include "syst_jeu.h"


/*
   groupe : la méthode groupe permet de construire un groupe qui correspond à une chaine

*/


int getGroupe(int p,int data[maxSizeCarre], int *g, int nbelgr){
   int *g1;
   int trouve=FALSE;
   int nbg1=nbelgr;
   g1=g+nbg1;
   *g1=p;
    g1++;
    nbg1++;

  // printf(" j'ajoute %d dans le groupe\n",p);
   //printf(" hhhhhhhhhhhhh   %d\n",nbg1);
   int nbv=0;
   int *v;
   v=voisin(p,&nbv);
   int i;
   int k;
   for(i=0;i<nbv;i++){
    k=*v;
    trouve= testexist(k,g,nbg1);
     if(data[k]==data[p] && trouve==FALSE){
       nbg1= getGroupe(k,data,g,nbg1);
     }
    v++;
   }
     return nbg1;

}
