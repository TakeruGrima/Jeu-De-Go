#include <stdio.h>
#include <stdlib.h>
#include "syst_jeu.h"
#include "macros.h"

float * calculeScore( int data[maxSizeCarre]){

    int cmp;
    int * groupe;
    int * deja;
    int  nbdeja;
    int j;
    int *aux;
    int * v;
    int nbv;
    int testB;
    int testN;
    int i;
    int nbelvide;

          deja = (int *)malloc(maxSizeCarre*sizeof(int));  // Allocation de la mémoire
            if (deja== NULL)
            {
                printf("allocation échouée");
                exit(0);
            }



                   groupe = (int *)malloc(maxSizeCarre*sizeof(int));  // Allocation de la mémoire
                    if (groupe == NULL)
                    {
                        printf("allocation échouée");
                        exit(0);
                    }

         float *  resultat = (float *)malloc(2*sizeof(float));  // Allocation de la mémoire
            if (resultat== NULL)
            {
                printf("allocation échouée");
                exit(0);
            }
        *resultat=0;
        *(resultat+1)=0;



            int trouve;
            nbdeja=0;
            for(cmp=0;cmp<maxSizeCarre;cmp++){
                        trouve=0;
                        for(i=0;i<nbdeja;i++){
                            if(*(deja+i)==cmp){
                                trouve=1;
                            }
                        }

                    if(trouve==0){
                        if(data[cmp]==1){
                          (*resultat)++;
                        } else
                        if(data[cmp]==2){

                          (*(resultat+1))++;
                        } else {


                         // data[p]=0
                         testB=0;
                         testN=0;

                          nbelvide=getGroupe(cmp,data,groupe,0);
                          aux=groupe;
                          j=0;

                           while((j<nbelvide) && ((testN==0 && testB>=0)|| (testB==0 && testN>=0))){

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

                          if(testN==0 && testB>=0){ // territoire Blanc

                            (*(resultat+1))+=nbelvide;

                          } else
                           if(testB==0 && testN>=0){ //territoire noire
                             (*(resultat))+=nbelvide;
                           } else{ // pas un territoire

                           }

                           // mettre a jour deja
                           for(j=0;j<nbelvide;j++){
                            *(deja+nbdeja)= *(groupe+j);
                              nbdeja++;
                           }


                        }

                     }
          }


      *(resultat+1)+=7.5;
     return resultat;
}
