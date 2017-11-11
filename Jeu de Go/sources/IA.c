#include <stdio.h>
#include <stdlib.h>
#include "macros.h"
#include "syst_jeu.h"

int IA(int data[maxSizeCarre],int nbcapt,int param,int i_test,int *passe_tour,int tour_passe,int*libofp,char joueur)
{
    int liberte,trouve=0,trouve_2=0,trouve_capt=0;
    int libofp1=0,libofpm1=0,libof_capt=0,libof_sav=0;
    int i,i_capt,i_2,i_1;
    int p;
   int libchaine=361;
   float *score;
   int place_possible=FALSE;

    libofp = (int *)malloc(maxSizeCarre*sizeof(int));  // Allocation de la mémoire
    if (libofp== NULL)
    {
        printf("allocation échouée");
        exit(0);
    }
   score=calculeScore(data);
   for(p=0;p<maxSizeCarre;p++)
   {

       if(placementPossible(p,data,nbcapt,param,joueur)==TRUE)
       {
          p=maxSizeCarre-1;
          place_possible=TRUE;
       }
   }
   if((*(score+1)<*score && *score!=361 || place_possible==FALSE) ||tour_passe==1)
   {
       *passe_tour=TRUE;
   }
   else
   {
       *passe_tour=FALSE;
       for(i=i_test;i<maxSizeCarre;i++){
            if(data[i]==1)
            {
                liberte=calculeLiberte(i,data,libofp);

                if(liberte==1 && *libofp!=i_test-1)
                {
                    libofp1=*libofp;
                    libof_capt=libofp1;
                    trouve_capt=TRUE;
                    i_capt=i;
                }
                else if(liberte<=libchaine && *libofp!=i_test-1)
                {
                    libchaine=liberte;
                    libofp1=*libofp;
                    libofpm1=*libofp;
                    trouve=TRUE;
                    i_1=i;
                }
            }
            if(data[i]==2)
            {
                liberte=calculeLiberte(i,data,libofp);
                if(liberte==1 && *libofp!=i_test-1)
                {
                    libofp1=*libofp;
                    libof_sav=libofp1;
                    trouve_2=TRUE;
                    i_2=i;
                }
            }
        }
        free(libofp);
        if(trouve==TRUE && trouve_2==FALSE && trouve_capt==FALSE)
        {
            libofp = (int *)malloc(maxSizeCarre*sizeof(int));  // Allocation de la mémoire
             if (libofp== NULL)
            {
                printf("allocation échouée");
                exit(0);
            }
            liberte=calculeLiberte(i_1,data,libofp);
            libofp1=libofpm1;
        }
        else if(trouve_capt==TRUE)
        {
            libofp = (int *)malloc(maxSizeCarre*sizeof(int));  // Allocation de la mémoire
             if (libofp== NULL)
            {
                printf("allocation échouée");
                exit(0);
            }
            liberte=calculeLiberte(i_capt,data,libofp);
            libofp1=libof_capt;
        }
        else if(trouve_2==TRUE)
        {
            libofp = (int *)malloc(maxSizeCarre*sizeof(int));  // Allocation de la mémoire
            if (libofp== NULL)
            {
                printf("allocation échouée");
                exit(0);
            }
            liberte=calculeLiberte(i_2,data,libofp);
            libofp1=libof_sav;
        }
   }


    return libofp1;
}
