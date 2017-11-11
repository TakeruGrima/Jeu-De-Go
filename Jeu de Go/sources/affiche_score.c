#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDl/SDL_mixer.h>
#include "fonctions_techniques.h"
#include "jeu.h"
#include "macros.h"

void affiche_score(SDL_Surface *screen,float score,char joueur)
{
    SDL_Surface *chiffre_score;
    SDL_Rect taille_chiffre,position_chiffre;
    int continuer=TRUE;
    char chaine[5];
    int i,chiffre;

    chiffre_score=IMG_Load("./data/chiffre_score.png");
    if(score>=100)
    {
        chiffre=(int)score/100;
        sprintf(chaine,"%d",chiffre);
        score=score-chiffre*100;
    }
    else
    {
        chaine[0]=' ';
    }
    if(score>=10)
    {
        chiffre=(int)score/10;
        sprintf(&chaine[1],"%d",chiffre);
        score=score-chiffre*10;
    }
    else
    {
        chaine[1]=' ';
    }
    if(score>=1)
    {
        chiffre=(int)score/1;
        sprintf(&chaine[2],"%d",chiffre);
        score=score-chiffre;
    }
    else
    {
        chaine[2]='0';
    }
    chaine[3]=',';
    if(score>=0.1)
    {
        chiffre=(int)(score*10)/1;
        sprintf(&chaine[4],"%d",chiffre);
        score=score-(chiffre)/10;
    }
    else
    {
        chaine[4]='0';
    }
    if(joueur=='N')
    {
         position_chiffre.x=64;
    }
    else
    {
        position_chiffre.x=314;
    }
    position_chiffre.y=115+371;
    for(i=0;i<5;i++)
    {
        printf("%c",chaine[i]);
        switch(chaine[i])
        {
        case '0':
            taille_chiffre.x=0;
            taille_chiffre.y=0;
            taille_chiffre.w=7;
            taille_chiffre.h=14;
        break;
        case '1':
            taille_chiffre.x=16;
            taille_chiffre.y=0;
            taille_chiffre.w=6;
            taille_chiffre.h=14;
        break;
        case '2':
            taille_chiffre.x=32;
            taille_chiffre.y=0;
            taille_chiffre.w=7;
            taille_chiffre.h=14;
        break;
        case '3':
            taille_chiffre.x=48;
            taille_chiffre.y=0;
            taille_chiffre.w=7;
            taille_chiffre.h=14;
        break;
        case '4':
            taille_chiffre.x=64;
            taille_chiffre.y=0;
            taille_chiffre.w=8;
            taille_chiffre.h=14;
        break;
        case '5':
            taille_chiffre.x=80;
            taille_chiffre.y=0;
            taille_chiffre.w=7;
            taille_chiffre.h=14;
        break;
        case '6':
            taille_chiffre.x=96;
            taille_chiffre.y=0;
            taille_chiffre.w=7;
            taille_chiffre.h=14;
        break;
        case '7':
            taille_chiffre.x=112;
            taille_chiffre.y=0;
            taille_chiffre.w=8;
            taille_chiffre.h=14;
        break;
        case '8':
            taille_chiffre.x=128;
            taille_chiffre.y=0;
            taille_chiffre.w=7;
            taille_chiffre.h=14;
        break;
        case '9':
            taille_chiffre.x=144;
            taille_chiffre.y=0;
            taille_chiffre.w=7;
            taille_chiffre.h=14;
        break;
        case ',':
            taille_chiffre.x=161;
            taille_chiffre.y=0;
             taille_chiffre.w=4;
            taille_chiffre.h=14;
        break;
        case ' ':
            taille_chiffre.x=7;
            taille_chiffre.y=0;
            taille_chiffre.w=7;
            taille_chiffre.h=14;
        break;
        }
        print_image(screen,chiffre_score,position_chiffre.x,position_chiffre.y,taille_chiffre,255,255,255,255,&continuer);
        position_chiffre.x=position_chiffre.x+taille_chiffre.w;
        SDL_Flip(screen);
    }
    SDL_FreeSurface(chiffre_score);
}
