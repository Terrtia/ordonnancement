#ifndef __GENETIC_H__
#define __GENETIC_H__
#include <stdbool.h>
#include "structs.h"

int TAILLE_GENOME = 10;
s_taches * PROBLEME;

typedef struct individu
{
    int * genes;
    int fitness;
    bool aevaluer;
} s_individu;

s_individu * new_individu();

int retourneGene(s_individu * individu, int index);

int fixerGene(s_individu * individu, int index, int valeur);

int retourneTaille();

s_solution * retourneSolution(s_individu * individu);

int retourneFitness(s_individu * individu);

void mettreAEvaluer(s_individu * individu);

void individuToString(s_individu * individu);

int compareIndividu(s_individu * indiv1,s_individu * indiv2);

int retourneDistanceAvec(s_individu * indiv1,s_individu * indiv2);

#endif
