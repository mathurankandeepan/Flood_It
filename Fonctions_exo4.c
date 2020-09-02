#include<time.h>

#include "Fonctions_exo4.h"

#define INF 999999
#define VITESSE 0.1


void init_Sommet(Sommet *sommet, int nbsom, int cl){
    sommet->num = nbsom;
    sommet->cl = cl;
    init_liste(&sommet->cases);
    sommet->nbcase_som = 0;
    init_Cellule_som((&sommet->sommet_adj));
    sommet->marque=2;
    sommet->distance = INF;
    sommet->pere = NULL;
}

void init_Cellule_som(Cellule_som **cell){
    *cell=NULL;
}

void init_Graphe_zone(Graphe_zone *graphe, int dim){
    int i , j;
    graphe->nbsom= 0;
    init_Cellule_som( &(graphe->som) ); /* Initialise à NULL*/
    graphe->mat=(Sommet ***) malloc(sizeof(Sommet**)*dim);
    
    for (i=0;i<dim;i++){
        (graphe->mat)[i]=(Sommet**) malloc(sizeof(Sommet*)*dim);
        for (j=0;j<dim;j++){
            (graphe->mat)[i][j]=NULL;
        }
    }

}


void detruit_sommet (Sommet *sommet){
    detruit_liste(&(sommet->cases));
    free(sommet->cases);
    detruit_liste_sommet((&sommet->sommet_adj));
   
}

void detruit_Graphe_zone(Graphe_zone *graphe , int dim){
    int i;
    Cellule_som *tmp, *cell;
    cell=graphe->som;

    /* Free d'abord les sommets de la zone puis la liste Cellule_som*/
    while (cell != NULL){
        tmp = cell;
        detruit_sommet(cell->sommet); 
        free(cell->sommet);
        cell=cell->suiv; 
        free(tmp);
    }

      for (i=0;i<dim;i++){ /* Free le double tableau de pointeur de sommets*/
         free((graphe->mat)[i]);
      }
      free(graphe->mat);

}


void affichage_Listecase (ListeCase *L ){
    ListeCase list= *L ;
    while ( list !=NULL ){
        printf("\t\tCase: ( %d , %d )\n",list->i,list->j);
        list=list->suiv;
    }
}

void affichage_Cellule_som( Cellule_som *cell){
    Cellule_som *list = cell;
    while (list != NULL ){
        printf("\t\tSommet : %d\n", list->sommet->num );
        list = list->suiv;
    }
}
void affichage_zone (Cellule_som *list){
    printf("\n\n LA ZONE DE LA GRILLE\n\n");
    affichage_Cellule_som( list);
}

void affichage_sommet ( Sommet *sommet){
    printf("\nSommet numéro : %d\n", sommet->num);
    printf("\t\tDistance : %d\n",sommet->distance );
    printf("\tListe des cases contenues dans ce sommet : \n");
    affichage_Listecase(&(sommet->cases) );
    printf("\tListe des cases voisines dans ce sommet : \n");
    affichage_Cellule_som(sommet->sommet_adj);
}

void affichage_graphe_zone ( Graphe_zone *graphe ){
    printf("\n**************** Affichage du graphe sommet par sommet *******************\n");
    Cellule_som *cell = graphe->som;
    while(cell != NULL){
        affichage_sommet ( cell->sommet );
        cell = cell->suiv; 
    } 
    printf("\n Nombre de sommet total : %d\n",graphe->nbsom );
    printf("\n*************************************************************\n");
}

void affichage_matrice ( Graphe_zone *graphe, int dim ){
    int i,j;
    char *sep = "----" * (2 * dim - 1) + "\n"; // Séparateur de ligne
    char *ligne = ""; // Récupère la ligne à afficher
    Sommet ***mat = graphe->mat;
    Sommet *s;
    printf("\n**************** Affichage du graphe case par case *******************\n");
    for (i = 0; i<dim; i++){
        for(j = 0; j < dim; j++){
            s = mat[i][j];
            ligne += s->num + "\t";
        }
        printf(ligne + "\n");
        ligne = "";
        printf(sep);
    }
}


