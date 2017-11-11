#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include "fonctions_techniques.h"
#include "title_screen.h"
#include "jeu.h"
#include "macros.h"
#include "syst_jeu.h"

int calculeLiberte(int p, int data[maxSizeCarre],int *libofp){

 int * groupe;
 int nbg;
 int *v;
 int cmp;
 int i,j;
 int nbl=0;
 int * deja;

 deja = (int *)malloc(maxSizeCarre*sizeof(int));  // Allocation de la mémoire
            if (deja== NULL)
            {
                printf("allocation échouée");
                exit(0);
            }


 groupe = (int *)malloc(sizeof(int));  // Allocation de la mémoire
            if (groupe== NULL)
            {
                printf("allocation échouée");
                exit(0);
            }
        nbg=getGroupe(p,data,groupe,0);
        //printf("taille de groupe=%d\n",nbg);

        for( i=0;i<nbg;i++){
            cmp=0;
            v=voisin(*groupe,&cmp);

            for(j=0;j<cmp;j++){
                if(data[*v]==0){

                  if(testexist(*v,deja,nbl)==FALSE){
                    *(deja+nbl) = *v;
                    nbl++;
                    *libofp=*v;
                    libofp++;

                  }

                }
                v++;
            }
            groupe++;
        }
        libofp=libofp-nbl;
        free(groupe);
        return nbl;
}
