#include <stdio.h>
#include <stdlib.h>
#include "macros.h"
#include "syst_jeu.h"


/*
    fonction listeLiberte()
    retourne un tableau d'indices des libertés
  */

int  recursionLiberty(int p, int * deja, int * libOfp, int data[maxSizeCarre],int nbdej,int nl)
{
    int cmp=0;
    int * deja1, *libOfp1;
    deja1=deja+nbdej;
    libOfp1=libOfp+nl;
    int nbdeja=nbdej;
    int nbVoisin;
    int trouve=FALSE;
    int nbLib=nl;
    *deja1=p;
     nbdeja++;
     int *p1=NULL;

     nbVoisin=0;
    p1= voisin(p,&nbVoisin);

   //printf("j'entre dans la boucle %d \n", p);

    int i,k;
    for(i=0;i<nbVoisin;i++){
       //printf("voisin  %d \n", *p1);
        k=*p1;
       trouve=testexist(k,libOfp,nbLib);

       if(data[*p1]==0 && trouve==FALSE){  //
       // printf("hhhhhhhhhhhhhhhh");

         *libOfp1=*p1;
         libOfp1++;
         nbLib++;
         cmp++;

        }
         else
         {
             k=*p1;

                // printf("nbdeja   %d \n", nbdeja);

                 trouve=testexist(k,deja,nbdeja);
                //  printf("trouve  %d  pour %d     \n", trouve,k);

             if((data[k]==data[p]) && (trouve==FALSE)){
                 //printf(" hhhhhhh    fdata[p] =       %d \n",data[p]);

                 cmp=cmp+recursionLiberty(k,deja,libOfp,data,nbdeja,nbLib);
                //printf("hhhhhhhhhhh   cmp  = %d \n",cmp);

            }
         }
          p1++;

         }

//printf("hhhhhhhhhhh   nb Liberte  = %d \n",nl+nbLib);

    return cmp;
  }
