#include "structs.h"


struct s_tache * new_tache(int w, int s, int d)
{
    struct s_tache * nouvelle_tache = (struct s_tache *) malloc (sizeof(struct s_tache));
    nouvelle_tache->weight = w;
    nouvelle_tache->start_at_least = s;
    nouvelle_tache->duration = d;
}

struct s_machine * new_machine(int n)
{
    struct s_machine * nouvelle_machine = (struct s_machine *) malloc (sizeof(struct s_machine));
    nouvelle_machine->liste_taches = (struct s_tache **) malloc (sizeof(struct s_tache * )*n);
    nouvelle_machine->nb_taches = 0;
    nouvelle_machine->start_time = 0;
}

void ajouter_tache(struct s_machine * machine, struct s_tache * tache)
{
    machine->liste_taches[machine->nb_taches] = tache;
    machine->nb_taches++;
}

int evaluer(struct s_machine * machine)
{
    int i, time = machine->start_time, value = 0;
    for (i = 0; i < machine->nb_taches; i++)
    {
        time +=  machine->liste_taches[i]->duration;
        value += time * machine->liste_taches[i]->weight;
    }
    return value;
}

void toString(struct s_machine * m)
{
    int i;
    printf("Machine\n");
    for (i = 0; i < m->nb_taches; i++)
    {
        struct s_tache * temp = m->liste_taches[i];
        printf("P : %d , S : %d, D : %d\n", temp->weight, temp->start_at_least, temp->duration);
    }
}

int main ()
{
    int i;
    struct s_machine * M1, * M2;
    M1 = new_machine(10);
    M2 = new_machine(10);
    for (i = 0; i < 10; i++)
    {
        struct s_tache * tache = new_tache(1,i,1);
        ajouter_tache(M1, tache);

    }
    toString(M1);
    toString(M2);
    printf("%d , %d\n", evaluer(M1), evaluer(M2));
}
