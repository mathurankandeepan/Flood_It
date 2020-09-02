#include "math.h"

#include "Fonctions_exo8.h"

#define INF 999999

void init_Zsg2_graphe(Zsg2_graphe *Z , int dim , int nbcl , int tailleCligne){
    int i , tailleCtotal = tailleCligne * 4;

    Z->dim = dim;
    Z->nbcl = nbcl;
    Z->tailleCligne = tailleCligne;
    Z->tailleCtotal = tailleCtotal;
    Z->tab = malloc (sizeof(int) * nbcl); 
    Z->B = (Bordure_Zsg *) malloc (sizeof(Bordure_Zsg) * nbcl);
    for (i=0;i<nbcl;i++){
        Z->tab[i] = 0;
        init_Bordure_Zsg( (Z->B)+i );
    }
    Z->graphe = (Graphe_zone*)malloc(sizeof(Graphe_zone));
    init_Graphe_zone( Z->graphe, dim);
    Z->Contour = (Bordure_Zsg *) malloc (sizeof(Bordure_Zsg) * tailleCtotal);
    for (i=0;i< tailleCtotal ;i++){
        init_Bordure_Zsg( (Z->Contour)+i );
    }
    
} 

void init_Contour (Zsg2_graphe *Z, int tailleCtotal, int dim_moit ){
    int last = Z->dim -1, i = 0; 
    Graphe_zone *graphe = Z->graphe;
    Sommet ***mat = graphe->mat ;
    Bordure_Zsg *contour = Z->Contour;
    Sommet *milieu= mat[dim_moit][dim_moit];
    Cellule_som *list,*cell;

    init_Cellule_som(&list);
    
    points_strategiques(Z->graphe, &list, dim_moit, last );
    cell = list;
    
    BFS_graphe_complet(Z->graphe, milieu); /*BFS d'origine sommet_millieu sur tout le graphe */

    /* Attribution à chaque case stratégique du contour le plus petit chemin entre millieu et la case*/
    while (cell != NULL) {
        plus_court_chemin_sommet(milieu, cell->sommet, &(contour+i)->som) ;
        i++;
        cell = cell->suiv;
    }   
    
    detruit_liste_sommet(&list);
}

/* Pas encore fonctionnelle mais peut-être pour la soutenance */
void init_Contour2 (Zsg2_graphe *Z,int tailleCligne, int tailleCtotal, int dim_moit, int dim ){
    int i , last = Z->dim -1, pas, tmp1 , tmp2, tmp3; 
    Graphe_zone *graphe = Z->graphe;
    Sommet ***mat = graphe->mat ;
    Bordure_Zsg *contour = Z->Contour;
    Sommet *milieu= mat[dim_moit][dim_moit];
    pas= floor ( dim /2 ) - 1; /*Pas entre chaque point d'une ligne de contour*/ 

    for( i = 1 ; i < tailleCligne ;i++){
        if ( i != 0 ){
            plus_court_chemin(graphe, milieu, mat[0][i*pas],( &(contour+i)->som));
        }
        tmp1 = i+tailleCligne;
        plus_court_chemin(graphe, milieu, mat[i*pas][last],( &(contour+tmp1)->som));
        tmp2 = i+tailleCligne*2;
        plus_court_chemin(graphe, milieu, mat[last][i*pas], ( &(contour+tmp2)->som));
        tmp3 = i+tailleCligne*3;
        if ( i != tailleCligne -1  ) {
            plus_court_chemin(graphe, milieu, mat[i*pas][0],( &(contour+tmp3)->som));
        }
        
    }

}

void enleve_tete_Bordure_Zsg ( Bordure_Zsg *cell, int i ,Sommet **sommet ){
    Cellule_som *tmp = (cell+i)->som;
    *sommet = tmp->sommet;
    (cell+i)->som = tmp->suiv;
    free(tmp);
}

void init_tab (int *tab, int nbcl){
    int i;

    for (i=0;i<nbcl;i++){
        tab[i] = 0;
    }
}

void mis_a_jour_Contour_tab (Zsg2_graphe *Z ,int tailleCtotale){
    int i , cl;
    Bordure_Zsg *contour =  Z->Contour;
    int *tab = Z->tab;
    

    for ( i = 0 ; i < tailleCtotale ; i++){
        if ( (contour+i)->som != NULL  ){
            cl = (contour+i)->som->sommet->cl ;
            (tab[cl])++;
        }
    }
}

int max_tab_contour( int *tab, int nbcl ){
    int i, max = 0, cl = 0;

    for ( i = 0 ; i < nbcl ; i++){
        if ( tab[i]> max ){
            max = tab[i];
            cl = i;
        }
    }
    return cl;
}

void Creation_File_Contour (Zsg2_graphe *Z ,int tailleCtotale , File **File){
    int i, cl, nbcl = Z->nbcl;
    Sommet *sommet;
    Bordure_Zsg *contour =  Z->Contour;

    for ( i = 0 ; i < tailleCtotale ; i++){
        (contour+i)->len = 1;
    }

    while ( ! bordure_vide(contour , tailleCtotale )){ /* Si le Contour n'est pas vide*/
        init_tab(Z->tab,nbcl);  /* On remet le tab à 0*/
        mis_a_jour_Contour_tab(Z , tailleCtotale); /* On cree un tableau qui récupere le nombre d'occurence de chaque couleur*/
        cl = max_tab_contour (Z->tab , nbcl ) ; /* On prend le max de ce tableau*/
        
        for ( i = 0 ; i < tailleCtotale ; i++){
            if ( (contour+i)->som != NULL  ){
                if ( (contour+i)->som->sommet->cl == cl ){ /* Si le sommet est de la même couleur que le max, alors on l'enlève*/ 
                    enleve_tete_Bordure_Zsg (contour , i , &sommet);      
                    ajoute_queue_File(*File, sommet);   /*On ajoute ce sommet à la FILE*/
                }
            }
            else {
                (contour+i)->len = 0;
            }
        }

    }
}


