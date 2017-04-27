#include <stdlib.h>
#include <string.h>

struct s_tache
{
    int weight;
    int start_at_least;
    int duration;
};

struct s_machine
{
    struct s_tache ** liste_taches;
    int nb_taches;
    int start_time;
};

struct s_tache * new_tache(int w, int s, int d);

struct s_machine * new_machine(int n);

void ajouter_tache(struct s_machine * machine, struct s_tache * tache);

int evaluer(struct s_machine * machine);

void toString(struct s_machine * m);
