#include "Fonctions_exo5.h"


#define INF 999999



void init_Bordure_Zsg (Bordure_Zsg *cell){
    cell->len = 0;
    init_Cellule_som(&(cell->som));  
}

void init_Zsg_graphe(Zsg_graphe *Z , int dim , int nbcl){
    int i;

    Z->dim = dim;
    Z->nbcl = nbcl;
    init_Cellule_som( &(Z->Zone) );
    Z->B = ( Bordure_Zsg *) malloc (sizeof( Bordure_Zsg ) * nbcl);
    for ( i = 0 ; i < nbcl ; i++){
        init_Bordure_Zsg( (Z->B)+i );
    }
    Z->graphe = ( Graphe_zone *)malloc(sizeof( Graphe_zone ));
    init_Graphe_zone( Z->graphe, dim);
} 

void detruit_Bordure_Zsg(Bordure_Zsg *B){
    detruit_liste_sommet(&(B->som));
}




void detruit_Zsg_graphe(Zsg_graphe *Z , int dim, int nbcl ){
    int i;
    
    detruit_liste_sommet(&(Z->Zone)); 
    for ( i = 0 ; i < nbcl ; i++){
        detruit_Bordure_Zsg ( (Z->B)+i );
    }
    free(Z->B);

    detruit_Graphe_zone(Z->graphe , dim );
    free(Z->graphe);
}

void affiche_Bordure (Bordure_Zsg *B, int nbcl){
    int i ; 
    for ( i = 0 ; i < nbcl ; i++){
        printf("Case de la couleur : %d", i);
        affichage_Cellule_som( (B + i)->som );
    }
}

void ajoute_Bordure_Zsg (Bordure_Zsg *Bordure , Sommet *sommet, int cl ){
    ajoute_liste_sommet(sommet , &((Bordure+cl)->som));
    (Bordure+cl)->len += sommet->nbcase_som;
}

void agrandit_Zsg_graphe (Zsg_graphe *Z , int cl){
    Cellule_som *list;
    Cellule_som *cell = ((Z->B+cl)->som);
    
    while ( cell != NULL){
        
        /* Ajoute cell à la zone */ 
        cell->sommet->marque = 0; 
        ajoute_liste_sommet(cell->sommet, &(Z->Zone));
        
        /* Parcours les sommets adjacents de cell pour mettre à jour la bordure*/
        list = cell->sommet->sommet_adj;
        while( list != NULL){
            if (list->sommet->marque == 2){ /* Si le sommet n'a pas encore ete parcouru*/
                /* Ajout à la bordure */
                list->sommet->marque = 1;
                ajoute_Bordure_Zsg( Z->B , list->sommet, list->sommet->cl );
            }
            list = list->suiv;
        }

        cell = cell->suiv;
    }

    (Z->B+cl)->len = 0 ;    /* Reset du compteur de la case Bordure[cl]*/
    detruit_liste_sommet(&(Z->B+cl)->som);
}

int bordure_vide (Bordure_Zsg *B , int nbcl){
    int i ;

    for ( i = 0 ; i < nbcl ; i++){
        if( (B+i)->len != 0){
            return 0;            
        }
    }
    return 1;
}

/* Rend le numero de la case qui le plus de case */
int bordure_max1( Bordure_Zsg *B , int nbcl){
    int i , cl= 0, max = 0;
    
    for ( i = 0 ; i < nbcl ; i++){
        if( (B+i)->len > max){
            max = (B+i)->len;
            cl = i;
        }
    }
    return cl;
}


void Affichage_Grille_Graphe( Zsg_graphe *Z, Grille *G, int dim, int cl){
    int i, j;

    for ( i = 0 ; i < dim ; i++){
        for ( j = 0 ; j < dim ; j++){
            if (Z->graphe->mat[i][j]->marque != 0){
                Grille_attribue_couleur_case(G,i,j,Z->graphe->mat[i][j]->cl);
            }
            else{
                Grille_attribue_couleur_case(G,i,j,cl);
            }
        }
    }
    Grille_redessine_Grille();
    sleep(VITESSE);
}


int max_bordure_graphe ( int **M , Grille *G , int dim , int nbcl , int aff){
    int cl , cpt = 0; 
    Sommet *s;
    Zsg_graphe *Z = (Zsg_graphe *) malloc (sizeof (Zsg_graphe));

    /* Initialisation */
    init_Zsg_graphe( Z , dim , nbcl);
    cree_graphe_zone(Z->graphe, M,dim );
    
    /* On ajoute la case [0][0] à la liste des voisins pour initialiser la zone*/
    s = (Z->graphe->mat)[0][0] ;
    cl = s->cl;
    ajoute_Bordure_Zsg ( Z->B , s , cl); 
    
    /* Tant que la bordure n'est pas vide, cl prend la couleur des cases les plus representes dans la bordure*/
    while( ! bordure_vide(Z->B, nbcl)  ){
        cl = bordure_max1(Z->B, nbcl);
        agrandit_Zsg_graphe(Z, cl);
        cpt++;

        if( aff == 1 ){ /*Affichage*/
            Affichage_Grille_Graphe( Z , G , dim , cl );  
        }
        
    }

    /* Liberation de la memoire*/
    detruit_Zsg_graphe(Z,dim ,nbcl);
    free(Z);

    return cpt - 1;
}
