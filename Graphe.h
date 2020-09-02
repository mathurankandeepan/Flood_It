/* Graphe.h */

#ifndef  Graphe_h
#define  Graphe_h

#include <string.h>

/* Affiche la moyenne d'essais et de temps de la fonction de l'exercice exo sur un nombre de nbtest*/
/* If ecrire = 1 then dim nbcl nivdif temps_cpu essais sont récupere dans fichiers*/
void Graphe_exo_moyenne (int dim, int nbcl, int nivdif,int aff, int exo, int nbtest, char *fichier, int ecrire );

/* Appelle la fonction Graphe_exo_moyenne avec dim variant de dim_min à dim_max*/
void Graphe_dim ( int dim_min, int dim_max, int dim_pas, int nbcl, int nvdif, int exo, int nbtest, char *fichier, int ecrire );

/* Appelle la fonction Graphe_exo_moyenne  avec nbcl variant de nbcl_min à nbcl_max*/
void Graphe_nbcl ( int dim, int nbcl_min ,int nbcl_max, int nbcl_pas, int nvdif, int exo, int nbtest,char *fichier, int ecrire );

/* Recupère toutes les donnees importantes pour un exo en effectuant la moyenne sur nbtest test pour tracer les courbes avec gnuplot */
/* fichier est l'entete du du fichier qui va etre cree*/
void Graphe_2D_main ( int exo, int nbtest, char *fichier );

void Graphe_3D(int dim , int nbcl ,int nivdif ,char *fichier, int exo);


#endif /* Graphe.h */
