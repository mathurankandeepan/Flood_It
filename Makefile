GCC_FLAGS = -g -Wall

all: Flood-It_Partie1 Flood-It



API_Gene_instance.o: API_Gene_instance.c API_Gene_instance.h
	gcc $(GCC_FLAGS) -c API_Gene_instance.c

API_Grille.o: API_Grille.c API_Grille.h
	gcc $(GCC_FLAGS) -c API_Grille.c

Liste_case.o: Liste_case.c Liste_case.h
	gcc $(GCC_FLAGS) -c Liste_case.c

Graphe.o: Graphe.c Graphe.h
	gcc $(GCC_FLAGS) -c Graphe.c

Fonctions_exo1.o: Fonctions_exo1.c Entete_Fonctions.h Liste_case.h
	gcc $(GCC_FLAGS) -c Fonctions_exo1.c

Fonctions_exo3.o: Fonctions_exo3.c Fonctions_exo3.h Entete_Fonctions.h Liste_case.h
	gcc $(GCC_FLAGS) -c Fonctions_exo3.c	

Fonctions_exo4.o: Fonctions_exo4.c Fonctions_exo4.h Fonctions_exo6.h Entete_Fonctions.h Liste_case.h
	gcc $(GCC_FLAGS) -c Fonctions_exo4.c

Fonctions_exo5.o: Fonctions_exo5.c Fonctions_exo5.h Entete_Fonctions.h Liste_case.h
	gcc $(GCC_FLAGS) -c Fonctions_exo5.c

Fonctions_exo6.o: Fonctions_exo6.c Entete_Fonctions.h Fonctions_exo6.h Fonctions_exo4.h Liste_case.h
	gcc $(GCC_FLAGS) -c Fonctions_exo6.c

Fonctions_exo7.o: Fonctions_exo7.c  Entete_Fonctions.h Fonctions_exo7.h Liste_case.h
	gcc $(GCC_FLAGS) -c Fonctions_exo7.c

Fonctions_exo8.o: Fonctions_exo8.c  Entete_Fonctions.h Fonctions_exo8.h Liste_case.h
	gcc $(GCC_FLAGS) -c Fonctions_exo8.c

Flood-It_Partie1.o: Flood-It_Partie1.c
	gcc $(GCC_FLAGS) -c Flood-It_Partie1.c 

Flood-It.o: Flood-It.c
	gcc $(GCC_FLAGS) -c Flood-It.c 

Flood-It_Partie1: Flood-It_Partie1.o Liste_case.o  API_Grille.o API_Gene_instance.o Graphe.o Fonctions_exo1.o Fonctions_exo3.o Fonctions_exo4.o Fonctions_exo5.o Fonctions_exo6.o Fonctions_exo7.o Fonctions_exo8.o
	gcc $(GCC_FLAGS) -o Flood-It_Partie1 Flood-It_Partie1.o Liste_case.o API_Grille.o API_Gene_instance.o Graphe.o Fonctions_exo1.o Fonctions_exo3.o Fonctions_exo4.o Fonctions_exo5.o Fonctions_exo6.o Fonctions_exo7.o Fonctions_exo8.o -lSDL -lm
	
Flood-It :Flood-It.o Liste_case.o  API_Grille.o API_Gene_instance.o Graphe.o Fonctions_exo1.o Fonctions_exo3.o Fonctions_exo4.o Fonctions_exo5.o Fonctions_exo6.o Fonctions_exo7.o Fonctions_exo8.o
	gcc $(GCC_FLAGS) -o Flood-It Flood-It.o Liste_case.o API_Grille.o API_Gene_instance.o Graphe.o Fonctions_exo1.o Fonctions_exo3.o Fonctions_exo4.o Fonctions_exo5.o Fonctions_exo6.o Fonctions_exo7.o Fonctions_exo8.o -lSDL -lm

clean:
	rm -f *.o Flood-It_Partie1