void detruit_Zsg2_graphe(Zsg2_graphe *Z , int dim, int nbcl, int tailleCtotal ){
    int i;
    
    for (i=0;i<nbcl;i++){
        detruit_Bordure_Zsg ( (Z->B)+i );
    }
    free(Z->B);
    free(Z->tab);
    detruit_Graphe_zone(Z->graphe , dim );
    free(Z->graphe);

    for (i=0;i<tailleCtotal;i++){
        detruit_Bordure_Zsg ( (Z->Contour)+i );
    }
    free(Z->Contour);
}


void agrandit_Zsg2_graphe (Zsg2_graphe *Z , int cl){
    Cellule_som *list;
    Cellule_som *cell = ((Z->B+cl)->som);
    
    (Z->B+cl)->len=0;

    while ( cell != NULL){
        cell->sommet->marque = 0; /* Fait partie de la zone*/ 
        list = cell->sommet->sommet_adj;

        while( list != NULL){

            if (list->sommet->marque == 2 ){
                list->sommet->marque = 1;
                /* Ajout des sommets voisins de la nouvelle zone dans la bordure*/
                ajoute_Bordure_Zsg( Z->B , list->sommet, list->sommet->cl );

            }
            list = list->suiv;
        }

        cell = cell->suiv;
    }
    (Z->B+cl)->len = 0 ;    
    detruit_liste_sommet(&(Z->B+cl)->som);
}

void Affichage_Grille_Graphe2( Zsg2_graphe *Z, Grille *G, int dim, int cl){
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


int BFS_Contour ( int **M , Grille *G , int dim , int nbcl ,int tailleCligne , int aff){
    int cl , cpt = 0, dim_moit , tailleCtotal; 
    Sommet *sommet_depart, *sommet_milieu, *s = NULL;
    Cellule_som *chemin,  *cell, *tmp;
    File *file = malloc( sizeof( File ) );
    Zsg2_graphe *Z = (Zsg2_graphe *) malloc (sizeof (Zsg2_graphe));

    /* Initialisation */ 
    dim_moit = floor (dim /2);
    tailleCtotal = tailleCligne *4 ;

    init_Zsg2_graphe( Z , dim , nbcl, tailleCligne);
    cree_graphe_zone(Z->graphe, M,dim );
    init_Cellule_som(&chemin);
    init_Cellule_som(&tmp);
    init_Contour(Z, tailleCtotal, dim_moit);
    init_File(file);
    sommet_milieu = (Z->graphe->mat)[dim_moit][dim_moit];
    sommet_depart = (Z->graphe->mat)[0][0] ; 

    
    /* Ajout de la première case de la zone dans la bordure puis on applique agrandir_zone*/
    cl = sommet_depart->cl;
    ajoute_liste_sommet(sommet_depart , &((Z->B+cl)->som));
    ((Z->B+cl)->len)++;
    agrandit_Zsg2_graphe(Z, cl);

    

    /* Atteindre le milileu le plus vite possible*/
    plus_court_chemin_sommet(sommet_milieu , sommet_depart, &tmp ); /* On recupere le plus petit chemin du milieu vers [0][0]*/ 
    ajoute_liste_sommet(sommet_milieu, &tmp); /* On rajoute la case du milieu parce que par défault , la fonction de deçu ne le fait pas*/
    inverser(tmp,&chemin); /* on inverser le chemin*/
    
    cell = chemin;
    while( cell != NULL ){
  
        cl= cell->sommet->cl;

        agrandit_Zsg2_graphe(Z, cl);   /*Agrandit la zone */

        cell = cell->suiv;
        cpt++;

        if( aff == 1){ /*Affichage*/
            Affichage_Grille_Graphe2(Z, G , dim , cl );  
        }
    }


    /* Parcours de la File qui atteint tout le contour le plus rapidement possible grâce à max_tab_contour*/
    Creation_File_Contour(Z, tailleCtotal , &file);
    
    while( file->first != NULL ){
        enleve_tete_File(file , &s);
            
        if (s->marque == 0  ){ /* Si le sommet fait déjà parti de la zone, on passe au suiv*/
            continue;
        }
        cl = s->cl;
        agrandit_Zsg2_graphe(Z, cl);
        cpt++;

        if(aff==1){ /*Affichage*/
            Affichage_Grille_Graphe2(Z, G , dim , cl );  
        }
    }

    /* Bordure max pour la fin de l'exercice 5*/
    while( ! bordure_vide(Z->B, nbcl)  ){
        
        cl = bordure_max1(Z->B, nbcl);
        agrandit_Zsg2_graphe(Z, cl);
        cpt++;

        if(aff == 1){ /*Affichage*/
            Affichage_Grille_Graphe2(Z, G , dim , cl );  
        }
    }
    

    /* Destruction de toute la mémoire allouée*/
    detruit_liste_sommet(&chemin);
    free (file);
    detruit_Zsg2_graphe(Z , dim , nbcl , tailleCtotal);
    free(Z);
    

    return cpt;
} 