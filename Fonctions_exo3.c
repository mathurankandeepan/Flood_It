#include<time.h>

#include "Fonctions_exo3.h"


void init_Zsg (S_Zsg *Z, int dim, int nbcl){
    int i,j;
    Z->dim = dim;
    Z->nbcl = nbcl;
    init_liste(&(Z->Lzsg));

    Z->B = (ListeCase *)malloc(sizeof(ListeCase)*nbcl);

    for (i=0;i<nbcl;i++){
        init_liste( (Z->B)+i);
    }
    Z->App=(int **) malloc(sizeof(int*)*dim);
    for (i=0;i<dim;i++){
        (Z->App)[i]=(int*) malloc(sizeof(int)*dim);
        for (j=0;j<dim;j++){
            (Z->App)[i][j]=-2;
        }
    }
    
}

void free_Zsg(S_Zsg *Z,int dim,int nbcl){
    int i;
    detruit_liste(&(Z->Lzsg));
    free(Z->B);
    for (i=0;i<dim;i++){
        free(Z->App[i]);
    }
    free(Z->App);
}

int ajoute_Zsg (S_Zsg *Z, int i, int j){
    (Z->App)[i][j]=-1;
    return ajoute_en_tete(&(Z->Lzsg), i , j);
}

int ajoute_Bordure(S_Zsg *Z, int i, int j, int cl){
    (Z->App)[i][j]=cl;
    return ajoute_en_tete((Z->B)+cl, i , j);
}

int appartient_Zsg(S_Zsg *Z, int i, int j){
    return (Z->App)[i][j] == -1;
}

int appartient_Bordure(S_Zsg *Z, int i, int j, int cl){
    return ((Z->App)[i][j] == cl);
}



int agrandit_Zsg (int **M, S_Zsg *Z , int cl, int k, int l){
    int i, j, cpt, cl2;
    
    cpt=0; /*Compte le nombre de case rajouté à la zone*/
    ListeCase *Pile=(ListeCase *)malloc(sizeof(ListeCase));
    init_liste(Pile);

    ajoute_en_tete(Pile,k,l);

    while(!test_liste_vide(Pile)){
        enleve_en_tete(Pile, &i,&j);
        
        if((Z->App)[i][j]==-1){ /* Si on a deja parcouru la case, on passe à la suivante*/
            continue;
        }
        (Z->App)[i][j]=-1;
        cpt++;
        ajoute_Zsg(Z,i,j); /*Ajoute à la zone*/
        if (0<i){            /*Ne sors pas de la grille par le haut*/ 

            if( ! appartient_Zsg(Z, i-1,j) ){ /*Si la case voisine n'est pas déjà dans la zone*/
                cl2 = M[i-1][j];              /*cl2 récupère la couleur de la case voisine*/

                if (cl==cl2){                       /* Si la case voisine est de la même couleur que la zone */

                    if (! appartient_Bordure(Z,i-1,j,cl) ){ /*Si la case voisine n'appartient pas déjà à la bordure*/
                        ajoute_en_tete(Pile,i-1,j);             /*Alors rajoute à la Pile pour rajouter à la zone*/
                    }
                                                                /*Sinon la case est déjà dans la bordure donc elle va être parcourue donc rien à faire*/
                }
                else{                               /*Sinon pas de la même couleur que la zone*/
                    if ( !appartient_Bordure(Z,i-1,j,cl) ){ /*Si n'appartient pas à la bordure*/
                        ajoute_Bordure(Z,i-1,j,cl2);            /*Alors ajouter à la bordure*/
                    }
                                                                /*Sinon déjà dans la bordure donc rien à faire*/
                }  
            }
        }

        if (i<(Z->dim)-1){  /*Ne sors pas de la grille par le bas*/ 

            if( ! appartient_Zsg(Z, i+1,j) ){ // if pas  dans la zone
                cl2 = M[i+1][j];
                if (cl==cl2){ // meme couleur
                    if (! appartient_Bordure(Z,i+1,j,cl) ){ //meme couleur mais  ni dans bordure ni dans zone... sinon meme couleur mais appartient déja a la bordure(donc pas besoin de traiter)
                        ajoute_en_tete(Pile,i+1,j);
                    }
                }
                else{
                    if ( !appartient_Bordure(Z,i+1,j,cl) ){ //couleur differente  ni dans bordure ni dans zone...
                        ajoute_Bordure(Z,i+1,j,cl2);
                    }
                }  
            }
        }
        
        if (0<j){  /*Ne sors pas de la grille par la gauche*/ 

            if( ! appartient_Zsg(Z, i,j-1) ){ // if pas  dans la zone
                cl2 = M[i][j-1];
                if (cl==cl2){ // meme couleur
                    if (! appartient_Bordure(Z,i,j-1,cl) ){ //meme couleur mais  ni dans bordure ni dans zone... sinon meme couleur mais appartient déja a la bordure(donc pas besoin de traiter)
                        ajoute_en_tete(Pile,i,j-1);
                    }
                }
                else{
                    if ( !appartient_Bordure(Z,i,j-1,cl) ){ //couleur differente  ni dans bordure ni dans zone...
                        ajoute_Bordure(Z,i,j-1,cl2);
                    }
                }  
            }
        }

        if (j<(Z->dim)-1){  /*Ne sors pas de la grille par la droite*/ 
            if( ! appartient_Zsg(Z, i,j+1) ){ // if pas  dans la zone
                cl2 = M[i][j+1];
                if (cl==cl2){ // meme couleur
                    if (! appartient_Bordure(Z,i,j+1,cl) ){ //meme couleur mais  ni dans bordure ni dans zone... sinon meme couleur mais appartient déja a la bordure(donc pas besoin de traiter)
                        ajoute_en_tete(Pile,i,j+1);
                    }
                }
                else{
                    if ( !appartient_Bordure(Z,i,j+1,cl) ){ //couleur differente  ni dans bordure ni dans zone...
                        ajoute_Bordure(Z,i,j+1,cl2);
                    }
                }  
            }
        }
    }
    free(Pile);
    return cpt;

}


