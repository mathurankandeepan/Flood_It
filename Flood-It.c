#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "API_Grille.h"
#include "API_Gene_instance.h"

 
 
int main(int argc,char**argv){

  int dim=-1, nbcl=-1, nivdif=-1, graine=-1, aff=-1, exo=-1, nbtest=-1, ecrire=-1;
  char *fichier = "";
  Grille *G;
  int i,j;
  int **M;

  clock_t
    temps_initial, /* Temps initial en micro-secondes */
    temps_final;   /* Temps final en micro-secondes */
  float
    temps_cpu;     /* Temps total en secondes */ 
  do{
    printf("Dimension de la grille :");
    scanf("%d", &dim);
  }while(dim < 0);

  do{
  printf("Nombre de couleur :");
  scanf("%d", &nbcl)
  }while(nbcl < 0);

  do{
  printf("Niveau de difficulté :");
  scanf("%d", &nivdif);
  }while(nivdif < 0 && nivdif > 100);

  do{
    printf("Affichage [0/1] :");
    scanf("%d", &aff);
  }while(aff != 0 && aff != 1);

  do{
    printf("Exercice à tester :");
    scanf("%d", &exo);
  }while(exo < 0 && exo > 8);

  do{
    printf("Nombre de test");
    scanf("%d", &nbtest);
  }while(nbtest < 0);

  do{
    printf("Sauvegarder les données des tests [0/1] :");
    scanf("%d", &ecrire);
  }while(ecrire != 0 && ecrire != 1);

  if (ecrire == 1){
    do{
      printf("Nom du fichier");
      scanf(" %s", &fichier);
    }while(fichier == "");
  }

  // if(argc!=5){
  //   printf("usage: %s <dimension nb_de_couleurs niveau_difficulte graine>\n",argv[0]);
  //   return 1;
  // }

  // dim=atoi(argv[1]);


  // nbcl=atoi(argv[2]);
  // nivdif=atoi(argv[3]);
  // graine=atoi(argv[4]);

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

  for (i=0;i<dim;i++)
    for (j=0;j<dim;j++){
      Grille_attribue_couleur_case(G,i,j,M[i][j]);
    }

  Grille_redessine_Grille();
 
  /* 
     A VOUS DE JOUER

  */

  Graphe_exo_moyenne(dim, nbcl, nivdif, aff, exo, nbtest, fichier, ecrire);

  Grille_attente_touche();
 
  Grille_ferme_fenetre();

  Grille_free(&G);

  return 0;
}
