#include "genetic.h"

///////////////////////////////////// INDIVIDU
s_individu * new_individu()
{
    s_individu * new_indiv = (s_individu *) malloc (sizeof(s_individu));
    new_indiv->genes = (int *)malloc(sizeof(int)*TAILLE_GENOME);
    new_indiv->fitness = 0;
    new_indiv->aevaluer = true;

}
int retourneGene(s_individu * individu, int index)
{
    if (index >= 0 && index < TAILLE_GENOME)
        return individu->genes[index];
    return 0;
}


int fixerGene(s_individu * individu, int index, int valeur) {
    if (index >= 0 && index < TAILLE_GENOME)
    {
        individu->genes[index] = valeur;
        individu->aevaluer = true;
    }
}

int retourneTaille() {
    return TAILLE_GENOME;
}

s_solution * retourneSolution(s_individu * individu)
{
    s_solution * S = new_solution(PROBLEME);
    return S;
}

int retourneFitness(s_individu * individu) {
	if (individu->aevaluer)
        individu->fitness = evaluer(retourneSolution(individu));
    return individu->fitness;
}

void mettreAEvaluer(s_individu * individu){
	individu->aevaluer = true;
}

    // pour l'afichage
void individuToString(s_individu * individu) {
    int i;
    for (i = 0; i < TAILLE_GENOME; i++) {
        printf("%d",retourneGene(individu, i));
    }
    printf("\n");
}

int compareIndividu(s_individu * indiv1,s_individu * indiv2){
	return retournerFitness(indiv1) - retourneFitness(indiv2) ;
}

int retourneDistanceAvec(s_individu * indiv1,s_individu * indiv2){
	int dist = 0, i;
	for (i = 0; i < TAILLE_GENOME; i++)
	    if(retourneGene(indiv1,i) != retourneGene(indiv2,i))
            dist ++;
	return dist;
}
