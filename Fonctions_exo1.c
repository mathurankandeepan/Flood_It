#include<time.h>

#include "Entete_Fonctions.h"
#include "Liste_case.h"

void Affichage_Grille (int **M, Grille *G, int dim){
  int i, j;
  for (i=0;i<dim;i++)
    for (j=0;j<dim;j++){
      Grille_attribue_couleur_case(G,i,j,M[i][j]);
    }
  Grille_redessine_Grille();
  sleep(VITESSE);
}

/* Exercice 1*/

void trouve_zone_rec(int **M, int dim, int i, int j, int *taille, ListeCase *L)
{
  /*Rentre dans cette fonction ssi la case[i][j] est de la même couleur que la première case[0][0]*/

  ajoute_en_tete(L,i,j); /*On ajoute à L la case[i][j]*/
  (*taille)++;
  int cl= M[i][j]; /* cl récupère la couleur de la case pour la comparer à ses cases voisines*/
  M[i][j]=-1;
  
  if (0<i){ /*Ne sors pas de la grille par le haut*/ 
    if (cl==M[i-1][j]){        /*Si la case voisine du bas est de la même couleur*/
      trouve_zone_rec(M,dim,i-1,j,taille,L); /* On rappelle la fonction récursive dans la case
      voisine de la même couleur au départ que la case où on appelle la fonction*/
    }
  }

  if (i<dim-1){ /*Ne sors pas de la grille par le bas*/ 
    if (cl==M[i+1][j]){
      trouve_zone_rec(M,dim,i+1,j,taille,L);
    }
  }

  if (0<j){ /*Ne sors pas de la grille par la gauche*/ 
    if (cl==M[i][j-1]){
      trouve_zone_rec(M,dim,i,j-1,taille,L);
    }
  }

  if (j<dim-1){ /*Ne sors pas de la grille par la droite*/ 
    if (cl==M[i][j+1]){
      trouve_zone_rec(M,dim,i,j+1,taille,L);
    }
  }
}



int sequence_aleatoire_rec(int **M, Grille *G, int dim, int nbcl, int aff){
  int cl,cpt,taille,tmp;
  ListeCase *L= (ListeCase *)malloc(sizeof(ListeCase));
  ListeCase cell;
  
  srand(time(NULL));
  taille = 0;           /*Compteur des cases de la zone*/
  cpt=0;                /*Compteur de tours*/
  cl = M[0][0];         /*Récupère la couleur de la zone pour éviter que la couleur choisie soit la même*/
  tmp=cl;               /*Récupère la couleur cl du tour précédent pour éviter que celle-ci soit la même*/

  while(taille != dim * dim ){  /*Tant que la taille de la zone n'est pas le nombre totale de la Grille*/
    if (aff ==1 ){
      Affichage_Grille(M, G, dim);
    }
    
    init_liste(L);
    taille = 0;
    while((cl=rand() % nbcl) == tmp);   /*On choisit une couleur différente de la précédente*/
      
    tmp = cl;
    cpt++;
    trouve_zone_rec(M,dim,0,0,&taille,L); /*Affecte à -1 toutes les cases de la zone et L récupère ces cases*/
    cell = *L;
    while(cell){ /*Affecte la nouvelle couleur tiré aléatoirement à la zone*/
      M[cell->i][cell->j]= cl;
      cell=cell->suiv;
    }
    detruit_liste(L);
  }
  

  free(L);
  return cpt-1;
}

/* Exercice 2*/

void trouve_zone_imp(int **M, int dim, int Mi, int Mj, int *taille, ListeCase *L)
{
  int cl,i,j;
  ListeCase *Pile=(ListeCase *)malloc(sizeof(ListeCase));

  init_liste(Pile);
  ajoute_en_tete(Pile, Mi , Mj ); /*Ajoute à la zone la case [0][0] */
  cl=M[Mi][Mj];                   /* On récupère la couleur de la case[0][0]*/

  while(!test_liste_vide(Pile)){
    
    enleve_en_tete(Pile, &i,&j); /*Enlève à la Pile la première case de la liste et récupère i et j*/
    
    if(M[i][j]==-1 ){            /*Si la case a déjà été parcouru, on passe au prochain tour de boucle*/
      continue;
    }

    ajoute_en_tete(L,i,j);       /*On ajoute à L la case */
    (*taille)++;                 /*On incrémente la taille de la zone*/
    
    M[i][j]=-1;

    if (0<i){                   /*Ne sors pas de la grille par le haut*/ 
      if (cl==M[i-1][j]){       /*Si la case voisine du bas est de la même couleur que la */
        ajoute_en_tete(Pile,i-1,j);
      }
    }

    if (i<dim-1){   /*Ne sors pas de la grille par le bas*/ 
      if (cl==M[i+1][j]){
        ajoute_en_tete(Pile,i+1,j);
      }
    }

    if (0<j){    /*Ne sors pas de la grille par la gauche*/ 
      if (cl==M[i][j-1]){
        ajoute_en_tete(Pile,i,j-1);
      }
    }

    if (j<dim-1){    /*Ne sors pas de la grille par la droite*/
      if (cl==M[i][j+1]){
        ajoute_en_tete(Pile,i,j+1);
      }
    }
  }

  free(Pile);
}




int sequence_aleatoire_imp(int **M, Grille *G, int dim, int nbcl, int aff){
  int cl,cpt,taille,tmp;
  ListeCase *L= (ListeCase *)malloc(sizeof(ListeCase));
  ListeCase cell;
  
  srand(time(NULL));
  taille = 0;           /*Compteur des cases de la zone*/
  cpt=0;                /*Compteur de tours*/
  cl = M[0][0];         /*Récupère la couleur de la zone pour éviter que la couleur choisie soit la même*/
  tmp=cl;               /*Récupère la couleur du tour précédent pour éviter que celle-ci soit la même*/

  while(taille != dim * dim ){ /*Tant que la taille de la zone n'est pas le nombre totale de la Grille*/
   if (aff ==1 ){
      Affichage_Grille(M, G, dim);
    }
    init_liste(L);
    taille=0;
    while((cl=rand() % nbcl) == tmp); /*On choisit une couleur différente de la précédente*/
      
    tmp = cl;
    cpt++;
    trouve_zone_imp(M,dim,0,0,&taille,L); /*Affecte à -1 toutes les cases de la zone et L récupère ces cases*/
    cell = *L;
    while(cell){                      /*Affecte la nouvelle couleur tiré aléatoirement à la zone*/
      M[cell->i][cell->j]= cl;
      cell=cell->suiv;
    }
    detruit_liste(L);
  }
  
  free(L);

  return cpt-1;
}