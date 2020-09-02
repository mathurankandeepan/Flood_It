#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "API_Grille.h"
#include "API_Gene_instance.h"
#include "Graphe.h"
#include "Entete_Fonctions.h"

void Affichage_Menu(){
  printf("\nMenu : \n\n");
  printf("0-Sortie\n");
  printf("1-Test d'un exercice avec l'affichage de la grille \n");
  printf("2-Test d'un exercice sans l'affichage de la grille \n");
  printf("3-Moyenne pour des graines différentes sans affichage\n");
  printf("4-Affiche le graphe pour une petite matrice pour montrer la validé de la fonction de l'exercice 4\n");
  printf("\nVotre choix :\n");  
}

void Choisir_exo(int exo, int **M, Grille *G, int dim, int nbcl, int nivdif,  int aff){
  int res;
  clock_t
    temps_initial, /* Temps initial en micro-secondes */
    temps_final;   /* Temps final en micro-secondes */
  float
    temps_cpu;     /* Temps total en secondes */  
  
  temps_initial = clock ();
  
  switch (exo) {
    case 1:
      res = sequence_aleatoire_rec(M, G, dim, nbcl, aff);
      break;
    case 2:
      res = sequence_aleatoire_imp(M, G, dim, nbcl, aff);
      break;
    case 3:
      res = sequence_aleatoire_rapide(M, G, dim, nbcl, aff);
      break;
    case 5:
      res = max_bordure_graphe(M, G, dim, nbcl, aff);
      break;
    case 6:
      res = BFS_max_bordure_graphe(M, G, dim, nbcl, aff);
      break;
    case 7:
      res = BFS_max_bordure_graphe_croix(M, G, dim, nbcl, aff);
      break;
    case 8:
      res = BFS_Contour(M, G, dim, nbcl, 7, aff);
      break;
    default:
      printf("Dommage, vous avez tapé un mauvais numéro d'exercice\n");
      break;
  } 

  temps_final = clock ();
  temps_cpu = (temps_final - temps_initial) * 1e-6;
  printf ("\nExercice %d / dim %d / nbcl %d/ nivdiv %d / essais %d / temps_cpu %f \n",exo,dim,nbcl,nivdif,res,temps_cpu);

}

void entree( int ch , int *dim, int *nbcl, int *nivdif, int *exo, int *graine, int *nbtest, char **fichier, int *ecrire){
  printf("Dimension de la grille : ");
  scanf( "%d", dim);

  printf("Nombre de couleurs : ");
  scanf( "%d", nbcl);

  printf("Niveau de difficulté  [0-100] :");
  scanf( "%d", nivdif);

  printf("Exercice à tester [1-3]U[5-8] : ");
  scanf( "%d", exo);
  
  if (ch == 1 || ch == 2 ){
    printf("Graine :");
    scanf( "%d", graine);
  }
  if( ch == 3 ){
    printf("Nombre de test pour effectuer une moyenne (autrement dit, combien de graines différentes?): ");
    scanf( "%d", nbtest);

    printf("Sauvegarder les données des tests [0/1] :");
    scanf( "%d", ecrire);

    if (*ecrire == 1){
      printf("Nom de de l'entete du fichier :");
      scanf( "%s", *fichier);
    }
  }
}
 
int main(int argc,char**argv){

  int dim, nbcl, nivdif, graine, exo, nbtest, ecrire, lus, ch, i, j;
  char *fichier = malloc(sizeof(char)*20) ;
  Grille *G;
  int **M;
  
  do {
    Affichage_Menu();
    lus = scanf( " %d", &ch);
    if ( lus == 0 ){
      ch = 0;
      break;
    }
    
    switch(ch){
        case 1:

          entree(ch , &dim, &nbcl, &nivdif, &exo, &graine, &nbtest, &fichier, &ecrire );

          /* Generation de l'instance */
          M=(int **) malloc(sizeof(int*)*dim);
          for (i=0;i<dim;i++){
            M[i]=(int*) malloc(sizeof(int)*dim);
            if (M[i]==0) printf("Pas assez d'espace mémoire disponible\n");
          }

          Gene_instance_genere_matrice(dim, nbcl, nivdif, graine, M);
          
          /* Affichage de la grille */
          Grille_init(dim,nbcl, 500,&G);
          Grille_ouvre_fenetre(G);
          Affichage_Grille( M , G , dim );

          Choisir_exo(exo, M, G, dim, nbcl, nivdif, 1);

          Grille_ferme_fenetre();
          Grille_free(&G);
          /* Desallocation de la matrice */
          for(i = 0; i< dim; i++) {
            if (M[i])
                free(M[i]);
          }
          if (M) free(M);

          break;
        case 2:
        {
          entree(ch , &dim, &nbcl, &nivdif, &exo, &graine, &nbtest, &fichier, &ecrire );


          /* Generation de l'instance */
          M=(int **) malloc(sizeof(int*)*dim);
          for (i=0;i<dim;i++){
            M[i]=(int*) malloc(sizeof(int)*dim);
            if (M[i]==0) printf("Pas assez d'espace mémoire disponible\n");
          }

          Gene_instance_genere_matrice(dim, nbcl, nivdif, graine, M);

          Choisir_exo(exo, M, G, dim, nbcl, nivdif, 0);

          /* Desallocation de la matrice */
          for(i = 0; i< dim; i++) {
            if (M[i])
                free(M[i]);
          }
          if (M) free(M);
          break;
        }
        
        case 3:
        {
          entree(ch , &dim, &nbcl, &nivdif, &exo, &graine, &nbtest, &fichier, &ecrire );

          Graphe_exo_moyenne(dim, nbcl, nivdif, exo, nbtest, fichier, ecrire);
          break;
        }
        case 4:
        {
          dim = 3;
          nbcl = 10;
          M=(int **) malloc(sizeof(int*)*dim);
          for (i=0;i<dim;i++){
            M[i]=(int*) malloc(sizeof(int)*dim);
            if (M[i]==0) printf("Pas assez d'espace mémoire disponible\n");
          }

          M[0][0]=1;
          M[1][0]=1;
          M[0][1]=3;
          M[1][1]=4;
          M[2][0]=1;
          M[2][1]=6;
          M[2][2]=7;
          M[0][2]=8;
          M[1][2]=9;

          printf("\n**************** Affichage de la matrice de depart *******************\n");
          for (i = 0; i < dim; i++){
            for(j = 0; j < dim; j++){
              printf("%d\t", M[i][j] );
            }
          printf("\n");
          }
          printf("\n*************************************************************\n");

          Graphe_zone *graphe = (Graphe_zone*)malloc(sizeof(Graphe_zone));
          init_Graphe_zone(graphe,dim);
          cree_graphe_zone(graphe, M, dim);
          affichage_graphe_zone(graphe);
          affichage_matrice(graphe ,dim);
          detruit_Graphe_zone(graphe,dim);
          free(graphe);

          /* Desallocation de la matrice */
          for(i = 0; i< dim; i++) {
            if (M[i])
                free(M[i]);
          }
          if (M) free(M);

          break;
        }

        default:
          ch = 0;
          break;
    }
  } while ( ch != 0);

  printf("\nAu revoir ! Passez une bonne journée!\n");

  free(fichier);
  return 0;
}
