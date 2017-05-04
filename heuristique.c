#include "heuristique.h"
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

void heuristique_1(s_taches * taches, int nbTache)
{
    trier_liste(taches, 0);
    s_solution * solution = new_solution(taches);

    s_machine * M1 = solution->m1;
    M1->start_time = (int) taches->taches[0]->start_at_least;

    int i;
    for(i=0; i<nbTache; i++){
        ajouter_tache_m(M1, taches->taches[i]);
    }

    printf("\nheuristique 1:\n");
    solutionToString(solution);
    printf("eval: ");
    printf("%d",evaluer(solution));
    printf("\n");

   //free_solution(solution);
}

void heuristique_2(s_taches * taches, int nbTache)
{
    trier_liste(taches, 0);
    s_solution * solution = new_solution(taches);

    s_machine * M1 = solution->m1;
    s_machine * M2 = solution->m2;

    M1->start_time = (int) taches->taches[0]->start_at_least;
    M2->start_time = (int) taches->taches[1]->start_at_least;

    int i;
    bool ajout_m = true;
    for(i=0; i<nbTache; i++){
        if(ajout_m){
            ajouter_tache_m(M1, taches->taches[i]);
            ajout_m = false;
        } else {
            ajouter_tache_m(M2, taches->taches[i]);
            ajout_m = true;
        }
    }

    printf("\nheuristique 2:\n");
    solutionToString(solution);
    printf("eval: ");
    printf("%d",evaluer(solution));
    printf("\n");

   //free_solution(solution);
}

void heuristique_3(s_taches * taches, int nbTache)
{
    trier_liste(taches, 1);
    s_solution * solution = new_solution(taches);

    s_machine * M1 = solution->m1;
    s_machine * M2 = solution->m2;

    int i;
    bool ajout_m = true;
    for(i=0; i<nbTache; i++){
        if(ajout_m){
            ajouter_tache_m(M1, taches->taches[i]);
            ajout_m = false;
        } else {
            ajouter_tache_m(M2, taches->taches[i]);
            ajout_m = true;
        }
    }

    starting_time(M1);
    starting_time(M2);

    printf("\nheuristique 3:\n");
    solutionToString(solution);
    printf("eval: ");
    printf("%d",evaluer(solution));
    printf("\n");

    //free_solution(solution);
}

void heuristique_4(s_taches * taches, int nbTache)
{
    s_solution * solution = new_solution(taches);

    s_machine * M1 = solution->m1;
    s_machine * M2 = solution->m2;

    srand(time(NULL));
    bool rand_bool = rand() & 1;

    int i;
    for(i=0; i<nbTache; i++){

        rand_bool = rand() & 1;

        if(rand_bool){
            ajouter_tache_m(M1, taches->taches[i]);
        } else {
            ajouter_tache_m(M2, taches->taches[i]);
        }
    }

    starting_time(M1);
    starting_time(M2);

    printf("\nheuristique 4:\n");
    solutionToString(solution);
    printf("eval: ");
    printf("%d",evaluer(solution));
    printf("\n");

    //free_solution(solution);
}

/*int main ()
{

    heuristique_1();
    return 0;
}*/
