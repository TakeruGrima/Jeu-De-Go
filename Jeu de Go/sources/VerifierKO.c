#include <stdio.h>
#include <stdlib.h>
#include "macros.h"
#include "syst_jeu.h"

/*
   checkKO
*/

int VerifierKO(int p, int data[maxSizeCarre],int nbElCapt,int param){

    int * deja;
    int *libofp;
    int liberte;
    int * groupe;
    int nbelg;
    int ret=KO;
    int vLibre=0;

  if(nbElCapt==1){
     // calculer la liberté de p

         if(p==param){

            libofp = (int *)malloc(sizeof(int));  // Allocation de la mémoire
            if (libofp == NULL)
            {
                printf("allocation échouée");
                exit(0);
            }


           liberte = calculeLiberte(p,data,libofp);
           vLibre=*libofp;
          // printf("liberte de %d = %d\n",p, liberte );

           if (liberte ==0){

            // chercher la chaine qui contient le voisin v et faire la suppression
           groupe = (int *)malloc(sizeof(int));  // Allocation de la mémoire
            if (groupe== NULL)
            {
                printf("allocation échouée");
                exit(0);
            }
            nbelg=getGroupe(p,data,groupe,0);

            if(nbelg==1){

                ret = *groupe;
            }

           }

   }
  }
  return ret;
}
