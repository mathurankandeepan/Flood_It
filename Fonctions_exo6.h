#ifndef __FONCTIONS_EXO6__
#define __FONCTIONS_EXO6__

#include "API_Grille.h"
#include "Liste_case.h"
#include "Entete_Fonctions.h"
#include "Fonctions_exo4.h"
#include "Fonctions_exo5.h"

/* Structure qui recupere le premier et le dernier element d'une FILE
   de Cellule_som */
typedef struct file{
    Cellule_som *first;
    Cellule_som *last;
} File ;

/* Initialise la liste doublement chainée*/
void init_File(File *list);

/* Detruit la liste double chainée */
void detruit_File(File *list);

/* Enleve en tete de la liste doublement chaine et recupere le sommet*/
void enleve_tete_File (File *list , Sommet **sommet);

/* Ajoute en queue de la liste doublement chaine de Cellule_som*/
void ajoute_queue_File(File *list , Sommet *sommet );

/* Reset les distances de tous les sommets à 0*/
void reset_distance_sommet (Graphe_zone *graphe );

/* Recupère dans res une Cellule_som correspondant au plus court chemin entre départ et arrive*/
void plus_court_chemin( Graphe_zone *graphe , Sommet *depart, Sommet *arrive, Cellule_som **res );



#endif  /* __FONCTIONS_EXO6__ */