int ajoute_liste_sommet(Sommet *sommet, Cellule_som **cell ){
    Cellule_som *new=(Cellule_som *)malloc(sizeof(Cellule_som));
    if(new==NULL){
        printf("Erreur d'allocation \n");
        return 0;
    }
    new->sommet=sommet;
    new->suiv=*cell;
    *cell=new;
    return 1;
}


void detruit_liste_sommet(Cellule_som **cell){
    Cellule_som *cour,*temp;
    cour=*cell;
    while (cour!=NULL){
      temp=cour;
      cour=cour->suiv;
      free(temp);
    }
    *cell=NULL;
}

void ajoute_voisin( Sommet *s1, Sommet *s2){
    ajoute_liste_sommet(s1, &(s2->sommet_adj));
    ajoute_liste_sommet(s2, &(s1->sommet_adj));
}

int adjacent ( Sommet *s1, Sommet *s2){
    Cellule_som *cell= s1->sommet_adj;
    while(cell != NULL){
        if (cell->sommet == s2)
            return 1;
        cell= cell->suiv;
    }
    return 0;
}


void cree_graphe_zone(Graphe_zone *graphe , int **M, int dim){
    int i , j, cpt, cl;
    Sommet *sommet;
    Sommet ***mat; /* Recupère la grille de sommets*/
    ListeCase list;

    cpt = 0; /* Compteur pour le nombre de case dans chaque zone*/
    /* Création de tous les sommets du graphe */
    for (i=0;i<dim;i++){
        for (j=0;j<dim;j++){
            if ( (graphe->mat)[i][j]==NULL){ /* Si La case n'a pas encore de sommet*/
                cl = M[i][j]; /* Cl prend la couleur de la case*/
                sommet=(Sommet *)malloc(sizeof(Sommet)); /* Creation d'un nouveau sommet*/
                init_Sommet(sommet,graphe->nbsom,cl);
                (graphe->nbsom)++;  /* Incrémentation du nombre de sommets totaux */

                trouve_zone_imp(M, dim , i , j , &cpt , &(sommet->cases)); /* Sommet->cases récupère la zone de la case M[i][j]*/
                
                sommet->nbcase_som = cpt; /* Affecte le nombre de case de la zone obtenue*/
                cpt = 0; /* On remet le compteur à 0 pour le prochaine zone*/
                
                /* On affecte à toute  les cases  de la zone obtenue le sommet qu'on vient de créer*/
                list =  (sommet->cases);
                while(! test_liste_vide(&list) ){ 
                    graphe->mat[(list)->i][(list)->j]= sommet;
                    (list)=(list)->suiv;
                }
                /* Ajoute le sommet à la liste des sommets de graphe*/ 
                ajoute_liste_sommet(sommet,&(graphe->som));
            }
        }
    }
    
    /* Création des arêtes entre les voisins*/
    /* On teste que à droite et en bas car le graphe est non orienté*/
    mat = graphe->mat ;
    for ( i=0 ; i<dim ; i++){
        for ( j=0 ; j<dim ; j++){
            if (i<dim-1){   /* condition pour eviter des sorties de la grille*/
                if (mat[i][j] != mat[i+1][j] && !adjacent(mat[i][j],mat[i+1][j])){ /* case voisine de couleur différente et n'est pas déjà dans liste adjacent */
                    ajoute_voisin(mat[i][j],mat[i+1][j]);

                }
            }
            if (j<dim-1){
                if (mat[i][j] != mat[i][j+1] && !adjacent(mat[i][j],mat[i][j+1])){
                    ajoute_voisin(mat[i][j],mat[i][j+1]);
                }
            }
        }
    }
}
