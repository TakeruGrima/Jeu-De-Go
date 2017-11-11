#include <stdio.h>
#include <stdlib.h>
#include "macros.h"
#include "syst_jeu.h"

int *tab_2D_to_1D(char tab_2D[][19])
{
    int *tab_1D;
    int i,j;

    tab_1D = (int *)malloc(19*19*sizeof(int)); // Allocation de la mémoire
    for(j=0;j<19;j++)
    {
        for(i=0;i<19;i++)
        {
            if(tab_2D[i][j]=='N')
            {
                tab_1D[i+19*j]=1;
            }
            else if(tab_2D[i][j]=='B')
            {
                tab_1D[i+19*j]=2;
            }
            else
            {
                tab_1D[i+19*j]=0;
            }
        }
    }
    return tab_1D;
}

void tab_1D_to_2D(int tab_1D[19*19],char p[19][19])
{
    int u,i,j;
    for(u=0;u<19*19;u++)
    {
        i=u%19;
        j=(u-i)/19;
        if(tab_1D[u]==1)
        {
            p[i][j]='N';
        }
        else if(tab_1D[u]==2)
        {
            p[i][j]='B';
        }
        else
        {
            p[i][j]='O';
        }
    }
}
