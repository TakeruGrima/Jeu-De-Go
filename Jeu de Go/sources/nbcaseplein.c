#include <stdio.h>
#include <stdlib.h>
#include "syst_jeu.h"
#include "macros.h"

int nbCasePlein(int data[maxSizeCarre]){
    int i;
    int ret=0;
    for(i=0;i<maxSizeCarre;i++){
       if(data[i]!=0){
        ret++;
       }
    }
    return ret;
}
