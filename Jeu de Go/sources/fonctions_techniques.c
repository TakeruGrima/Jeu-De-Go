#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDl/SDL_mixer.h>
#include "fonctions_techniques.h"
#include "macros.h"

void print_image(SDL_Surface *ecran,SDL_Surface *surface,int x,int y,SDL_Rect selection,int opacite,int R,int V,int B,int *continuer)//RVB pour rendre une couleur de l'image transparente,continuer sert au cas o� la surface aurait mal �t� appliqu�
{
   SDL_Rect coordonnees;//cette structure va stocker les coordonn�es mis en argument (x et y)
   SDL_SetColorKey(surface, SDL_SRCCOLORKEY, SDL_MapRGB(surface->format,R,V,B));//on "efface" la couleur de fond(en g�n�ral c'est blanc donc 255,255,255
   SDL_SetAlpha(surface, SDL_SRCALPHA,opacite);//ici on modifie l'opacit� de la surface plus elle est faible plus opacite est petit plus la surface est transparente
   coordonnees.x=x;
   coordonnees.y=y;
   coordonnees.w=0;//les coordonn�es n'ont pas besoin de stocker une taille
   coordonnees.h=0;
   if (SDL_BlitSurface(surface,&selection,ecran,&coordonnees) != FALSE )//affichage de la surface,on test si l'image a bien �t� afficher(FALSE=0)
        {
            fprintf(stderr,"Erreur de copie de la surface sur l'�cran\n");
            *continuer=FALSE;
        }
}

void cleanup()
{
    IMG_Quit();
    Mix_CloseAudio();
    SDL_Quit();
}
