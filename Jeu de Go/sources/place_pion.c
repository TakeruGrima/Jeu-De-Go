#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDl/SDL_mixer.h>
#include "fonctions_techniques.h"
#include "jeu.h"
#include "macros.h"
#include "syst_jeu.h"

void place_pion(SDL_Surface* ecran,SDL_Surface* plateau,char p[][19],char joueur,int *continuer, int * param, int * nbelCapt,int choix,int *passe_tour,int tour_passe)
{
     SDL_Surface* pions=NULL;
     SDL_Surface *passe=NULL;

     SDL_Rect select_pion,select_plateau;//4 variable dans 1 c'est une structure
     SDL_Rect select_passe,position_passe;

     SDL_Event event;
     int x,y,cont_deplace,event_x,event_y;
     int case_x,case_y,i_IA,i_test=0;
     int *tab_1D;
     int IA_active=FALSE;
     int menu_bas=FALSE;
     int *libofp=NULL;
     int place_possible=FALSE;
     int erreur_seg=FALSE;
     pions=SDL_LoadBMP("./data/pions.bmp");
     passe=IMG_Load("./data/passe.png");

     if(joueur=='N')
     {
         select_pion.x=0;
     }
     else if(joueur=='B')
     {
         select_pion.x=PION_W;
     }
     select_pion.y=0;
     select_pion.w=PION_W;
     select_pion.h=PION_H;
     select_plateau.x=0;
     select_plateau.y=0;
     select_plateau.w=plateau->w;
     select_plateau.h=plateau->h;

     cont_deplace = TRUE;
     print_image(ecran,plateau,0,0,select_plateau,255,255,255,255,continuer);
     refresh_plateau(ecran,pions,select_pion,p,continuer);
     SDL_Flip(ecran);
    while(cont_deplace==TRUE && joueur=='B'&& choix==2)
    {
            IA_active=TRUE;
            tab_1D=tab_2D_to_1D(p);
            libofp = (int *)malloc(maxSizeCarre*sizeof(int));  // Allocation de la mémoire
            i_IA=IA(tab_1D,*nbelCapt,*param,i_test,passe_tour,tour_passe,libofp,joueur);
            place_possible=placementPossible(i_IA,tab_1D,*nbelCapt,*param,joueur);
            if(place_possible==TRUE && *passe_tour==FALSE)
            {
                tab_1D[i_IA]=2;
                *nbelCapt=capturer(i_IA,tab_1D,param);
                cont_deplace=FALSE;
                tab_1D_to_2D(tab_1D,p);
                refresh_plateau(ecran,pions,select_pion,p,continuer);
                SDL_Flip(ecran);
            }
            else if(place_possible==FALSE && *passe_tour==FALSE)
            {
                while(place_possible==FALSE)
                {
                     if(libofp+1!=NULL)
                     {
                         libofp=libofp+1;
                         place_possible=placementPossible(*libofp,tab_1D,*nbelCapt,*param,joueur);
                     }
                     else
                     {
                         place_possible=TRUE;
                         erreur_seg=TRUE;
                     }
                }
                if(erreur_seg==FALSE)
                {
                    place_possible=TRUE;
                    i_IA=*libofp;
                }
                else
                {
                    place_possible=FALSE;
                }
            }
            if(*passe_tour==FALSE && place_possible==FALSE)
            {
                 cont_deplace=TRUE;
                 i_test=i_IA+1;
            }
            else if(*passe_tour==TRUE)
            {
                select_passe.x=0;
                select_passe.y=0;
                select_passe.w=105;
                select_passe.h=14;
                position_passe.x=(SCREEN_W-select_passe.w)/2;
                position_passe.y=0;
                cont_deplace=FALSE;
                print_image(ecran,passe,position_passe.x,position_passe.y,select_passe,255,255,0,0,continuer);
                SDL_Flip(ecran);
                SDL_Delay(700);
            }
    }
    if(choix==2)
    {
        IA_active=TRUE;
    }
     while ( cont_deplace==TRUE && IA_active==FALSE || (cont_deplace==TRUE && IA_active==TRUE && joueur=='N'))
	{
	    //printf("i= %d\n",i++);
	    SDL_WaitEvent(&event);

        // Detecte si on clique sur la croix
	    switch( event.type)
	    {
	        case SDL_QUIT:
            //On quitte le programme
            *continuer = FALSE;
            cont_deplace=FALSE;
            break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE://appui sur la touche escape est on ferme le programme
                        *continuer=FALSE;
                        cont_deplace=FALSE;
                    break;
                    case SDLK_RETURN:
                        *continuer=TRUE;
                        cont_deplace=TRUE;
                        pause(ecran,plateau,select_plateau,p,continuer,&cont_deplace,joueur,&IA_active);
                        print_image(ecran,plateau,0,0,select_plateau,255,255,255,255,continuer);
                        print_image(ecran,pions,x,y,select_pion,200,255,255,255,continuer);
                        refresh_plateau(ecran,pions,select_pion,p,continuer);
                        SDL_Flip(ecran);
                    break;
                    default:
                    break;
                }
            break;
            case SDL_MOUSEMOTION:
                menu_bas=FALSE;
                SDL_ShowCursor(FALSE);
                event_x=event.motion.x-PION_W-10;
                event_y=event.motion.y-PION_H-10;
                select_pion.w=PION_W;
                select_pion.h=PION_H;
                if(event_x<0)
                {
                    x=0;
                }
                else if(event_x>342)
                {
                    x=342;
                }
                else
                {
                    x=event_x;
                }
                if(event_y<0)
                {
                    y=0;
                }
                else if(event_y>342)
                {
                    SDL_ShowCursor(TRUE);
                    select_pion.w=0;
                    select_pion.h=0;
                    menu_bas=TRUE;
                }
                else
                {
                    y=event_y;
                }
                print_image(ecran,plateau,0,0,select_plateau,255,255,255,255,continuer);
                print_image(ecran,pions,x,y,select_pion,200,255,255,255,continuer);
                refresh_plateau(ecran,pions,select_pion,p,continuer);
                SDL_Flip(ecran);
            break;
            case SDL_MOUSEBUTTONDOWN:
                if(event.button.button==SDL_BUTTON_LEFT)
                {
                    menu_bas=FALSE;
                    cont_deplace=FALSE;
                    event_x=event.button.x;
                    event_y=event.button.y;
                    select_pion.w=PION_W;
                    select_pion.h=PION_H;
                    if(event_x<PION_W)
                    {
                        x=PION_W;
                    }
                    else if(event_x>361)
                    {
                        x=361;
                    }
                    else
                    {
                        x=event_x;
                    }
                    if(event_y<PION_H)
                    {
                        y=PION_H;
                    }
                    else if(event_y>371)
                    {
                        select_pion.w=0;
                        select_pion.h=0;
                        cont_deplace=TRUE;
                        menu_bas=TRUE;
                        if(event_y>371+61&&event_y<371+84 && event_x>120 && event_x<272)
                        {
                            *passe_tour=TRUE;
                            if(joueur=='N')
                            {
                                select_passe.y=14;
                                select_passe.w=91;
                            }
                            else
                            {
                                select_passe.y=0;
                                select_passe.w=105;
                            }
                            select_passe.x=0;
                            select_passe.h=14;
                            position_passe.x=(SCREEN_W-select_passe.w)/2;
                            position_passe.y=0;
                            print_image(ecran,passe,position_passe.x,position_passe.y,select_passe,255,255,0,0,continuer);
                            SDL_Flip(ecran);
                            cont_deplace=FALSE;
                            SDL_Delay(700);
                        }
                    }
                    else
                    {
                        y=event_y;
                    }
                    if(menu_bas==FALSE)
                    {
                        x=(x/19)*19;
                        y=((y)/19)*19;
                        y=y-19;
                        x=x-19;
                        case_x=x/19;
                        case_y=y/19;
                        tab_1D=tab_2D_to_1D(p);
                        tab_1D_to_2D(tab_1D,p);


                        if(placementPossible(case_x+19*case_y,tab_1D,*nbelCapt,*param,joueur)==TRUE)
                        {

                            p[case_x][case_y]=joueur;
                            //printf("je modifie ");
                            print_image(ecran,plateau,0,0,select_plateau,255,255,255,255,continuer);

                            tab_1D=tab_2D_to_1D(p);
                            *nbelCapt=capturer(case_x+19*case_y,tab_1D,param);
                             cont_deplace=FALSE;
                             *continuer=TRUE;
                            }
                            else
                            {
                                 //printf("je modifie pas");
                                 cont_deplace=TRUE;
                            }




                       /*
                            int * g;
                            g = (int *)malloc(sizeof(int));  // Allocation de la mémoire
                            if (g== NULL)
                            {
                                printf("allocation échouée");
                                exit(0);
                            }
                            int r=getGroupe(*param,tab_1D,g,0);
                            printf("nombre elem groupe capturé = %d\n",r);
                            printf("p = %d\n",case_x+19*case_y);
                            printf("le paramètre = %d\n",*param);

                         */

                            // une variable qui prend après chaque appel à la méthode capturer le nomre de pion capturé
                            // cette variale sera utilisé par la fonction vérifier KO
                            tab_1D_to_2D(tab_1D,p);
                            refresh_plateau(ecran,pions,select_pion,p,continuer);
                            SDL_Flip(ecran);
                    }
                }
            break;
		}
	}
    SDL_FreeSurface(pions);
}
