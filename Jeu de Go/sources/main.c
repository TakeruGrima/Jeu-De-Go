#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDl/SDL_mixer.h>
#include "fonctions_techniques.h"
#include "title_screen.h"
#include "jeu.h"
#include "syst_jeu.h"
#include "macros.h"

int main(int argc, char *argv[])
{
    //déclaration des surfaces principales:
    SDL_Surface* screen = NULL; // déclaration de l'ecran principal
    SDL_Surface* plateau = NULL;// déclaration du plateau
    SDL_Surface *sous_plateau=NULL;
    SDL_Surface *victoire=NULL;

    //déclaration des "selections"(élément de la surface séléctionné)
    SDL_Rect select_plateau,select_sous_plateau,position_sous_plateau;
    SDL_Rect select_victoire,position_victoire;
    int j,i,choix;
    int param=-1;
    int nbelCapt=0;

    int mustContinue = TRUE; // Indicateur boolean pour la boucle principale

    char p[19][19]={{'O'}};
    int charger=FALSE;
    int caractereActuel=0;
    float *score;
    int *tab_1D;
    int tour_passer=0,pass_noir=FALSE,pass_blanc=FALSE,aff_victoire=FALSE;
    char joueur='N';

    int imgFlags = IMG_INIT_JPG|IMG_INIT_PNG|IMG_INIT_TIF; // Flags pour charger le support du JPG, PNG et TIF

    plateau=SDL_LoadBMP("./data/plateau.bmp");//chargement de l'image du plateau
    sous_plateau=IMG_Load("./data/sous_plateau.png");
    victoire=IMG_Load("./data/victoire.png");

    //initialisation de la selection du plateau(ici on prend l'intégralité de l'image)
    select_plateau.x=0;//abscisse ou commence la séléction
    select_plateau.y=0;//ordonnée ou commence la séléction
    select_plateau.w=plateau->w;//taille en abscisse
    select_plateau.h=plateau->h;//taille en ordonnée

    select_sous_plateau.x=0;
    select_sous_plateau.y=0;
    select_sous_plateau.w=sous_plateau->w;
    select_sous_plateau.h=sous_plateau->h;

    position_sous_plateau.x=0;
    position_sous_plateau.y=select_plateau.h;
    // Demarre SDL
    if ( SDL_Init(SDL_INIT_VIDEO) == -1 )
    {
        fprintf(stderr,"Erreur lors de l'initialisation de la SDL\n");
        return -1;
    }

    SDL_WM_SetCaption("Jeu de Go", NULL);

    if ( IMG_Init(imgFlags) != imgFlags )
    {
        fprintf(stderr,"Erreur lors de l'initialisation de la SDL_image : '%s'\n",IMG_GetError());
        cleanup();
        return -1;
    }

    // Creer la fenetre
    screen = SDL_SetVideoMode(SCREEN_W,SCREEN_H,32,SDL_SWSURFACE | /*SDL_FULLSCREEN |*/ SDL_DOUBLEBUF);
	if ( screen == NULL )
	{
	    printf("Erreur lors de l'ouverture de la fenetre\n");
	    cleanup();
        return -2;
	}
    SDL_ShowCursor(0);//on désactive l'affichage de la souris
    title_screen(screen,&mustContinue);
    if(mustContinue==TRUE)
    {
        print_image(screen,plateau,0,0,select_plateau,255,255,255,255,&mustContinue);
        SDL_Flip(screen);
        charger=menu(screen,&mustContinue,p);
    }
    if(mustContinue==TRUE)
    {
        print_image(screen,plateau,0,0,select_plateau,255,255,255,255,&mustContinue);
        SDL_Flip(screen);
        int IA_active=FALSE;
        load(p,charger,&joueur,&choix);
        if(charger==FALSE)
        {
             choix=choix_adversaire(screen,&mustContinue);
        }
    }
    if(mustContinue==TRUE)
    {
        screen = SDL_SetVideoMode(SCREEN_W2,SCREEN_H2,32,SDL_SWSURFACE | /*SDL_FULLSCREEN |*/ SDL_DOUBLEBUF);
        print_image(screen,sous_plateau,position_sous_plateau.x,position_sous_plateau.y,select_sous_plateau,255,255,0,0,&mustContinue);
        SDL_Flip(screen);
    }
    // Boucle principale
    select_victoire.x=0;
    select_victoire.y=0;
    select_victoire.h=38;
    position_victoire.y=(SCREEN_H-select_victoire.h)/2;
	while ( mustContinue==TRUE )
	{
	    SDL_Event event;
	    SDL_WaitEvent(&event);

        switch(event.type)
        {
            case SDL_QUIT:
                mustContinue=FALSE;
                // Detecte si on clique sur la croix
            break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE://appui sur la touche escape est on ferme le programme
                        mustContinue=FALSE;
                        break;
                    default:
                    break;
                }
            break;
        }
        print_image(screen,plateau,0,0,select_plateau,255,255,255,255,&mustContinue);
        if(joueur=='N')
        {
             place_pion(screen,plateau,p,'N',&mustContinue,&param,&nbelCapt,choix,&pass_noir,pass_blanc);
        }
        if(pass_blanc==TRUE && pass_noir==FALSE)
        {
            pass_blanc=FALSE;
        }
        tab_1D=tab_2D_to_1D(p);
        score=calculeScore(tab_1D);
        print_image(screen,sous_plateau,position_sous_plateau.x,position_sous_plateau.y,select_sous_plateau,255,255,0,0,&mustContinue);
        affiche_score(screen,*score,'N');
        affiche_score(screen,*(score+1),'B');
        if(*score>*(score+1) && pass_blanc==TRUE && pass_noir==TRUE)
        {
            mustContinue=FALSE;
            aff_victoire=TRUE;
            select_victoire.y=0;
            select_victoire.w=338;
            position_victoire.x=(SCREEN_W-select_victoire.w)/2;
            print_image(screen,victoire,position_victoire.x,position_victoire.y,select_victoire,255,255,0,0,&mustContinue);
        }
        else if(*(score+1)>*score && pass_blanc==TRUE && pass_noir==TRUE)
        {
            mustContinue=FALSE;
            aff_victoire=TRUE;
            select_victoire.y=38;
            select_victoire.w=374;
            position_victoire.x=(SCREEN_W-select_victoire.w)/2;
            print_image(screen,victoire,position_victoire.x,position_victoire.y,select_victoire,255,255,0,0,&mustContinue);
        }
        if(mustContinue==TRUE)
        {
             place_pion(screen,plateau,p,'B',&mustContinue,&param,&nbelCapt,choix,&pass_blanc,pass_noir);
        }
        SDL_Flip(screen);
        tab_1D=tab_2D_to_1D(p);
        score=calculeScore(tab_1D);
        print_image(screen,sous_plateau,position_sous_plateau.x,position_sous_plateau.y,select_sous_plateau,255,255,0,0,&mustContinue);
        affiche_score(screen,*score,'N');
        affiche_score(screen,*(score+1),'B');
		if(*score>*(score+1) && pass_blanc==TRUE && pass_noir==TRUE && aff_victoire==FALSE)
        {
            mustContinue=FALSE;
            aff_victoire=TRUE;
            select_victoire.y=0;
            select_victoire.w=338;
            position_victoire.x=(SCREEN_W-select_victoire.w)/2;
            print_image(screen,victoire,position_victoire.x,position_victoire.y,select_victoire,255,255,0,0,&mustContinue);
        }
        else if(*(score+1)>*score && pass_blanc==TRUE && pass_noir==TRUE && aff_victoire==FALSE)
        {
            mustContinue=FALSE;
            aff_victoire=TRUE;
            select_victoire.y=38;
            select_victoire.w=374;
            position_victoire.x=(SCREEN_W-select_victoire.w)/2;
            print_image(screen,victoire,position_victoire.x,position_victoire.y,select_victoire,255,255,0,0,&mustContinue);
        }
        else if(pass_blanc==FALSE && pass_noir==TRUE)
        {
            pass_noir=FALSE;
        }
        SDL_Flip(screen);
        tour_passer=0;
        joueur='N';
	}
	SDL_Delay(1000);
	free(score);
	free(tab_1D);
	SDL_FreeSurface(sous_plateau);
    SDL_FreeSurface(plateau);
    SDL_FreeSurface(victoire);
    SDL_FreeSurface(screen);
    cleanup();
    return EXIT_SUCCESS;
}
