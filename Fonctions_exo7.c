#include "math.h"

#include "Fonctions_exo7.h"




int BFS_max_bordure_graphe_croix ( int **M , Grille *G , int dim , int nbcl , int aff){
    int cl , cpt = 0, dim_moit, last = dim-1; 
    Sommet *s;
    Zsg_graphe *Z;
    Cellule_som *chemin,  *cell;
    Sommet ***mat;
    
    
    /* Initialisation  */ 
    dim_moit = floor (dim /2);

    Z = (Zsg_graphe *) malloc (sizeof (Zsg_graphe));
    init_Zsg_graphe( Z , dim , nbcl);
    cree_graphe_zone(Z->graphe, M,dim );
    init_Cellule_som(&chemin);
    mat = Z->graphe->mat;

    /* Ajoute la premiere case a la bordure et aggrandit la zone */
    s = mat[0][0] ;
    cl = s->cl;
    ajoute_liste_sommet(s , &((Z->B+cl)->som));
    ((Z->B+cl)->len)++;
    agrandit_Zsg_graphe(Z, cl);


    /*On en empile le chemin de plusieurs points stratégiques comme les coins et les milieu des 
      cote*/
   
    plus_court_chemin(Z->graphe , mat[dim_moit][dim_moit], mat[0][dim_moit], &chemin);
    plus_court_chemin(Z->graphe , mat[dim_moit][dim_moit], mat[dim_moit][0], &chemin);
    plus_court_chemin(Z->graphe , mat[dim_moit][dim_moit], mat[dim_moit][last], &chemin);
    plus_court_chemin(Z->graphe , mat[dim_moit][dim_moit], mat[last][dim_moit], &chemin);
    plus_court_chemin(Z->graphe , mat[dim_moit][dim_moit], mat[last][0], &chemin);
    plus_court_chemin(Z->graphe , mat[dim_moit][dim_moit], mat[0][last], &chemin);
    plus_court_chemin(Z->graphe , mat[dim_moit][dim_moit], mat[last][last], &chemin);
    plus_court_chemin(Z->graphe , mat[0][0], mat[dim_moit][dim_moit], &chemin);

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
    detruit_Zsg_graphe(Z,dim ,nbcl);
    free(Z);

    return cpt;
}



