#include "macros.h"
#ifndef SYST_JEU_H_INCLUDED
#define SYST_JEU_H_INCLUDED

//conversion tableau:
void tab_1D_to_2D(int tab_1D[19*19],char p[19][19]);
int *tab_2D_to_1D(char tab_2D[][19]);
int * correspondanceIndice(int n);

//fonctions liées a la capture
int * voisin(int p,int *cmp);
int testexist(int nb, int *tab, int cmp);
int getGroupe(int p,int data[maxSizeCarre], int *g, int nbelgr);
int VerifierKO(int p, int data[maxSizeCarre],int nbElCapt,int param);
int capturer(int n, int data[maxSizeCarre], int * ret);
int placementPossible(int p, int data[maxSizeCarre], int nbElCapt,int param, char joueur);
int calculeLiberte(int p, int data[maxSizeCarre],int *libofp);
int nbCasePlein(int data[maxSizeCarre]);
float * calculeScore( int data[maxSizeCarre]);
int IA(int data[maxSizeCarre],int nbcapt,int param,int i_test,int *passe_tour,int tour_passe,int*libofp,char joueur);
int **territoire(int data[maxSizeCarre],int joueur);

//fgnction load ans save pour la sauvegarde
void load(char p[][19],int charger,char *joueur,int *choix);
void save(char p[][19],char joueur,int IA_active);

#endif // SYST_JEU_H_INCLUDED
