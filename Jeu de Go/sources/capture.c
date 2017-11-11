#include <stdio.h>
#include <stdlib.h>
#include "macros.h"
#include "syst_jeu.h"


int capturer(int n, int data[maxSizeCarre], int *ret)//n représente l'indice du pion
{
    int i=0;
    int j=0;
    //variable concernant les voisins
    int nbv=0;//nbv: nombre de voisins
    int *v=NULL;
    v= voisin(n,&nbv);//adresse de la premiere case de la liste des voisins
    int *vm1=NULL;//voisin précédent

    //variables concernant les libertés
    int *libofn=NULL;
    int liberte =0;

    //variables concernant les chaines
    int * groupe=NULL;
    int nb_element=0;


    for( i=0;i<nbv;i++){

         if(data[*v] !=data[n] && data[*v]!=0 )
         {

            libofn = (int *)malloc(sizeof(int));  // Allocation de la mémoire
            if (libofn == NULL)
            {
                printf("allocation échouée");
                exit(0);
            }
          liberte = calculeLiberte(*v,data,libofn);
          //free(vm1);
          //free(libofn);


          if(liberte==0){
            // chercher la chaine qui contient le voisin v et faire la suppression
           groupe = (int *)malloc(sizeof(int));  // Allocation de la mémoire
            if (groupe== NULL)
            {
                printf("allocation échouée");
                exit(0);
            }
            nb_element=getGroupe(*v,data,groupe,0);
            for(j=0;j<nb_element;j++){
                data[*groupe]=0;
                *ret=*groupe;
                groupe++;
            }
            free(groupe);

          }
       }
      v++;
    }


    return nb_element;
}
