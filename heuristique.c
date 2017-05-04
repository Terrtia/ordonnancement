#include "heuristique.h"
#include <stdio.h>
#include <stdbool.h>

void heuristique_1(s_taches * taches, int nbTache)
{
    trier_liste(taches);
    s_solution * solution = new_solution(taches);

    s_machine * M1 = solution->m1;
    M1->start_time = (int) taches->taches[0]->start_at_least;

    int i;
    for(i=0; i<nbTache; i++){
        ajouter_tache_m(M1, taches->taches[i]);
    }

    printf("heuristique 1:\n");
    solutionToString(solution);
}

void heuristique_2(s_taches * taches, int nbTache)
{
    trier_liste(taches);
    s_solution * solution = new_solution(taches);

    s_machine * M1 = solution->m1;
    s_machine * M2 = solution->m2;

    M1->start_time = (int) taches->taches[0]->start_at_least;
    M2->start_time = (int) taches->taches[1]->start_at_least;
    printf("heuristique 2:\n");
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

    printf("heuristique 2:\n");
    solutionToString(solution);
}

void heuristique_3(s_taches * taches, int nbTache)
{

}

void heuristique_4(s_taches * taches, int nbTache)
{

}

/*int main ()
{

    heuristique_1();
    return 0;
}*/
