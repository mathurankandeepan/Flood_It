#ifndef __FONCTIONS_EXO4__
#define __FONCTIONS_EXO4__

#include "API_Grille.h"
#include "Liste_case.h"
#include "Entete_Fonctions.h"


typedef struct sommet Sommet;

/* Element d'une liste chaine\^in\'ee de pointeurs sur Sommets */
typedef struct cellule_som{
    Sommet * sommet;
    struct cellule_som * suiv;
} Cellule_som;

struct sommet {
    int num; /* Numero du sommet (sert uniquement à l'affichage) */
    int cl; /* Couleur d'origine du sommet-zone */
    ListeCase cases ; /* Listes des cases du sommet-zone */
    int nbcase_som; /* Nombre de cases de cette liste */
    Cellule_som * sommet_adj; /* Liste des arêtes pointeurs sur les sommets adjacents */
    int marque; /* 0 si dans la zone, 1 si voisin, 2 si non-visité */
    int distance; /* Nombre d'aretes reliant ce sommet a la racine
                    du parcours en largeur */
    Sommet *pere; /* Pere du sommet dans l'arborescene du parcours en largeur */
};


typedef struct graphe_zone{
    int nbsom; /* Nombre de sommet dans le graphe */
    Cellule_som * som;  /* Liste chainee des sommets du graphes */
    Sommet ***mat; /* Matrice de pointeurs sur les sommets indiquant a quel sommet appartient une 
                    case (i,j) de la grille */
}Graphe_zone;


/* Initialise la structure Sommet*/
void init_Sommet(Sommet *sommet, int nbsom, int cl);

/* Initialise la structure Cellule_nom*/
void init_Cellule_som(Cellule_som **cell);

/* Initialise la structure Graphe_zone*/
void init_Graphe_zone(Graphe_zone *graphe, int dim);

/* Detruit sommet */
void detruit_sommet (Sommet *sommet);

/* Detruit graphe_zone */ 
void detruit_Graphe_zone(Graphe_zone *graphe, int dim);

/* Ajoute un élement Sommet à la liste Cellule_nsom*/
int ajoute_liste_sommet(Sommet *sommet, Cellule_som **cell );

/* Détruit une liste chainée de Cellule_som sans détruire les sommets*/
void detruit_liste_sommet(Cellule_som **cell);

/* Mis à jour de S1 et S2 en indiquant qu'ils deviennent voisins*/
void ajoute_voisin( Sommet *s1, Sommet *s2);

/* Renvoie vrai ssi S1 et S2 sont adjacents */
int adjacent ( Sommet *s1, Sommet *s2);

/* Crée le graphe tout entier */
void cree_graphe_zone(Graphe_zone *graphe, int **M, int dim);

/* Affichage sommet*/
void affichage_sommet ( Sommet *sommet);

/* Affiche sous format texte la zone graphe*/
void affichage_graphe_zone(Graphe_zone *graphe);

/* Affiche la zone de la grille*/
void affichage_Cellule_som (Cellule_som *list);

/* Affiche la grille sous forme de matrice */
void affichage_matrice ( Graphe_zone *graphe, int dim );



#endif  /* __FONCTIONS_EXO4__ */