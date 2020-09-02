#ifndef __FONCTIONS_EXO8__
#define __FONCTIONS_EXO8__

#include "API_Grille.h"
#include "Liste_case.h"
#include "Entete_Fonctions.h"
#include "Fonctions_exo4.h"
#include "Fonctions_exo5.h"
#include "Fonctions_exo6.h"
#include "Fonctions_exo7.h"

typedef struct {
    int dim; /* Dimension de la grille */
    int nbcl; /* Nombre de couleurs */
    int tailleCligne; /* Nombre de case sur une ligne du contour */
    int tailleCtotal; /* Nombre de case totale dans le Contour */
    int *tab; /* Tableau de taille nbcl recupérant le nombre de case de chaque couleur dans la première case du contour */

    Bordure_Zsg *B; /*Tableau de listes de pointeurs sur sommets-zone*/
    Graphe_zone *graphe; /* Graphes de sommets de la grille*/
    Bordure_Zsg *Contour; /*Tableau de listes de pointeurs sur sommets-zone*/

} Zsg2_graphe;

/* Initialise la stucture Zsg2 */
void init_Zsg2_graphe(Zsg2_graphe *Z , int dim , int nbcl, int tailleCligne); 

/* Initialise le countour */
void init_Contour (Zsg2_graphe *Z, int tailleCtotal, int dim_moit );

/* Enlève le premier élement de cell[i] et le récupère dans sommet */
void enleve_tete_Bordure_Zsg ( Bordure_Zsg *cell, int i ,Sommet **sommet );

/* Reset les valeurs du tableau à 0*/
void init_tab (int *tab, int nbcl);

/* Regarde le premier sommet de chaque case du tableau du contour, et incrémente
   Z->tab[cl] pour chaque couleur de chaque sommet */
void mis_a_jour_Contour_tab (Zsg2_graphe *Z ,int tailleCtotale);

/* Retourne la couleur la plus représentée sur la première ligne du contour grace à tab*/
int max_tab_contour( int *tab, int nbcl );

/* Récupère dans File des Cellule_som rangés dans un ordre basé sur le max
   pour atteindre tout le contour le plus rapidement possible*/
void Creation_File_Contour (Zsg2_graphe *Z ,int tailleCtotale , File **File);


/* Detruit Zsg2_graphe*/
void detruit_Zsg2_graphe(Zsg2_graphe *Z , int dim , int nbcl, int tailleCligne );

/* Mettre à jour Zsg2_graphe et retourne le nombre de case qui a été ajouté à Lzsg*/  
void agrandit_Zsg2_graphe (Zsg2_graphe *Z , int cl);

/* Refresh la grille de la Zsdg2_graphe */
void Affichage_Grille_Graphe2( Zsg2_graphe *Z, Grille *G, int dim, int cl);



#endif  /* __FONCTIONS_EXO8__ */
