#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include "fonctions_techniques.h"
#include "title_screen.h"
#include "macros.h"

int menu(SDL_Surface *screen,int *mustcontinue,char p[][19])
{
    SDL_Surface *choix,*commande;
    SDL_Rect position_new_game,position_continuer,position_quitter,position_choix;
    SDL_Rect new_game,continuer,quitter;
    SDL_Rect taille_new,taille_cont,taille_quit;
    SDL_Rect taille_commande,position_commande;
    SDL_Rect taille_choix,taille;
    SDL_Event event;

    int choix_menu=1,choix_m1=0,tescontinuer=TRUE,i=50,tour=0;
    int tempsPrecedent = 0, tempsActuel = 0;
    int t,j,charger=0;
    choix = IMG_Load("./data/menu_template.bmp");
    commande = IMG_Load("./data/menu_commande.png");

    taille_commande.x=0;
    taille_commande.y=0;
    taille_commande.w=commande->w;
    taille_commande.h=commande->h;

    position_commande.x=(SCREEN_W-taille_commande.w)/2;
    position_commande.y=10;

    taille.x=0;
    taille.y=0;
    taille.w=272;
    taille.h=48;

    taille_choix.x=0;
    taille_choix.y=48;
    taille_choix.w=272;
    taille_choix.h=48;

    position_new_game.x=(SCREEN_W-taille.w)/2;
    position_continuer.x=position_new_game.x;
    position_quitter.x=position_new_game.x;

    position_new_game.y=(SCREEN_H-taille.h)/4;
    position_continuer.y=position_new_game.y+4+taille.h;
    position_quitter.y=position_continuer.y+4+taille.h;
    position_choix.y=position_new_game.y;
    position_choix.x=position_new_game.x;

    print_image(screen,choix,position_new_game.x,position_new_game.y,taille,255,255,0,0,&tescontinuer);
    print_image(screen,choix,position_continuer.x,position_continuer.y,taille,255,255,0,0,&tescontinuer);
    print_image(screen,choix,position_quitter.x,position_quitter.y,taille,255,255,0,0,&tescontinuer);
    print_image(screen,commande,position_commande.x,position_commande.y,taille_commande,255,255,255,255,&tescontinuer);
    taille_new.x=273;
    taille_new.y=0;
    taille_new.w=164;
    taille_new.h=28;
    new_game.y=position_new_game.y+10;
    new_game.x=(SCREEN_W-taille_new.w)/2;

    taille_cont.x=273;
    taille_cont.y=31;
    taille_cont.w=132;
    taille_cont.h=28;
    continuer.y=position_continuer.y+10;
    continuer.x=(SCREEN_W-taille_cont.w)/2;

    taille_quit.x=273;
    taille_quit.y=63;
    taille_quit.w=88;
    taille_quit.h=28;
    quitter.y=position_quitter.y+10;
    quitter.x=(SCREEN_W-taille_quit.w)/2;

    print_image(screen,choix,new_game.x,new_game.y,taille_new,255,255,0,0,&tescontinuer);
    print_image(screen,choix,continuer.x,continuer.y,taille_cont,255,255,0,0,&tescontinuer);
    print_image(screen,choix,quitter.x,quitter.y,taille_quit,255,255,0,0,&tescontinuer);

    SDL_Flip(screen);
    while (tescontinuer==TRUE)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                *mustcontinue=FALSE;
                tescontinuer=FALSE;
            break;

            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    case SDLK_UP:
                            switch(choix_menu)
                            {
                            case 1:
                                position_choix.y=position_quitter.y;
                                choix_menu=3;
                            break;
                            case 2:
                                position_choix.y=position_new_game.y;
                                choix_menu=1;
                            break;
                            case 3:
                                position_choix.y=position_continuer.y;
                                choix_menu=2;
                            break;
                            }
                    break;
                     case SDLK_DOWN:
                            switch(choix_menu)
                            {
                            case 1:
                                position_choix.y=position_continuer.y;
                                choix_menu=2;
                                 tescontinuer=TRUE;
                                *mustcontinue=TRUE;
                            break;
                            case 2:
                                position_choix.y=position_quitter.y;
                                choix_menu=3;
                                 tescontinuer=TRUE;
                                *mustcontinue=TRUE;
                            break;
                            case 3:
                                position_choix.y=position_new_game.y;
                                choix_menu=1;
                                 tescontinuer=TRUE;
                                *mustcontinue=TRUE;
                            break;
                            }
                    break;
                    case SDLK_ESCAPE:
                        tescontinuer=FALSE;
                        *mustcontinue=FALSE;
                    break;
                    case SDLK_RETURN:
                        switch(choix_menu)
                        {
                            case 1:
                                 tescontinuer=FALSE;
                                 *mustcontinue=TRUE;
                            break;
                            case 2:
                                charger=TRUE;
                                tescontinuer=FALSE;
                                *mustcontinue=TRUE;
                            break;
                            case 3:
                                *mustcontinue=FALSE;
                                tescontinuer=FALSE;
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
        taille_choix.y=48;

        print_image(screen,choix,position_new_game.x,position_new_game.y,taille,255,255,0,0,&tescontinuer);
        print_image(screen,choix,position_continuer.x,position_continuer.y,taille,255,255,0,0,&tescontinuer);
        print_image(screen,choix,position_quitter.x,position_quitter.y,taille,255,255,0,0,&tescontinuer);

        print_image(screen,choix,new_game.x,new_game.y,taille_new,255,255,0,0,&tescontinuer);
        print_image(screen,choix,continuer.x,continuer.y,taille_cont,255,255,0,0,&tescontinuer);
        print_image(screen,choix,quitter.x,quitter.y,taille_quit,255,255,0,0,&tescontinuer);

        print_image(screen,choix,position_choix.x,position_choix.y,taille_choix,i,255,0,0,&tescontinuer);
        SDL_Flip(screen);
    }
    SDL_FreeSurface(commande);
    SDL_FreeSurface(choix);
    return charger;
}
