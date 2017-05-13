
#include "structs.h"


s_tache * new_tache(int w, int s, int d)
{
    s_tache * nouvelle_tache = (s_tache *) malloc (sizeof( s_tache));
    nouvelle_tache->weight = w;
    nouvelle_tache->start_at_least = s;
    nouvelle_tache->duration = d;
    return nouvelle_tache;
}

s_taches * new_taches(int n)
{
    s_taches * liste_taches = (s_taches *) malloc (sizeof(s_taches));
    liste_taches->nb_taches = 0;
    liste_taches->taches = (s_tache **) malloc (sizeof(s_tache *)*n);
    return liste_taches;
}

 s_machine * new_machine(int n)
{
    s_machine * nouvelle_machine = ( s_machine *) malloc (sizeof( s_machine));
    nouvelle_machine->liste_taches = new_taches(n);
    nouvelle_machine->nb_taches = 0;
    nouvelle_machine->start_time = 0;
    return nouvelle_machine;
}

s_solution * new_solution(s_taches * liste)
{
    s_solution * nouvelle_solution = (s_solution *)malloc (sizeof( s_solution));
    nouvelle_solution->taches = liste;
    nouvelle_solution->m1 = new_machine(liste->nb_taches);
    nouvelle_solution->m2 = new_machine(liste->nb_taches);
    return nouvelle_solution;
}

void ajouter_tache(s_taches * liste, s_tache * tache)
{
    liste->taches[liste->nb_taches] = tache;
    liste->nb_taches++;
}

void ajouter_tache_m( s_machine * machine,  s_tache * tache)
{
    s_taches *  l = (s_taches *)machine->liste_taches;
    ajouter_tache(l, tache);
    machine->nb_taches++;
}

void ajouter_tache_s(s_solution * s, int n_machine, int ntache)
{
    if (n_machine == 0)
        ajouter_tache_m(s->m1, s->taches->taches[ntache]);
    else if (n_machine == 1)
        ajouter_tache_m(s->m2, s->taches->taches[ntache]);
}

void swap (s_taches * liste, int x, int y)
{
    s_tache * t = liste->taches[x];
    liste->taches[x] = liste->taches[y];
    liste->taches[y] = t;
}

bool compare(s_tache * t1, s_tache * t2, int i)
{
    bool res = false;
    switch (i)
    {
        case 0:
            res = t1->start_at_least > t2->start_at_least;
            break;
        case 1:
            res = t1->start_at_least < t2->start_at_least;
            break;
        case 2:
            res = ((float)t1->weight/(float)t1->duration) < ((float)t2->weight/(float)t2->duration);
            break;
    }
    return res;
}


void trier_liste(s_taches * liste, int comp)
{
    int tab_size = liste->nb_taches;
    int i, j;
    for ( i = 0; i < tab_size - 1; i++) {
        for ( j = 1; j < tab_size - i; j++) {
            if ( compare(liste->taches[j-1], liste->taches[j],comp)) {
                swap(liste, j, j-1 );
            }
        }
    }
}


int evaluer_m( s_machine * machine)
{
    int i, time = machine->start_time, value = 0;
    for (i = 0; i < machine->nb_taches; i++)
    {
        s_taches* l = machine->liste_taches;
        s_tache * t = l->taches[i];
        time +=  t->duration;
        value += time * t->weight;
    }
    return value;
}

int evaluer(s_solution * solution)
{
    int res = 0;
    res += evaluer_m(solution->m1);
    res += evaluer_m(solution->m2);
    return res;
}

int starting_time(s_machine * machine)
{
    s_taches * l = machine->liste_taches;
    s_tache ** liste = l->taches;
    int i, times[machine->nb_taches+1];
    s_tache * t = liste[0];
    int start = t->start_at_least;
    times[0] = start;
    times[1] = times[0] + t->duration;
    for (i = 1; i < machine->nb_taches;i++)
    {
        t = liste[i];
        int time_diff = (t->start_at_least - times[1]);
        times[i+1] = times[i] + t->duration;
        if (time_diff > 0)
        {
            start += time_diff;
            times[i+1] += time_diff;
        }
    }
    machine->start_time = start;
    return start;
}

int ending_time( s_machine * machine)
{
    int i, time = machine->start_time;
    for (i = 0; i < machine->nb_taches; i++)
    {
        s_taches * l = machine->liste_taches;
        s_tache * t = l->taches[i];
        time +=  t->duration;
    }
    return time;
}

void tacheToString(s_tache * t)
{
    printf("P : %d , S : %d, D : %d\n", t->weight, t->start_at_least, t->duration);
}

void tachesToString(s_taches * t)
{
    int i;
    for (i = 0; i < t->nb_taches; i++)
    {
        s_tache * temp = t->taches[i];
        tacheToString(temp);
    }
}

void machineToString( s_machine * m)
{
    tachesToString((s_taches *)m->liste_taches);
}

void solutionToString( s_solution * s)
{
    printf("Liste des tâches : \n");
    tachesToString(s->taches);
    printf("Machine 1:\n");
    machineToString(s->m1);
    printf("Machine 2:\n");
    machineToString(s->m2);
}

void free_tache(s_tache * tache)
{
    free(tache);
}

void free_taches(s_taches * taches)
{
    int i;
    for (i = 0; i < taches->nb_taches; i++)
        if (taches->taches[i] != NULL)
            free_tache(taches->taches[i]);
    free(taches->taches);
    free(taches);
}

void free_taches_mini(s_taches * taches)
{
    free(taches->taches);
    free(taches);
}

void free_machine(s_machine * machine)
{
    free_taches_mini((s_taches *)machine->liste_taches);
    free(machine);
}

void free_solution(s_solution * solution)
{
    free_machine(solution->m1);
    free_machine(solution->m2);
    free(solution);
}

