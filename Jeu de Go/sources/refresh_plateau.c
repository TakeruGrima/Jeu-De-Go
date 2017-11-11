#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDl/SDL_mixer.h>
#include "fonctions_techniques.h"
#include "jeu.h"
#include "macros.h"

void refresh_plateau(SDL_Surface* ecran,SDL_Surface* pions,SDL_Rect select_pion,char p[][19],int *continuer)
{
    int x,y,i,j;
	for(i=0;i<19;i++)
    {
        for (j=0;j<19;j++)
        {
            x=i*19;
            y=j*19;
            if(p[i][j]=='N')
            {
                select_pion.x=0;
                select_pion.y=0;
                select_pion.w=PION_W;
                select_pion.h=PION_H;
            }
            else if(p[i][j]=='B')
            {
                select_pion.x=PION_W;//on sélectionne le pion blanc donc on ajoute la taille d'un pion a l'abscisse(voir l'image)
                select_pion.y=0;
                select_pion.w=PION_W;
                select_pion.h=PION_H;
            }
            else
            {
                select_pion.w=0;
                select_pion.h=0;
            }
            print_image(ecran,pions,x,y,select_pion,255,255,255,255,continuer);
        }
    }
}
