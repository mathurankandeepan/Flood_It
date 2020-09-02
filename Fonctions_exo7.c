#include "math.h"

#include "Fonctions_exo7.h"

#define INF 999999

void points_strategiques( Graphe_zone *graphe, Cellule_som **res, int dim_moit, int last){
    Sommet ***mat = graphe->mat;
    ajoute_liste_sommet( mat[last][last] ,res);
    ajoute_liste_sommet( mat[0][last] ,res);
    ajoute_liste_sommet( mat[last][0] ,res);
    ajoute_liste_sommet( mat[dim_moit][0] ,res);
    ajoute_liste_sommet( mat[dim_moit][last] ,res);
    ajoute_liste_sommet( mat[last][dim_moit] ,res);
    ajoute_liste_sommet( mat[0][dim_moit] ,res);
}


void BFS_graphe_complet( Graphe_zone *graphe , Sommet *depart){
    Cellule_som *cour = NULL;
    Sommet *u, *v;
    File *file = malloc( sizeof( File ) );
    
    /* On remet les disctances à INF si elles ne le sont pas déjà*/
    reset_distance_sommet(graphe);
    init_File (file);
    depart->distance = 0;

    /* On ajoute la case de départ à la FILE*/
    ajoute_queue_File (file, depart);

    while ( file->first != NULL){ /* La File sera NULL quand toute la grille aura été parcouru*/ 

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
            
            cour = cour->suiv;
        }
    } 
    detruit_File (file);
    free(file);
}

void plus_court_chemin_sommet (Sommet *depart, Sommet *arrive, Cellule_som **chemin ){
    Sommet *pere = arrive;

    /* Part de l'arrrive pour revenir au départ (chemin inverse) */
    while ( pere != depart && pere->pere!= NULL){
        ajoute_liste_sommet(pere, chemin);
        pere = pere->pere;
    }
}

void plus_court_chemin_Cellule_som( Sommet *depart, Cellule_som *list, Cellule_som **chemin  ){
    Cellule_som *cell = list;

    /* Parcours la Cellule_som des sommets auxquels nous devons retrouver le chemin */
    while ( cell != NULL){
        if (cell->sommet->pere != NULL){
            plus_court_chemin_sommet (depart , cell->sommet->pere , chemin);
        }
        cell = cell->suiv;
    }

}

void inverser(Cellule_som *som, Cellule_som **res){
    Cellule_som *cell = som;
    while (cell != NULL){
        ajoute_liste_sommet( cell->sommet , res);
        cell = cell->suiv;
    }
}


int BFS_max_bordure_graphe_croix ( int **M , Grille *G , int dim , int nbcl , int aff){
    int cl , cpt = 0, dim_moit, last = dim-1; 
    Sommet *sommet_depart, *sommet_milieu;
    Zsg_graphe *Z;
    Cellule_som *chemin,  *cell , *list, *inverse, *tmp;
    Sommet ***mat;
    
    
    /* Initialisation  */ 
    dim_moit = floor (dim /2);

    Z = (Zsg_graphe *) malloc (sizeof (Zsg_graphe));
    init_Zsg_graphe( Z , dim , nbcl);
    cree_graphe_zone(Z->graphe, M,dim );
    init_Cellule_som(&chemin);
    init_Cellule_som(&list);
    init_Cellule_som(&tmp);
    init_Cellule_som(&inverse);
    mat = Z->graphe->mat;
    sommet_milieu = mat[dim_moit][dim_moit];
    sommet_depart = mat[0][0] ;
    /* Ajoute la premiere case a la bordure et aggrandit la zone */
    cl = sommet_depart->cl;
    ajoute_liste_sommet(sommet_depart , &((Z->B+cl)->som));
    ((Z->B+cl)->len)++;
    agrandit_Zsg_graphe(Z, cl);


    /*On en empile le chemin de plusieurs points stratégiques comme les coins et les milieu des 
      cote*/
    points_strategiques(Z->graphe, &list, dim_moit, last); /*list recupère les points stratégiques que nous avons forcés*/
    BFS_graphe_complet(Z->graphe, sommet_milieu); /*BFS qui a pour origine sommet_millieu sur tout le graphe */
    plus_court_chemin_Cellule_som ( sommet_milieu, list ,&chemin ); /*Empile les differents chemins*/
    /*On atteint d'abord le milieu*/
    plus_court_chemin_sommet(sommet_milieu , sommet_depart, &tmp ); /* On recupere le plus petit chemin du milieu vers [0][0]*/ 
    ajoute_liste_sommet(sommet_milieu, &tmp); /* On rajoute la case du milieu parce que par défault , la fonction de deçu ne le fait pas*/
    inverser(tmp,&chemin); /* on inverser le chemin*/

    cell = chemin;
    /* Parcours ce chemin trouve */
     while( cell != NULL ){
        /* Si cell est deja dans la zone, on passe directement au suiv*/
        if (cell->sommet->marque == 0 ){
            cell = cell->suiv;
            continue;
        }
        /* Recupere la couleur cl de cell->sommet pour agrandir la zone */    
        cl= cell->sommet->cl;
        agrandit_Zsg_graphe(Z, cl);
        cell = cell->suiv;
        cpt++;

        if(aff==1){ /*Affichage*/
            Affichage_Grille_Graphe(Z, G , dim , cl );  
        }
    }
    
    /* Applique bordure_max de l exercice 5*/
    while( ! bordure_vide(Z->B, nbcl)  ){
        
        cl = bordure_max1(Z->B, nbcl);
        agrandit_Zsg_graphe(Z, cl);
        cpt++;

        if(aff==1){ /*Affichage*/
            Affichage_Grille_Graphe(Z, G , dim , cl );  
        }
    }
    /* Liberation de la memoire*/
    detruit_liste_sommet(&chemin);
    detruit_liste_sommet(&list);
    detruit_liste_sommet(&tmp);
    detruit_Zsg_graphe(Z,dim ,nbcl);
    free(Z);

    return cpt;
}



