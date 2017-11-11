#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include "fonctions_techniques.h"
#include "title_screen.h"
#include "macros.h"

void title_screen(SDL_Surface *screen,int *mustcontinue)
{
    int continuer=1; // Le booleen de la boucle
    int i = 0,aff=0;//la valeur aff est égal à la valeur des images afficher(aff=0 correspond au plateau)
    int image =0,tour=0;
    SDL_Event event;
    SDL_Surface *background = NULL, *press_start = NULL;
    SDL_Surface *titre_1 =NULL,*titre_2=NULL;
    SDL_Surface *credit=NULL;
    SDL_Rect positionstart;
    SDL_Rect positiontitre_1,positiontitre_2,position_credit;
    SDL_Rect select,select_credit;
    SDL_Rect selectbackground,select_titre_1,select_titre_2;
    int tempsPrecedent = 0, tempsActuel = 0;
    Mix_Music *musique;

    background = IMG_Load("./data/plateau.bmp");

    if(Mix_OpenAudio(30000, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 5000000) == -1) //Initialisation de l'API Mixer
    {
        printf("%s", Mix_GetError());
    }
    /* Chargement et blittage de press_start sur la scène */
    press_start = IMG_Load("./data/Entree.png");
    titre_1 = IMG_Load("./data/titre(1).png");
    titre_2 = IMG_Load("./data/titre(2).png");
    credit = IMG_Load("./data/credit.png");

    positiontitre_1.x = (background->w - titre_1->w)/2;
    positiontitre_1.y = 67;


    positionstart.x = (background->w - press_start->w)/2;
    positionstart.y = positiontitre_1.y+titre_1->h+20*2;

    position_credit.x = (background->w - credit->w)/2;
    position_credit.y = positionstart.y+40;

    selectbackground.x =0;
    selectbackground.y =0;
    selectbackground.w=background->w;
    selectbackground.h=background->h;

    select_titre_1.x=0;
    select_titre_1.y=0;
    select_titre_1.w=titre_1->w;
    select_titre_1.h=titre_1->h;

    select_titre_2.x=0;
    select_titre_2.y=0;
    select_titre_2.w=titre_2->w;
    select_titre_2.h=titre_2->h;

    select_credit.x=0;
    select_credit.y=0;
    select_credit.w=credit->w;
    select_credit.h=credit->h;

    positiontitre_2.x = (background->w - titre_2->w)/2;
    positiontitre_2.y = 52+(titre_1->h)/2;

    print_image(screen,background,0,0,selectbackground,255,255,255,255,mustcontinue);
    musique = Mix_LoadMUS("./data/titre.mp3");
    Mix_PlayMusic(musique, -1);

    while (continuer==TRUE)
    {
        SDL_PollEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                *mustcontinue=FALSE;
                continuer=FALSE;
                Mix_HaltMusic();
                Mix_FreeMusic(musique);
            break;

            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    case SDLK_RETURN: /* Appui sur la touche Entrée, on arrête le programme */
                    if(aff==2)
                    {
                        continuer = FALSE;
                    }
                    break;
                    case SDLK_ESCAPE:
                        continuer=FALSE;
                        *mustcontinue=FALSE;
                    break;
                    default:
                    break;
                }
        }

        tempsActuel = SDL_GetTicks();
        if (tempsActuel - tempsPrecedent >120)
        {
            i++;
            if(aff==2)
            {
                if(tour==0)
                {
                    image++;
                }
                else
                {
                    image--;
                }
            }
            tempsPrecedent = tempsActuel;

        }
        else
        {
           SDL_Delay(120-(tempsActuel - tempsPrecedent));
        }
        if(tour==0&&image<=8)
        {
            select . x  = 0;
            select . y  =36*image;
            select.h=36;
            select.w=press_start->w;
        }
        if(image>8||tour==1)
        {
            select . x  = 0;
            select . y  =36*image;
            select.h=36;
            select.w=press_start->w;
            tour=1;
            if(image==1)
            {
                tour=0;
            }
        }
        print_image(screen,titre_2,positiontitre_2.x,positiontitre_2.y,select_titre_2,i,255,255,255,mustcontinue);
        if(i>=25&&aff==0)
        {
            aff=1;
            i=0;
        }
        if(aff==1)
        {
            print_image(screen,titre_1,positiontitre_1.x,positiontitre_1.y,select_titre_1,i,255,255,255,mustcontinue);
        }
        if((i>=25)&(aff==1))
        {
            i=0;
            aff=2;
        }
        if(aff==2)
        {
            print_image(screen,press_start,positionstart.x,positionstart.y,select,i,255,255,255,mustcontinue);
            print_image(screen,credit,position_credit.x,position_credit.y,select_credit,i,255,255,255,mustcontinue);
        }
        SDL_Flip(screen);
    }
    SDL_FreeSurface(press_start);
    SDL_FreeSurface(titre_1);
    SDL_FreeSurface(titre_2);
    SDL_FreeSurface(credit);
    Mix_FreeMusic(musique);
}
