#include "structs.h"


s_tache * new_tache(int w, int s, int d)
{
    s_tache * nouvelle_tache = (s_tache *) malloc (sizeof( s_tache));
    nouvelle_tache->weight = w;
    nouvelle_tache->start_at_least = s;
    nouvelle_tache->duration = d;
    printf("%d, %d, %d\n",w,s,d);
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
    ajouter_tache(machine->liste_taches, tache);
    machine->nb_taches++;
}

void ajouter_tache_s(s_solution * s, int n_machine, s_tache * tache)
{
    if (n_machine == 1)
        ajouter_tache_m(s->m1, tache);
    else if (n_machine == 2)
        ajouter_tache_m(s->m2, tache);
}

void trier_liste(s_taches * liste)
{

}

int evaluer( s_machine * machine)
{
    int i, time = machine->start_time, value = 0;
    for (i = 0; i < machine->nb_taches; i++)
    {
        s_taches * l = machine->liste_taches;
        s_tache * t = l->taches[i];
        time +=  t->duration;
        value += time * t->weight;
    }
    return value;
}

int ending_time( s_machine * machine)
{
    int i, time = machine->start_time, value = 0;
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
    printf("Machine\n");
    tachesToString(m->liste_taches);
}

void solutionToString( s_solution * s)
{
    tachesToString(s->taches);
    machineToString(s->m1);
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

void free_machine(s_machine * machine)
{
    free_taches(machine->liste_taches);
    free(machine);
}

void free_solution(s_solution * solution)
{
    //free_machine(solution->m1);
    //free_machine(solution->m2);
    //free_taches(solution->taches);
    free(solution);
}

//int main (){
    /*int i;
    s_taches * liste = new_taches(10);
    s_solution * S = new_solution(liste);
    solutionToString(S);
    for (i = 0; i < 10; i++)
    {
        s_tache * tache = new_tache(1,i,1);
        ajouter_tache(liste,tache);
        tacheToString(liste->taches[0]);
        ajouter_tache_s(S, 2, tache);

    }
    solutionToString(S);
    free_solution(S);
    printf("%d , %d\n", evaluer(S->m1), evaluer(S->m2));*/

//}

