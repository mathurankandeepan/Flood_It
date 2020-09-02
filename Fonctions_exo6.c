#include "Fonctions_exo6.h"
#include "Fonctions_exo4.h"


#define INF 999999


void init_File(File *list){
   list->first = NULL;
   list->last = NULL;
}

void detruit_File(File *list){
    Cellule_som *tmp;
    Cellule_som*pelem = list->first;
    while(pelem)
    {
      tmp = pelem;
      pelem = pelem->suiv;
      free(tmp);
    }
    list->first = NULL;
    list->last = NULL;
}


void enleve_tete_File (File *list , Sommet **sommet){
    Cellule_som *tmp = list->first;
    *sommet = tmp->sommet;
    list->first = tmp->suiv;
    if(list->first == NULL)
        list->last = NULL;
    free(tmp);
}

void ajoute_queue_File(File *list , Sommet *sommet ){
    Cellule_som *nouv = malloc(sizeof(Cellule_som));
    nouv->sommet = sommet;
    nouv->suiv = NULL;
    if(list->last) 
        list->last->suiv = nouv;
    else 
        list->first = nouv;
    list->last = nouv;        
}

/* Reset les distances à INF*/
void reset_distance_sommet (Graphe_zone *graphe ){
    Cellule_som *cell = graphe->som;
    while (cell != NULL){
        cell->sommet->distance = INF;
        cell = cell->suiv;
    }
}

/* Nous nous sommes basés sur la fonction nbarc_depuis_r du cours 7 sur le parcours en largeur */
void plus_court_chemin( Graphe_zone *graphe , Sommet *depart, Sommet *arrive, Cellule_som **res ){
    Cellule_som *cour = NULL;
    Sommet *u, *v;
    File *file = malloc( sizeof( File ) );
    
    /* On remet les disctances à INF pour appeler plusieurs fois cette fonction*/
    reset_distance_sommet(graphe);
    init_File (file);
    /* On ajoute la case de départ à la FILE*/
    ajoute_queue_File (file, depart);
    /* Si la File est vide, cela veut dire que la case n'est pas dans la grille*/
    while ( file->first != NULL){

        enleve_tete_File (file, &u);
        /* Récupère la liste des sommets adjacents de u */    
        cour = u->sommet_adj;

        /*On parcourt tous les voisins de u*/
        while ( cour != NULL){
            v = cour->sommet;
            /* Si le sommet v n'a pas encore ete parcouru, on lui attribue sa distance et on l'ajoute à la FILE*/
            if ( v->distance == INF){
                v->distance = u->distance + 1;
                v->pere = u;
                ajoute_queue_File(file, v);
            }
            /* Si le sommet v est celui d'arrive, on remonte le chemin en recuperant dans
            res le chemin parcouru pour arriver au sommet v*/
            if ( v == arrive){
                while ( v != depart){
                    ajoute_liste_sommet ( v , res);
                    v = v->pere;
                }
                /* Liberation de la memoire */
                detruit_File (file);
                free(file);
                /* Sortie anticipee*/
                return ;
            }
            cour = cour->suiv;
        }
    } 
}

int BFS_max_bordure_graphe ( int **M , Grille *G , int dim , int nbcl , int aff){
    int cl , cpt = 0; 
    Sommet *s;
    Zsg_graphe *Z;
    Cellule_som *chemin, *cell;

    /* Initialisation de Zsg_graphe */ 
    Z = (Zsg_graphe *) malloc (sizeof (Zsg_graphe));
    init_Zsg_graphe( Z , dim , nbcl);
    cree_graphe_zone(Z->graphe, M,dim );
    init_Cellule_som(&chemin);

    /* Ajoute la premiere case a la bordure et aggrandit la zone */
    s = (Z->graphe->mat)[0][0] ;
    cl = s->cl;
    ajoute_Bordure_Zsg ( Z->B , s , cl);
    agrandit_Zsg_graphe(Z, cl);

    /* Chemin trouve le plus court chemin pour faire la diagonale  */
    plus_court_chemin(Z->graphe , (Z->graphe->mat)[0][0], (Z->graphe->mat)[dim-1][dim-1], &chemin);
    cell = chemin;
    /* Parcours ce chemin trouve */
    while( cell != NULL ){
        /* Recupere la couleur cl de cell->sommet pour agrandir la zone */
        cl= cell->sommet->cl;
        agrandit_Zsg_graphe(Z, cl);
        cell = cell->suiv;
        cpt++;

        /*Affichage de la Grille*/
        if(aff==1){
            Affichage_Grille_Graphe(Z, G , dim , cl );  
        }
    }

    /* Applique bordure_max de l exercice 5*/
    while( ! bordure_vide(Z->B, nbcl)  ){
        cl = bordure_max1(Z->B, nbcl);
        agrandit_Zsg_graphe(Z, cl);
        cpt++;

        /*Affichage de la Grille*/
        if(aff==1){ 
            Affichage_Grille_Graphe(Z, G , dim , cl );  
        }
    }
    
    /* Liberation de la memoire*/
    detruit_liste_sommet(&chemin);
    detruit_Zsg_graphe(Z,dim ,nbcl);
    free(Z);

    return cpt;
}