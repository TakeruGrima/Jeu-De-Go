#include <stdio.h>
#include <stdlib.h>
#include "macros.h"

int libertes(char p[][19],int x,int y)
{
    int lib;
    int chaine[4]={0};

    if(p[x+1][y]=='O')
    {
        lib++;
    }
    else if(p[x+1][y]!=p[x][y])
    {
        lib--;
    }
    else
    {
        chaine[1]=1;//il y a un pion a x+1 on stocke 1 dans chaine[1]
    }
    if(p[x-1][y]=='O')
    {
        lib++;
    }
    if(p[x][y+1]=='O')
    {
        lib++;
    }
    if(p[x][y-1]=='O')
    {
        lib++;
    }
}
