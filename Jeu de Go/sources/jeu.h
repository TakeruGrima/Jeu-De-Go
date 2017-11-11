#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDl/SDL_mixer.h>
#ifndef JEU_H_INCLUDED
#define JEU_H_INCLUDED

void place_pion(SDL_Surface* ecran,SDL_Surface* plateau,char p[][19],char joueur,int *continuer, int * param, int * nbelCapt,int choix,int *passe_tour,int tour_passe);
void refresh_plateau(SDL_Surface* ecran,SDL_Surface* pions,SDL_Rect select_pion,char p[][19],int *continuer);
void pause(SDL_Surface *screen,SDL_Surface *plateau,SDL_Rect select_plateau,char p[][19],int *mustcontinue,int *continuer,char joueur,int *IA_active);
void affiche_score(SDL_Surface *screen,float score,char joueur);

#endif // JEU_H_INCLUDED
