#include "structs.h"


s_tache * new_tache(int w, int s, int d)
{
    s_tache * nouvelle_tache = (s_tache *) malloc (sizeof( s_tache));
    nouvelle_tache->weight = w;
    nouvelle_tache->start_at_least = s;
    nouvelle_tache->duration = d;
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
    nouvelle_machine->liste_taches = ( s_tache **) malloc (sizeof( s_tache * )*n);
    nouvelle_machine->nb_taches = 0;
    nouvelle_machine->start_time = 0;
}

void ajouter_tache(s_taches * liste, s_tache * tache)
{
    liste->taches[liste->nb_taches] = tache;
    liste->nb_taches++;
}

void trier_liste(s_taches * liste)
{

}

void ajouter_tache_m( s_machine * machine,  s_tache * tache)
{
    ajouter_tache(machine->liste_taches, tache);
    machine->nb_taches++;
}

int evaluer( s_machine * machine)
{
    int i, time = machine->start_time, value = 0;
    for (i = 0; i < machine->nb_taches; i++)
    {
        time +=  machine->liste_taches[i]->duration;
        value += time * machine->liste_taches[i]->weight;
    }
    return value;
}

int ending_time( s_machine * m)

void toString( s_machine * m)
{
    int i;
    printf("Machine\n");
    for (i = 0; i < m->nb_taches; i++)
    {
         s_tache * temp = m->liste_taches[i];
        printf("P : %d , S : %d, D : %d\n", temp->weight, temp->start_at_least, temp->duration);
    }
}

int main ()
{
    int i;
     s_machine * M1, * M2;
    M1 = new_machine(10);
    M2 = new_machine(10);
    for (i = 0; i < 10; i++)
    {
         s_tache * tache = new_tache(1,i,1);
        ajouter_tache_m(M1, tache);

    }
    printf("%d , %d\n", evaluer(M1), evaluer(M2));
}
