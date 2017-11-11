#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include "fonctions_techniques.h"
#include "title_screen.h"
#include "macros.h"

int choix_adversaire(SDL_Surface *screen,int *mustcontinue)
{
    SDL_Surface *icon,*commande;
    SDL_Rect position_joueur,position_IA,taille_icon;
    SDL_Rect position_choix,taille_choix;
    SDL_Rect taille_commande,position_commande;
    int continuer=TRUE,choix=1,i=50,tour=0;
    int tempsPrecedent = 0, tempsActuel = 0;
    SDL_Event event;

    icon = IMG_Load("./data/IA_joueur.png");
    commande = IMG_Load("./data/menu_commande.png");

    taille_commande.x=0;
    taille_commande.y=0;
    taille_commande.w=commande->w;
    taille_commande.h=commande->h;

    position_commande.x=(SCREEN_W-taille_commande.w)/2;
    position_commande.y=10;

    print_image(screen,commande,position_commande.x,position_commande.y,taille_commande,255,255,255,255,&continuer);

    taille_icon.x=0;
    taille_icon.y=0;
    taille_icon.w=138;
    taille_icon.h=122;

    position_joueur.x=50;
    position_joueur.y=(SCREEN_H-taille_icon.h)/2;

    position_IA.x=SCREEN_W-50-taille_icon.h;
    position_IA.y=(SCREEN_H-taille_icon.h)/2;


    print_image(screen,icon,position_joueur.x,position_joueur.y,taille_icon,255,255,0,0,&continuer);

    taille_icon.x=138;
    print_image(screen,icon,position_IA.x,position_IA.y,taille_icon,255,255,0,0,&continuer);

    taille_choix.x=276;
    taille_choix.y=0;
    taille_choix.w=taille_icon.w;
    taille_choix.h=taille_icon.h;

    position_choix.x=position_joueur.x;
    position_choix.y=position_joueur.y;

    SDL_Flip(screen);
    while (continuer==TRUE)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                *mustcontinue=FALSE;
                continuer=FALSE;
            break;

            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    case SDLK_RIGHT:
                            switch(choix)
                            {
                            case 1:
                                position_choix.x=position_IA.x;
                                choix=2;
                            break;
                            case 2:
                                position_choix.x=position_joueur.x;
                                choix=1;
                            break;
                            }
                    break;
                     case SDLK_LEFT:
                            switch(choix)
                            {
                            case 1:
                                position_choix.x=position_IA.x;
                                choix=2;
                            break;
                            case 2:
                                position_choix.x=position_joueur.x;
                                choix=1;
                            break;
                            continuer=TRUE;
                            mustcontinue=TRUE;
                            }
                    break;
                    case SDLK_ESCAPE:
                        continuer=FALSE;
                        *mustcontinue=FALSE;
                    break;
                    case SDLK_RETURN:
                        switch(choix)
                        {
                            case 1:
                                 continuer=FALSE;
                                 *mustcontinue=TRUE;
                            break;
                            case 2:
                                continuer=FALSE;
                                *mustcontinue=TRUE;
                            break;
                        }
                    default:
                    break;
                }
        }
        tempsActuel = SDL_GetTicks();
        if (tempsActuel - tempsPrecedent >120)
        {
            tempsPrecedent = tempsActuel;
            if(i==100)
            {
                tour=1;
            }
            else if(i==50)
            {
                tour=0;
            }

            if(tour==0)
            {
                i=i+5;
            }
            else
            {
                i=i-5;
            }
        }
        else
        {
            SDL_Delay(120-(tempsActuel - tempsPrecedent));

        }
        taille_icon.x=0;
        print_image(screen,icon,position_joueur.x,position_joueur.y,taille_icon,255,255,0,0,&continuer);

        taille_icon.x=138;
        print_image(screen,icon,position_IA.x,position_IA.y,taille_icon,255,255,0,0,&continuer);

        print_image(screen,icon,position_choix.x,position_choix.y,taille_choix,i,255,0,0,&continuer);
        SDL_Flip(screen);
    }
    SDL_FreeSurface(commande);
    SDL_FreeSurface(icon);
    return choix;
}
