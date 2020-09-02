#ifndef __FONCTIONS_EXO3__
#define __FONCTIONS_EXO3__

#include "API_Grille.h"
#include "Liste_case.h"
#include "Entete_Fonctions.h"

typedef struct {
    int dim; /*dimension de la grille*/
    int nbcl; /*nombre de couleurs*/

    ListeCase Lzsg; /*Liste des cases de la zone Zsg*/
    ListeCase *B; /*Tableau de listes de cases de la bordure*/
    int **App; /* Tableau a double entree des appartenances*/
} S_Zsg;



/*initialise la structure*/
void init_Zsg (S_Zsg *Z, int dim, int nbcl);

/*Ajoute une cas edans la liste Lszg*/
int ajoute_Zsg (S_Zsg *Z, int i, int j);

/*Ajoute une case dnas la bordure d'une couleur cl donnée*/
int ajoute_Bordure(S_Zsg *Z, int i, int j, int cl);

/*Renvoie vrai si une case est dans LZsg*/
int appartient_Zsg(S_Zsg *Z, int i, int j);

/*Renvoie vrai si une case est dans la bordure de couleur cl donnée*/
int appartient_Bordure(S_Zsg *Z, int i, int j, int cl);

/*Mettre à jour S_Zsg et retourne le nombre de case qui a été ajouté à Lzsg*/  
int agrandit_Zsg (int **M, S_Zsg *Z , int cl, int k, int l);

#endif  /* __FONCTIONS_EXO3__ */
