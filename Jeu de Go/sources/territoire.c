#include <stdio.h>
#include <stdlib.h>
#include "macros.h"
#include "syst_jeu.h"

int **territoire(int data[maxSizeCarre],int joueur){
  int nbelvide=0;
  int *v;
  int *aux,nbv,j=0,cmp=0,cpt,i;
  int test=0;
  int testN=0;
  int testB=0;
  int *groupe;
  int **terri=NULL;

            groupe = (int *)malloc(sizeof(int));  // Allocation de la mémoire
            if (groupe== NULL)
            {
                printf("allocation échouée");
                exit(0);
            }
             terri=(int **)malloc(sizeof(int*)*361);
         for(i=0;i<361;i++)
         {
              terri[i]=(int *)malloc(sizeof(int)*361);
         }



            for(i=0;i<maxSizeCarre;i++)
            {
                nbelvide=getGroupe(i,data,groupe,0);
                 aux =groupe;
                if(data[i]==joueur){

                     while((j<nbelvide))
                     {

                              nbv=0;
                              v=voisin(*aux,&nbv);
                              for(i=0;i<nbv;i++){
                                if(data[*v]==1){
                                    testN++;
                                } else
                                if(data[*v]==2){
                                    testB++;
                                }

                                v++;
                              }
                              aux++;
                              j++;


                      }
                           if((testN==0 && testB>=0)|| (testB==0 && testN>=0))
                           {
                               test=1;
                           }

                           else{
                            test=0;
                           }
                           if(test==1)
                           {
                               for(cpt=0;cpt<nbelvide;cpt++){
                                terri[cmp][cpt]=groupe[nbelvide];
                               }
                              cmp++;

                           }
                           else{
                            cmp++;
                           }

                     }
                 }
                 return terri;

}
