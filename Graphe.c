#include <time.h>
#include "math.h"
#include <string.h>


#include "API_Grille.h"
#include "API_Gene_instance.h"
#include "Entete_Fonctions.h"

void Graphe_exo_moyenne (int dim, int nbcl, int nivdif, int exo, int nbtest, char *fichier, int ecrire ){
  int i, j, graine, essais, essais_moyenne = 0;
  int **M;
  Grille* G = NULL;
  clock_t
     temps_initial, /* Temps initial en micro-secondes */
     temps_final;   /* Temps final en micro-secondes */
  float
    temps_cpu,       /* Temps total en secondes */
    temps_moyenne = 0;     

  if (nbtest == 0){
    printf("\nD'accord vous n'aurez pas de test!\n");
    return;
  }  
  for ( i = 0 ; i <  nbtest ; i++){

    graine = i;
   
    M=(int **) malloc(sizeof(int*)*dim);
    for ( j = 0 ; j <  dim ; j++){
        M[j]=(int*) malloc(sizeof(int)*dim);
        if (M[j]==0) printf("Pas assez d'espace mémoire disponible\n");
    }

    Gene_instance_genere_matrice(dim, nbcl, nivdif, graine, M);

    temps_initial = clock ();

    if (exo==1){
      essais = sequence_aleatoire_rec(M, G, dim, nbcl, 0);
    }
    if (exo==2){
      essais = sequence_aleatoire_imp(M, G, dim, nbcl, 0);
    }
    if (exo==3){
      essais = sequence_aleatoire_rapide(M, G, dim, nbcl, 0);
    }
    if (exo==5){
      essais =  max_bordure_graphe(M, G, dim, nbcl, 0);
    }
    if (exo==6){
      essais = BFS_max_bordure_graphe(M, G, dim, nbcl, 0);
    }
    if (exo==7){
      essais = BFS_max_bordure_graphe_croix(M, G, dim, nbcl, 0);
    }
    if (exo==8){
      essais = BFS_Contour(M, G, dim, nbcl, 7, 0);
    }
    temps_final = clock ();
    temps_cpu = (temps_final - temps_initial);

    /* Desallocation de la matrice */
    for(j = 0; j< dim ; j++) {
      if (M[j])
          free(M[j]);
    }
    if (M) free(M);

    essais_moyenne  = essais_moyenne + essais;
    temps_moyenne = temps_moyenne + temps_cpu;
  }
  essais_moyenne = floor ( essais_moyenne / nbtest );
  temps_moyenne = (temps_moyenne / nbtest) * 1e-6;

  printf ("Exercice %d / dim %d / nbcl %d/ nivdiv %d / essais %d / temps_cpu %f \n",exo,dim,nbcl,nivdif,essais_moyenne,temps_moyenne);
  /* Si nous devons écrire dans un fichier */
  if ( ecrire == 1){
    FILE *F= fopen(fichier,"a");
    fprintf(F, "%d %d %d %f %d\n",dim, nbcl, nivdif, temps_moyenne, essais_moyenne );
    fclose(F);
  }


}

void Graphe_dim ( int dim_min, int dim_max, int dim_pas, int nbcl, int nvdif, int exo, int nbtest,char *fichier, int ecrire  ){
  int i;
  /* Fais varier les dimensions*/
  for ( i = dim_min ; i < dim_max ; i = i + dim_pas){
    Graphe_exo_moyenne(i , nbcl, nvdif , exo, nbtest, fichier, ecrire );
  }
}

void Graphe_nbcl ( int dim, int nbcl_min ,int nbcl_max, int nbcl_pas, int nvdif, int exo, int nbtest,char *fichier, int ecrire ){
  int i;
  /* Fais varier le nombre de couleurs*/ 
  for ( i = nbcl_min ; i < nbcl_max ; i = i + nbcl_pas){
    Graphe_exo_moyenne(dim , i, nvdif, exo, nbtest, fichier, ecrire );
  }
}

/* Concatene les noms des fichiers dans titres*/ 
void titre_graphe ( char *fichier_debut, char *fichier_fin, char **titre ){
  *titre = (char *)malloc(30);
  strcpy(*titre,fichier_debut);
  strcat(*titre, fichier_fin  );
}

