#ifndef __ENTETE_FONCTIONS__
#define __ENTETE_FONCTIONS__

#include "API_Grille.h"
#include "Liste_case.h"
#include <unistd.h>

#include "Fonctions_exo4.h"

#define VITESSE 0.1

/* Refresh la Grille */
void Affichage_Grille (int **M, Grille *G, int dim);

/* Exercice 1*/

/* Retourne dans L la liste des cases de meme couleur que la case i,j
   et met -1 dans ces cases */
void trouve_zone_rec(int **M, int dim, int i, int j, int *taille, ListeCase *L);

/* Algorithme tirant au sort une couleur: il utilise la fonction recursive pour determiner la Zsg */
int sequence_aleatoire_rec(int **M, Grille *G, int dim, int nbcl, int aff);

/* Exercice 2*/

/* Retourne dans L la liste des cases de meme couleur que la case M[0][0]
   et met -1 dans ces cases */
void trouve_zone_imp(int **M, int dim, int i, int j, int *taille, ListeCase *L);

/* Algorithme tirant au sort une couleur: il utilise la fonction itéraive pour determiner la Zsg */
int sequence_aleatoire_imp(int **M, Grille *G, int dim, int nbcl, int aff);

/* Exercice 3*/
int sequence_aleatoire_rapide(int **M, Grille *G, int dim, int nbcl, int aff);

/* Exercice 5 */
/* Stratégie qui choisit la couleur en fonction de la couleur la plus representé dans la bordure */
int max_bordure_graphe ( int **M , Grille *G , int dim , int nbcl , int aff);

/* Exercice 6*/
/* Applique la stratégie de la diagonale puis max_bordure_graphe */
int BFS_max_bordure_graphe ( int **M , Grille *G , int dim , int nbcl , int aff);

/* Exercice 7*/
/* Applique plus petit chemin un par un à des points strategiques comme le contour puis max_bordure_graphe */
int BFS_max_bordure_graphe_croix ( int **M , Grille *G , int dim , int nbcl , int aff);

/* Exerice 8*/
/* Applique plus petit chemin en meme temps (règle du max de cl) à des points strategiques comme le contour puis max_bordure_graphe */
int BFS_Contour ( int **M , Grille *G , int dim , int nbcl , int tailleCligne , int aff);

#endif  /* __ENTETE_FONCTIONS__ */
