#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#define DUREE_MAX 50
#define POID_MAX 50
#define START_MAX 50
#define MIN 0
#define TAILLE_MAX 1000

int rand_a_b(int a, int b){
    return rand()%(b-a) +a;
}

char *lire(char *tableau, int taille, FILE *fichier)
{
    char *retour=fgets(tableau, taille, fichier);
    char *retourligne= strchr(tableau, '\n');
    if (retourligne != NULL)
    {
        retourligne = '\0';
    }
    return retour;
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

    FILE* fichier = NULL;
    fichier = fopen("test.txt", "w+");
    if (fichier != NULL)
    {
      fprintf(fichier, "%d\n", nbTache);
      s_tache ** taches = listTaches->taches;
      for( i = 0; i < nbTache; i++){
	s_tache* tache = taches[i];
        fprintf(fichier, "%d\n", tache->weight);
        fprintf(fichier, "%d\n", tache->start_at_least);
        fprintf(fichier, "%d\n", tache->duration);
      }
        // On peut lire et écrire dans le fichier
       fclose(fichier);
    }
    else
    {
        // On affiche un message d'erreur si on veut
        printf("Impossible d'ouvrir le fichier test.txt");
    }
//     int nbTache
   } else {
	  FILE* fichier = NULL;
	int nbTache, i;
	fichier = fopen("test.txt", "r");
	char nb[TAILLE_MAX];
	fgets(nb, TAILLE_MAX, fichier);
	nbTache = atoi(nb);
	s_taches* listTaches = new_taches(nbTache);
	if (fichier != NULL)
	{
	    char ligne[TAILLE_MAX];
	    for( i = 0; i < nbTache; i++){

		fgets(ligne, TAILLE_MAX, fichier);
		int duree = atoi(ligne);
		fgets(ligne, TAILLE_MAX, fichier);
		int poid = atoi(ligne);
		fgets(ligne, TAILLE_MAX, fichier);
		int start_at_least = atoi(ligne);
		ajouter_tache(listTaches, new_tache(poid,start_at_least,duree));
		//printf("%d, %d, %d", duree, poid, start_at_least);

	    }
	    printf("%d", listTaches->nb_taches);
/*	    while (fgets(ligne, TAILLE_MAX, fichier) != NULL)
	    {
	      printf("%s", ligne);
	    }
  */
	    fclose(fichier);
      }

      heuristique_1(listTaches, nbTache);
      heuristique_2(listTaches, nbTache);
   }
   return 0;
}
