#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDl/SDL_mixer.h>
#include "fonctions_techniques.h"
#include "jeu.h"
#include "macros.h"
#include "syst_jeu.h"

void pause(SDL_Surface *screen,SDL_Surface *plateau,SDL_Rect select_plateau,char p[][19],int *mustcontinue,int *continuer,char joueur,int *IA_active)
{
    SDL_Surface *menu_pause;
    SDL_Rect position_retour,position_save_cont,position_save_quit,position_quit;
    SDL_Rect taille;

    SDL_Rect retour,save_cont,save_quit,quitter;
    SDL_Rect taille_retour,taille_sav_cont,taille_sav_quit,taille_quit;

    SDL_Rect position_choix,taille_choix;

    int testcontinuer=TRUE;
    int choix_menu=1,choix_m1=0,i=50,tour=0;
    int tempsPrecedent = 0, tempsActuel = 0;
    int param=-1;
    int nbelCapt=0;
    SDL_Event event;

    menu_pause = IMG_Load("./data/pause_template.png");

    taille.x=0;
    taille.y=0;
    taille.h=48;
    taille.w=304;

    taille_choix.x=0;
    taille_choix.y=48;
    taille_choix.h=48;
    taille_choix.w=304;

    position_retour.x=(SCREEN_W-taille.w)/2;
    position_retour.y=(SCREEN_H-taille.h)/4;

    position_save_cont.x=position_retour.x;
    position_save_cont.y=position_retour.y+taille.h+4;

    position_save_quit.x=position_retour.x;
    position_save_quit.y=position_save_cont.y+taille.h+4;

    position_quit.x=position_retour.x;
    position_quit.y=position_save_quit.y+taille.h+4;

    position_choix.x=position_retour.x;
    position_choix.y=position_retour.y;

    taille_retour.x=306;
    taille_retour.y=0;
    taille_retour.w=88;
    taille_retour.h=28;

    taille_sav_cont.x=306;
    taille_sav_cont.y=32;
    taille_sav_cont.w=278;
    taille_sav_cont.h=28;

    taille_sav_quit.x=306;
    taille_sav_quit.y=64;
    taille_sav_quit.w=248;
    taille_sav_quit.h=28;

    taille_quit.x=306;
    taille_quit.y=96;
    taille_quit.w=102;
    taille_quit.h=28;

    retour.x=(SCREEN_W-taille_retour.w)/2;
    retour.y=position_retour.y+10;

    save_cont.x=(SCREEN_W-taille_sav_cont.w)/2;
    save_cont.y=position_save_cont.y+10;

    save_quit.x=(SCREEN_W-taille_sav_quit.w)/2;
    save_quit.y=position_save_quit.y+10;

    quitter.x=(SCREEN_W-taille_quit.w)/2;
    quitter.y=position_quit.y+10;

    while (testcontinuer==TRUE)
    {
            SDL_WaitEvent(&event);
            switch(event.type)
            {
                case SDL_QUIT:
                    testcontinuer=FALSE;
                    *mustcontinue=FALSE;
                    *continuer=FALSE;
                break;

                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_UP:
                                switch(choix_menu)
                                {
                                case 1:
                                    position_choix.y=position_quit.y;
                                    choix_menu=4;
                                break;
                                case 2:
                                    position_choix.y=position_retour.y;
                                    choix_menu=1;
                                break;
                                case 3:
                                    position_choix.y=position_save_cont.y;
                                    choix_menu=2;
                                break;
                                case 4:
                                    position_choix.y=position_save_quit.y;
                                    choix_menu=3;
                                break;
                                }
                        break;
                         case SDLK_DOWN:
                                switch(choix_menu)
                                {
                                case 1:
                                    position_choix.y=position_save_cont.y;
                                    choix_menu=2;
                                    testcontinuer=TRUE;
                                break;
                                case 2:
                                    position_choix.y=position_save_quit.y;
                                    choix_menu=3;
                                    testcontinuer=TRUE;
                                break;
                                case 3:
                                    position_choix.y=position_quit.y;
                                    choix_menu=4;
                                    testcontinuer=TRUE;
                                break;
                                case 4:
                                    position_choix.y=position_retour.y;
                                    choix_menu=1;
                                break;
                                }
                        break;
                        case SDLK_ESCAPE:
                            testcontinuer=FALSE;
                            *continuer=FALSE;
                            *mustcontinue=FALSE;
                        break;
                        case SDLK_RETURN:
                            switch(choix_menu)
                            {
                                case 1:
                                    *continuer=TRUE;
                                     testcontinuer=FALSE;
                                     *mustcontinue=TRUE;
                                break;
                                case 2:
                                    save(p,joueur,*IA_active);
                                    testcontinuer=FALSE;
                                    *mustcontinue=TRUE;
                                    *continuer=TRUE;
                                break;
                                case 3:
                                    save(p,joueur,*IA_active);
                                    testcontinuer=FALSE;
                                    *mustcontinue=FALSE;
                                    *continuer=FALSE;
                                break;
                                case 4:
                                    testcontinuer=FALSE;
                                    *mustcontinue=FALSE;
                                    *continuer=FALSE;
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

            print_image(screen,menu_pause,position_retour.x,position_retour.y,taille,255,255,0,0,&testcontinuer);
            print_image(screen,menu_pause,position_save_cont.x,position_save_cont.y,taille,255,255,0,0,&testcontinuer);
            print_image(screen,menu_pause,position_save_quit.x,position_save_quit.y,taille,255,255,0,0,&testcontinuer);
            print_image(screen,menu_pause,position_quit.x,position_quit.y,taille,255,255,0,0,&testcontinuer);

            print_image(screen,menu_pause,retour.x,retour.y,taille_retour,255,255,0,0,&testcontinuer);
            print_image(screen,menu_pause,save_cont.x,save_cont.y,taille_sav_cont,255,255,0,0,&testcontinuer);
            print_image(screen,menu_pause,save_quit.x,save_quit.y,taille_sav_quit,255,255,0,0,&testcontinuer);
            print_image(screen,menu_pause,quitter.x,quitter.y,taille_quit,255,255,0,0,&testcontinuer);

            print_image(screen,menu_pause,position_choix.x,position_choix.y,taille_choix,i,255,0,0,&testcontinuer);
            SDL_Flip(screen);
        }
        SDL_FreeSurface(menu_pause);
}