void Graphe_2D_main ( int exo, int nbtest, char *fichier ){
  char *titre ;
  

  titre_graphe(fichier, "_X_10_0.txt", &titre);
  Graphe_dim ( 10 , 1000 , 10, 10 , 0 , exo , nbtest, titre , 1 );
  free(titre);
  
  titre_graphe( fichier, "_X_100_0.txt", &titre );
  Graphe_dim ( 10 , 1000 , 10, 100 , 0 , exo , nbtest, titre , 1 );
  free(titre);

  titre_graphe( fichier, "_X_10_50.txt", &titre );
  Graphe_dim (  10 , 1000 , 10, 10 , 50 , exo , nbtest, titre , 1 );
  free(titre);

  titre_graphe( fichier, "_X_100_50.txt", &titre );
  Graphe_dim (  10 , 1000 , 10, 100 , 50 , exo , nbtest, titre , 1 );
  free(titre);

  titre_graphe( fichier, "_10_X_0.txt", &titre );
  Graphe_nbcl ( 10 , 10 , 100, 2 , 0 , exo , nbtest, titre , 1 );
  free(titre);

  titre_graphe( fichier, "_1000_X_0.txt", &titre );
  Graphe_nbcl ( 1000 , 10 , 100, 2 , 0 , exo , nbtest, titre , 1 );
  free(titre);
  
  titre_graphe( fichier, "_10_X_50.txt", &titre );
  Graphe_nbcl ( 10 , 10 , 100, 2 , 50 , exo , nbtest, titre , 1 );
  free(titre);

  titre_graphe( fichier, "_1000_X_50.txt", &titre );
  Graphe_nbcl ( 1000 , 10 , 100, 2 , 50 , exo , nbtest, titre , 1 );
  free(titre);

}

// void Graphe_3D(int dim , int nbcl ,int nivdif ,char *fichier, int exo){
//     int i, j, k, graine, res;
//     int **M;
//     Grille* G = NULL;
//     clock_t
//      temps_initial, /* Temps initial en micro-secondes */
//      temps_final;   /* Temps final en micro-secondes */
//     float
//      temps_cpu;     /* Temps total en secondes */
//     FILE *F= fopen(fichier,"a");
//     graine = 1;  

    

//     for (i = 10; i<dim; i=i+2){
//         for (k = 2 ; k < nbcl ; k = k + 1 ){

//         printf("%d\n",i);
//         M=(int **) malloc(sizeof(int*)*i);
//         for (j=0;j<i;j++){
//             M[j]=(int*) malloc(sizeof(int)*i);
//             if (M[j]==0) printf("Pas assez d'espace mémoire disponible\n");
//         }
//         Gene_instance_genere_matrice(i, k, nivdif, graine, M);
        
//         temps_initial = clock ();
        
//         if (exo==1){
//           srand(time(NULL));
//           res = sequence_aleatoire_rec(M, G, i, k, 0);
//           printf("%d essais\t", res);
//         }

//         if (exo==2){
//           res = sequence_aleatoire_imp(M, G, i, k, 0);
//            printf("%d essais\t", res);
//         }
//         if (exo==3){
//           res = sequence_aleatoire_rapide(M, G, i, k, 0);
//            printf("%d essais\t", res);
//         }

//         if (exo==5){
//           res =  max_bordure_graphe(M, G, i, k, 0);
//           printf("%d essais\t",res);
//         }

//         if (exo==6){
//           res = BFS_max_bordure_graphe(M, G, i, k, 0);
//           printf("%d essais\t", res);
//         }

//          if (exo==7){
//           res = BFS_max_bordure_graphe_croix(M, G, i, k, 0);
//           printf("%d essais\t", res);
//         }
//         if (exo==8){
//           res =BFS_Contour(M, G, i, k, 7, 0);
//           printf("%d essais\t", res);
//         }

//         temps_final = clock ();
//         temps_cpu = (temps_final - temps_initial) * 1e-6;
//         fprintf(F, "%d %d %d %f\n", i, k, res, temps_cpu );

//         /* Desallocation de la matrice */
//         for(j = 0; j< i; j++) {
//           if (M[j])
//               free(M[j]);
//         }
//         if (M) free(M);
//         }

//     }
//     fclose(F);

// }

