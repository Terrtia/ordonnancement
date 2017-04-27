#include <stdlib.h>
#include <string.h>

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
    struct s_tache ** liste_taches;
    int nb_taches;
    int start_time;
} s_machine;

s_tache * new_tache(int w, int s, int d);

s_taches * new_taches(int n);

s_machine * new_machine(int n);

void ajouter_tache(s_taches * liste, s_tache * tache);

void ajouter_tache(s_machine * machine, s_tache * tache);

void trier_liste(s_taches * liste);

int evaluer(s_machine * machine);

void toString(s_machine * m);
