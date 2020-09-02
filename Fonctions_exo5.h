#ifndef __FONCTIONS_EXO5__
#define __FONCTIONS_EXO5__

#include "API_Grille.h"
#include "Liste_case.h"
#include "Entete_Fonctions.h"
#include "Fonctions_exo4.h"

typedef struct bordure_Zsg{
    int len; /* Nombre de cases totales dans la liste chainée de sommet de la même couleur */
    Cellule_som * som;  /* Liste chainee des sommets du graphes de la même couleur */
} Bordure_Zsg;


typedef struct {
    int dim; /* Dimension de la grille*/
    int nbcl; /* Nombre de couleurs*/

    Cellule_som *Zone; /* Liste chainée des sommets de la zone*/
    Bordure_Zsg *B; /*Tableau de listes de pointeurs sur sommets-zone de la bordure*/
    Graphe_zone *graphe; /* Graphes de sommets de la grille*/

} Zsg_graphe;


/* Initialise la stucture Bordule_Zone*/
void init_Bordure_Zsg ( Bordure_Zsg *cell);

/* Initialise la stucture Zsg */
void init_Zsg_graphe( Zsg_graphe *Z , int dim , int nbcl); 

/* Detruit Bordure_Zsg*/
void detruit_Bordure_Zsg( Bordure_Zsg *B);

/* Detruit Zsg_graphe*/
void detruit_Zsg_graphe( Zsg_graphe *Z , int dim , int nbcl );

/* Ajoute un sommet à la case de couleur cl de la bordure */
void ajoute_Bordure_Zsg ( Bordure_Zsg *Bordure , Sommet *sommet, int cl );

/* Affiche la bordure complete (a servi pour les tests*/
void affiche_Bordure ( Bordure_Zsg *B, int nbcl);

/* Mettre à jour Zsg_graphe en particulier la bordure */  
void agrandit_Zsg_graphe ( Zsg_graphe *Z , int cl);

/* Renvoie 1 si la bordure est vide sinon 0 */
int bordure_vide ( Bordure_Zsg *B , int nbcl);

/* Renvoie la couleur de la bordure ayant le plus de sommets*/
int bordure_max1( Bordure_Zsg *B , int nbcl);

/* Refresh l'affichage de la grille*/
void Affichage_Grille_Graphe( Zsg_graphe *Z, Grille *G , int dim , int cl );  



#endif  /* __FONCTIONS_EXO5__ */
