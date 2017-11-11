#ifndef TITLE_SCREEN_H_INCLUDED
#define TITLE_SCREEN_H_INCLUDED

void title_screen(SDL_Surface *screen,int *continuer );
int menu(SDL_Surface *screen,int *mustcontinue,char p[][19]);
int choix_adversaire(SDL_Surface *screen,int *mustcontinue);

#endif // TITLE_SCREEN_H_INCLUDED
