#include <stdio.h>
#include <stdlib.h>
#include "macros.h"
#include "syst_jeu.h"


 int getNbElement(int data[maxSizeCarre]);
/*
 placementPossible : pemet de tester si on a le droit de placer une pierre dans une position quelconque
 nbElCapt:  représente le nombre de pierre captées pendant la dernière phase de jeu
 joueur réprésente soit 1 soit 2
 */

 int placementPossible(int p, int data[maxSizeCarre], int nbcapt,int param, char joueur){
      int *groupe,*v;
      int liberte=0;
      int nbv=0;
      int ret=FALSE;
      int test=FALSE;
      int nbg=0;
      int i,j;
      int caseVide;
      int test1=0,test2=0;
      int liberte1=0;


int nbcaseplein=nbCasePlein(data);
      if(nbcaseplein==0){
        return TRUE;
      }


     groupe = (int *)malloc(sizeof(int));  // Allocation de la mémoire
            if (groupe== NULL)
            {
                printf("allocation échouée");
                exit(0);
            }


        int *libofp = (int *)malloc(sizeof(int));  // Allocation de la mémoire
            if (libofp== NULL)
            {
                printf("allocation échouée");
                exit(0);
            }

      if(VerifierKO(p,data,nbcapt,param)==p){
        return ret;
      }
      if(data[p]!=0){

        return ret;
      }


       if(joueur=='N'){


           data[p]=1;


           liberte=calculeLiberte(p,data,libofp);
         // printf("La liberté de Noir  est %d   \n", liberte);

          if(liberte==0){
             v=voisin(p,&nbv);
              test=FALSE; // on suppose qu'il y'a une chaine a capter
             for(i=0;i<nbv;i++){

                   if(data[*v]==2){
                        liberte1=calculeLiberte(*v,data,libofp);
                        if(liberte1==0){
                        test=TRUE;
                     }
                 }
                 v++;
             }
            if(test==FALSE){ // on capte pas

            data[p]=0;
            return ret;
            } else { // on capte
            data[p]=0;
            return TRUE;
            }
        }

         else  if(liberte==1){
              // on cherche le voisin libre

              nbg=getGroupe(p,data,groupe,0);
              i=0;
              ///////////////////////////////////////////////  n'entre pas dans la bouclle
              test=FALSE;

              while((i<nbg) && (test==FALSE )){
                 nbv=0;
                 v=voisin(*groupe,&nbv);
                  for(j=0;j<nbv;j++){
                    if(data[*v]==0){
                       test=TRUE;
                       caseVide = *v;
                    }
                    v++;
                  }

                groupe++;
                i++;
              }
            // on teste si on a plus d'element libre collé
            free(groupe);

            groupe = (int *)malloc(sizeof(int));  // Allocation de la mémoire
            if (groupe== NULL)
            {
                printf("allocation échouée");
                exit(0);
            }

             nbg=0;
             nbg=getGroupe(caseVide,data,groupe,0);
             if(nbg>1){

                    data[p]=0;
                     return TRUE;
                }else if(nbg==1){  // cas mort vivant

                  data[caseVide] = 1;
                  if(calculeLiberte(caseVide,data,libofp)==0){
                    test1=0; // on sera capté si on avance de 2 pas
                  }
                  data[caseVide] = 2;
                  if(calculeLiberte(p,data,libofp)==0){
                    test2=0; // on sera capté si on supposte qu' on met un blanc dans l'autre cas vide
                  }
                 data[caseVide]=0;
             }
             if((test1 == 0) && (test2 ==0)){
                data[p]=0;
                return FALSE;
             }

          }
    }



    if(joueur=='B'){

           data[p]=2;
           liberte=calculeLiberte(p,data,libofp);
         // printf("La liberté de Noir  est %d   \n", liberte);

          if(liberte==0){
             v=voisin(p,&nbv);
              test=FALSE; // on suppose qu'il y'a une chaine a capter
             for(i=0;i<nbv;i++){

                   if(data[*v]==1){
                        liberte1=calculeLiberte(*v,data,libofp);
                        if(liberte1==0){
                        test=TRUE;
                     }
                 }
                 v++;
             }
            if(test==FALSE){ // on capte pas

            data[p]=0;
            return ret;
            } else { // on capte
            data[p]=0;
            return TRUE;
            }
        }

         else  if(liberte==1){
              // on cherche le voisin libre

              nbg=getGroupe(p,data,groupe,0);
              i=0;
              ///////////////////////////////////////////////  n'entre pas dans la bouclle
              test=FALSE;

              while((i<nbg) && (test==FALSE )){
                 nbv=0;
                 v=voisin(*groupe,&nbv);
                  for(j=0;j<nbv;j++){
                    if(data[*v]==0){
                       test=TRUE;
                       caseVide = *v;
                    }
                    v++;
                  }

                groupe++;
                i++;
              }
            // on teste si on a plus d'element libre collé
            free(groupe);

            groupe = (int *)malloc(sizeof(int));  // Allocation de la mémoire
            if (groupe== NULL)
            {
                printf("allocation échouée");
                exit(0);
            }

             nbg=0;

             nbg=getGroupe(caseVide,data,groupe,0);
             if(nbg>1){
                   data[p]=0;
                            return TRUE;
                }else if(nbg==1){  // cas mort vivant

                  data[caseVide] = 2;
                  if(calculeLiberte(caseVide,data,libofp)==0){
                    test1=0; // on sera capté si on avance de 2 pas
                  }
                  data[caseVide] = 1;
                  if(calculeLiberte(p,data,libofp)==0){
                    test2=0; // on sera capté si on supposte qu' on met un blanc dans l'autre cas vide
                  }
                 data[caseVide]=0;
             }
             if((test1 == 0) && (test2 ==0)){
                data[p]=0;
                return FALSE;
             }

          }
    }


   data[p]=0;

   int * groupeVide;
   int * aux;


    groupeVide = (int *)malloc(maxSizeCarre*sizeof(int));  // Allocation de la mémoire
    if (groupeVide == NULL)
                    {
                        printf("allocation échouée");
                        exit(0);
                    }


        int testB=0;
        int testN=0;

        aux=groupeVide;
        j=0;
        int   nbelvide=getGroupe(p,data,groupeVide,0);

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

            if(((testN==0 && testB>=0)|| (testB==0 && testN>=0)) && getNbElement(data)>1){
                               return FALSE;

            }







   return TRUE;

 }

 int getNbElement(int data[maxSizeCarre]){
     int i=0;
     int cmp=0;
     for(i=0;i<maxSizeCarre;i++){
        if(data[i]!=0){
           cmp++;
        }
     }
     return cmp;
 }
