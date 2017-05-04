#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#define DUREE_MAX 50
#define POID_MAX 50
#define START_MAX 50
#define MIN 0

int rand_a_b(int a, int b){
    return rand()%(b-a) +a;
}

int main(int argc, char *argv[] ) {
   
   if(argc == 2){
     int nbTache= atoi(argv[1]);
     int i = 0;
     s_taches* listTaches = new_taches(nbTache);
     for(i = 0; i < nbTache; i++){
	int duree = rand_a_b(MIN, DUREE_MAX);
	int poid = rand_a_b(MIN, POID_MAX);
	int start_at_least = rand_a_b(MIN, START_MAX);
	ajouter_tache(listTaches, new_tache(poid,start_at_least,duree));
     }
//     int nbTache 
   } 
   return 0;
}
