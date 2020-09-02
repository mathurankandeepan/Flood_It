#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


#include "API_Grille.h"
#include "API_Gene_instance.h"
#include "Entete_Fonctions.h"
#include "Graphe.h"




int main(int argc,char**argv){
  srand(time(NULL));

  int dim, nbcl, nivdif, graine, exo, aff;
  Grille *G;
  int i,j;
  int **M;

  clock_t
    temps_initial, /* Temps initial en micro-secondes */
    temps_final;   /* Temps final en micro-secondes */
  float
    temps_cpu;     /* Temps total en secondes */



  if(argc!=7){
    printf("usage: %s <dimension> <nb_de_couleurs> <niveau_difficulte> <graine> <exo:1-2-3> <aff 0/1>\n",argv[0]);
    return 1;
  }

  dim=atoi(argv[1]);


  nbcl=atoi(argv[2]);
  nivdif=atoi(argv[3]);
  graine=atoi(argv[4]);
  exo=atoi(argv[5]);
  aff=atoi(argv[6]);

  /* Generation de l'instance */

  M=(int **) malloc(sizeof(int*)*dim);
  for (i=0;i<dim;i++){
    M[i]=(int*) malloc(sizeof(int)*dim);
    if (M[i]==0) printf("Pas assez d'espace mémoire disponible\n");
  }

  Gene_instance_genere_matrice(dim, nbcl, nivdif, graine, M);
  //  M[0][0]=1;
  //  M[1][0]=1;
  //  M[0][1]=3;
  //  M[1][1]=4;
  //  M[2][0]=1;
  //  M[2][1]=6;
  //  M[2][2]=7;
  //  M[0][2]=8;
  //  M[1][2]=9;

  // Graphe_3D( 1000 , 100 , 1 , "Graphe3D_exo7_nivdif1.txt" , 7  );
  // Graphe_exo_moyenne (dim, nbcl, nivdif, exo, 20);
  // Graphe_exo_moyenne (dim, nbcl, nivdif, exo, 20);

  //  Graphe_dim(10, 100 , 10 , nbcl , nivdif, exo, 20 );
  // Graphe_2D_main(8, 20, "exo8");
  // Graphe_2D_main(7, 20, "exo7");
  // Graphe_2D_main(6, 20, "exo6");
  // Graphe_2D_main(5, 20, "exo5");
  // Graphe_2D_main(3, 40, "exo3");
  // Graphe_2D_main(2, 10, "exo2");
  // Graphe_2D_main(1, 20, "exo1");



  /* Affichage de la grille */

  if (aff==1){
    Grille_init(dim,nbcl, 500,&G);

    Grille_ouvre_fenetre(G);

    for (i=0;i<dim;i++)
      for (j=0;j<dim;j++){
	Grille_attribue_couleur_case(G,i,j,M[i][j]);
      }

    Grille_redessine_Grille();
    Grille_attente_touche();
  }

  temps_initial = clock ();
  if (exo==1){
     printf("%d essais\t", sequence_aleatoire_rec(M, G, dim, nbcl, aff));
  }

  if (exo==2){
     printf("%d essais\t", sequence_aleatoire_imp(M, G, dim, nbcl, aff));
  }
  if (exo==3){
     printf("%d essais\t", sequence_aleatoire_rapide(M, G, dim, nbcl, aff));
  }
  
  if (exo==4){
    Graphe_zone *graphe = (Graphe_zone*)malloc(sizeof(Graphe_zone));
    init_Graphe_zone(graphe,dim);
    cree_graphe_zone(graphe, M, dim);
    affichage_graphe_zone(graphe);
    detruit_Graphe_zone(graphe,dim);
    free(graphe);
  }

  if (exo==5){
    printf("%d essais\t", max_bordure_graphe(M, G, dim, nbcl, aff));
  }

    if (exo==6){
    printf("%d essais\t", BFS_max_bordure_graphe(M, G, dim, nbcl, aff));
  }

   if (exo==7){
    printf("%d essais\t", BFS_max_bordure_graphe_croix(M, G, dim, nbcl, aff));
  }
  if (exo==8){
    printf("%d essais\t", BFS_Contour(M, G, dim, nbcl, 7, aff));
  }

  temps_final = clock ();
  temps_cpu = (temps_final - temps_initial) * 1e-6;
  printf("%f\n",temps_cpu);

  /* Desallocation de la matrice */
  for(i = 0; i< dim; i++) {
    if (M[i])
        free(M[i]);
  }
  if (M) free(M);

  if (aff==1){
    Grille_ferme_fenetre();

    Grille_free(&G);
  }


  return 0;
}
