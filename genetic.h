#ifndef __GENETIC_H__
#define __GENETIC_H__
#include <stdbool.h>
#include "structs.h"

int TAILLE_GENOME;
s_taches * PROBLEME;

typedef struct individu
{
    int * genes;
    int fitness;
    bool aevaluer;
} s_individu;

typedef struct population
{
    s_individu ** individus;
    int nb_individus;
    int nb_pop_max;
} s_population;

typedef struct algorithme {
    int     taillePopulationParents;
    int     taillePopulationEnfants;
    int     tailleTournoi;
    double  tauxMutation;
    int     maxGenerations;
    int     maxEvaluations;
    bool    verbose;
    int     generationsEffectuee;

    s_individu * meilleurSolution;
    s_individu * meilleurSolutionGlobale;
    int     meilleurFitness;
    int     pireFitness;
} s_algorithme;

//INDIVIDU

s_individu * new_individu();

int retourneGene(s_individu * individu, int index);

void fixerGene(s_individu * individu, int index, int valeur);

void echangerGene(s_individu * individu, int i1, int i2);

int retourneTaille();

s_solution * retourneSolution(s_individu * individu);

int retourneFitness(s_individu * individu);

void mettreAEvaluer(s_individu * individu);

void individuToString(s_individu * individu);

int compareIndividu(s_individu * indiv1,s_individu * indiv2);

int retourneDistanceAvec(s_individu * indiv1,s_individu * indiv2);

void freeIndividu(s_individu * individu);

//POPULATION

s_population * new_population(int nb_max);

s_individu ** retournePopulation(s_population * pop);

s_individu * retourneIndividu(s_population * pop, int index);

s_individu * extraireIndividu(s_population * pop, int index);

void insererIndividu(s_population * pop, s_individu * indiv, int index);

int retourneTaillePopulation(s_population * pop);

void ajouterIndividu(s_population * pop, s_individu * ind);

void evaluerPopulation(s_population * pop);

void trierPopulation(s_population * pop);

void populationToString(s_population * pop);

double retourneFitnessMoyenne(s_population * pop);

double retourneDiversite(s_population * pop);

void freePopulation(s_population * pop);

void freeAllPopulation(s_population * pop);

//ALGORITHME

s_algorithme * init_algorithme();

bool estFini(s_algorithme * algo);

s_individu * croisementUniforme(s_individu * i1, s_individu * i2);

int chercheValeurLibre(int * taches, int taille);

void mutation (s_algorithme * algo, s_individu * indiv);

s_population * remplacement(s_algorithme * algo, s_population * parents, s_population * enfants);

s_individu * selectionTournoi(s_algorithme * algo, s_population * pop);

s_population * creerEnfants(s_algorithme * algo, s_population * parents);

s_population * executerUneGeneration(s_algorithme * algo, s_population * parents);

s_individu * executerAlgortihme(s_algorithme * algo);


#endif
