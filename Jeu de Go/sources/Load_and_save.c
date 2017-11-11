#include <stdio.h>
#include <stdlib.h>
#include "syst_jeu.h"
#include "macros.h"


void load(char p[][19],int charger,char *joueur,int *choix)
{
    int caractereActuel=0;
    int i,j;
    FILE* sav;
    sav=fopen("./data/sav.txt","r");

    if (sav != NULL && charger==TRUE)
    {
        // Boucle de lecture des caractères un à un
        do
        {
            caractereActuel = fgetc(sav); // On lit le caractère
            if(caractereActuel!='\n' && j!=19)
            {
                p[i][j]=(char)caractereActuel;
            }
            else if(j==19&& i==0)
            {
                *joueur=caractereActuel;
            }
            else if(j==19)
            {
                if(caractereActuel=='1')
                {
                    *choix=2;
                }
                else if(caractereActuel=='0')
                {
                    *choix=1;
                }
            }
            if(i==19)
            {
                j++;
                i=0;
            }
            else if(i<19)
            {
                i++;
            }
            if(j==20)
            {
                caractereActuel=EOF;
            }
        } while (caractereActuel != EOF); // On continue tant que fgetc n'a pas retourné EOF (fin de fichier)

        fclose(sav);
    }
}

void save(char p[][19],char joueur,int IA_active)
{
    int i,j;
    char IA;
    FILE* sav;
    sav=fopen("./data/sav.txt","w+");
    if (sav != NULL)
    {
        if(IA_active==1)
        {
            IA='1';
        }
        else
        {
            IA='0';
        }
        for(j=0;j<19;j++)
        {
            for(i=0;i<19;i++)
            {
                fputc(p[i][j],sav);
            }
            fprintf(sav,"\n");
        }
        fputc(joueur,sav);
        fputc(IA,sav);
    }
    fclose(sav);
}
