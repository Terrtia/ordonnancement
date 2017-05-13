#ifndef __STRUCT_H__
#define __STRUCT_H__
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdbool.h>

typedef struct tache
{
    int weight;
    int start_at_least;
    int duration;
} s_tache;

typedef struct taches
{
    int nb_taches;
    s_tache ** taches;
} s_taches;

typedef struct machine
{
    s_taches * liste_taches;
    int nb_taches;
    int start_time;
} s_machine;

typedef struct solution
{
    s_machine * m1, * m2;
    s_taches * taches;
} s_solution;

s_tache * new_tache(int w, int s, int d);

s_taches * new_taches(int n);

s_machine * new_machine(int n);

s_solution * new_solution(s_taches * liste);

void ajouter_tache(s_taches * liste, s_tache * tache);

void ajouter_tache_m(s_machine * machine, s_tache * tache);

void ajouter_tache_s(s_solution * s, int n_machine, int ntache);

void swap(s_taches * liste, int x, int y);

bool compare(s_tache * t1, s_tache * t2, int i);

void trier_liste(s_taches * liste, int comp);

int evaluer_m(s_machine * machine);

int evaluer(s_solution * solution);

int starting_time(s_machine * machine);

int ending_time( s_machine * machine);

void machineToString(s_machine * m);

void solutionToString(s_solution * m);

void free_tache(s_tache * tache);

void free_taches(s_taches * taches);

void free_machine(s_machine * machine);

void free_solution(s_solution * solution);
#endif // __STRUCTS
