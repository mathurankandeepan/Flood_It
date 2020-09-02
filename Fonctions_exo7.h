#ifndef __FONCTIONS_EXO7__
#define __FONCTIONS_EXO7__

#include "API_Grille.h"
#include "Liste_case.h"
#include "Entete_Fonctions.h"
#include "Fonctions_exo4.h"
#include "Fonctions_exo5.h"
#include "Fonctions_exo6.h"

/* Force les 7 points stratégiques que nous avons forcé */
void points_strategiques( Graphe_zone *graphe, Cellule_som **res, int dim_moit, int last);

/* Cette fonction utilise encore une fois un parcours en largeur mais différent de celui de l'exercice 6 car il n'y a pas 
   de retour anticipé. */
/* Pose la distance et le père de chaque sommet du graphe en fonction du parcours en largeur*/
void BFS_graphe_complet( Graphe_zone *graphe , Sommet *depart);

/* Recupere dans Chemin le chemin partant de départ et arrivant à arrivé */
void plus_court_chemin_sommet (Sommet *depart, Sommet *arrive, Cellule_som **chemin );

/* Recupere dans Chemin la suite successive des chemins partant de départ et arrivant à différents éléments de list */
void plus_court_chemin_Cellule_som( Sommet *depart, Cellule_som *list, Cellule_som **chemin  );

/* Copie la l'inverser de la Cellule_som dans res */
void inverser(Cellule_som *som, Cellule_som **res);


#endif  /* __FONCTIONS_EXO7__ */