int sequence_aleatoire_rapide(int **M, Grille *G, int dim, int nbcl, int aff){
    int taille,tmp,cpt,cl, i,j;
    ListeCase *list;
    ListeCase cell;
    S_Zsg *Z;

    srand(time(NULL));

    cpt = 0;                /*Compteur de tours*/
    cl = M[0][0];         /*Récupère la couleur de la zone pour éviter que la couleur choisie soit la même*/
    tmp = cl;               /*Récupère la couleur cl du tour précédent pour éviter que celle-ci soit la même*/
    
    Z=(S_Zsg*) malloc(sizeof(S_Zsg));
    init_Zsg(Z,dim,nbcl);
    taille = agrandit_Zsg(M,Z,cl,0,0);   /*Compteur des cases de la zone*/


    while(taille != dim * dim ){  /*Tant que la taille de la zone n'est pas le nombre totale de la Grille*/
        
        while((cl=rand() % nbcl) == tmp); /*On choisit une couleur différente de la précédente*/

        tmp = cl;
        cpt++;
        list = (Z->B)+cl;    /*list récupère la liste des cases de couleur cl du tableau de la bordure*/
        while(! test_liste_vide(list) ){ /*Parcours  toutes les cases de la bordure de la couleur cl*/
            enleve_en_tete(list,&i,&j);
            taille += agrandit_Zsg(M,Z,cl,i,j);   
        }

        if(aff==1){ /*Affichage*/
            cell = Z->Lzsg;
            while(! test_liste_vide(&cell) ){ /*Remplace les -1 par la nouvelle couleur choisie juste pour l'affichage*/
                M[cell->i][cell->j]= cl;
                cell=(cell)->suiv;
            }
            for (i=0;i<dim;i++)
                for (j=0;j<dim;j++){
                        Grille_attribue_couleur_case(G,i,j,M[i][j]);
                }
            Grille_redessine_Grille();
            sleep(0.1);
        }
    }
    free_Zsg(Z,dim,nbcl);    
    free(Z);
    return cpt;
}