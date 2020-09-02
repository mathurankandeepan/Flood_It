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
    int tailleCligne; /* Nombre de case sur le contour pour une case */
    int tailleCtotal; /* Nombre de case totale dans le Contour */
    int *tab; /* Tableau de taille nbcl recupérant le nombre de case de cette couleur dans la première case du contour */

    Bordure_Zsg *B; /*Tableau de listes de pointeurs sur sommets-zone*/
    Graphe_zone *graphe; /* Graphes de sommets de la grille*/
    Bordure_Zsg *Contour; /*Tableau de listes de pointeurs sur sommets-zone*/

} Zsg2_graphe;

/* Initialise la stucture Zsg2 */
void init_Zsg2_graphe(Zsg2_graphe *Z , int dim , int nbcl, int tailleCligne); 

/* Detruit Zsg2_graphe*/
void detruit_Zsg2_graphe(Zsg2_graphe *Z , int dim , int nbcl, int tailleCligne );

/* Mettre à jour Zsg_graphe et retourne le nombre de case qui a été ajouté à Lzsg*/  
void agrandit_Zsg2_graphe (Zsg2_graphe *Z , int cl);


void Affichage_Grille_Graphe2( Zsg2_graphe *Z, Grille *G, int dim, int cl);



#endif  /* __FONCTIONS_EXO8__ */
