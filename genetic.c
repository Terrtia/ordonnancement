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

//POPULATION


s_population * new_population(int nb_max)
{
    s_population * pop = (s_population *) malloc (sizeof(s_population));
    pop->individus = (s_individu **) malloc (sizeof(s_individu *)*nb_max);
    pop->nb_pop_max = nb_max;
    pop->nb_individus = 0;
    return pop;
}

s_individu ** retournePopulation(s_population * pop)
{
    return pop->individus;
}

s_individu * retourneIndividu(s_population * pop, int index)
{
    if (index < pop->nb_individus)
        return pop->individus[index];
    return NULL;
}

int retourneTaillePopulation(s_population * pop)
{
    return pop->nb_individus;
}

void ajouterIndividu(s_population * pop, s_individu * ind)
{
    if (pop->nb_individus < pop->nb_pop_max)
        pop->individus[pop->nb_individus] = ind;
    else
        printf("Erreur, population complete. Ajout impossible.");
}

void evaluerPopulation(s_population * pop)
{
    int i;
    for (i = 0; i < pop->nb_individus; i++) {
        s_individu * individu = pop->individus[i];
        mettreAEvaluer(individu);
        retourneFitness(individu);
    }
}

void swapIndividu(s_population * pop, int x, int y)
{
    s_individu * i = pop->individus[x];
    pop->individus[x] = pop->individus[y];
    pop->individus[y] = i;
}

void trierPopulation(s_population * pop)
{
    int tab_size = pop->nb_individus;
    int i, j;
    for ( i = 0; i < tab_size - 1; i++) {
        for ( j = 1; j < tab_size - i; j++) {
            if ( compareIndividu(pop->individus[j-1], pop->individus[j])) {
                swapIndividu(pop, j, j-1 );
            }
        }
    }
}

void populationToString(s_population * pop)
{
    printf("J'ai rien fait :p\n");
}

double retourneFitnessMoyenne(s_population * pop)
{
    int i, s = 0;
    for (i = 0; i < pop->nb_individus; i++)
    {
        s += retourneFitness(pop->individus[i]);
    }
    return ((double)s/(double)pop->nb_individus);
}

double retourneDiversite(s_population * pop)
{
    int i, j;
    double diversite = 0.0;
    for (i = 0; i < pop->nb_individus - 1; i++)
    {
        s_individu * I1 = pop->individus[i];
        for (j = i+1; j < pop->nb_individus - 1; j++)
        {
            s_individu * I2 = pop->individus[j];
            /*if (!Ii.equals(Ij))
            {*/
                diversite += retourneDistanceAvec(I1,I2);
            //}
        }
    }
    diversite = diversite/pop->nb_individus;
    return diversite;
}

//ALGORITHME

s_algorithme * init_algorithme()
{
    s_algorithme * algo = (s_algorithme *) malloc (sizeof(s_algorithme));
    algo->taillePopulationParents = 10;
    algo->taillePopulationEnfants = 50;
    algo->tailleTournoi = 5;
    algo->tauxMutation = 0.4;
    algo->maxGenerations  = 50;
    algo->maxEvaluations  = 300;
    algo->verbose   = false;
    algo->generationsEffectuee = 0;
    algo->meilleurFitness  = 0xffff;
    algo->pireFitness = 0;
}

bool estFini(s_algorithme * algo) {
	if(algo->generationsEffectuee >= algo->maxGenerations)
	    return true;
	return false;
}

s_individu * croisementUniforme(s_individu * i1, s_individu * i2);

void mutation (s_algorithme * algo, s_individu * indiv)
{
    int i = 0;
}

s_population * remplacement(s_population * parents, s_population * enfants)
{

}

s_individu * selectionTournoi(s_algorithme * algo, s_population * pop)
{
}

s_population * creerEnfants(s_algorithme * algo, s_population * parents)
{
    int i;
    s_population * enfants = new_population(algo->taillePopulationEnfants);
    for (int i = 0; i < algo->taillePopulationEnfants; i++)
    {
        s_ndividu * c1, * c2;
        c1 = selectionTournoi(algo, parents);
        parents.retournePopulation().remove(c1);
        c2 = selectionTournoi(algo, parents);
        ajouterIndividu(c1);
        s_individu * enfant = croisementUniforme(algo, c1,c2);
        mutation(algo, enfant);
        ajouterIndividu(enfants, enfant);
    }
    return enfants;
}

s_population * executerUneGeneration(s_algorithme * algo, s_population * parents)
{
    s_population * enfants = creerEnfants(algo, parents);
    evaluerPopulation(enfants);
    s_population * survivants = Remplacement(parents, enfants);
    return survivants;
}

s_individu * executerAlgortihme(s_algorithme * algo)
{
    s_population * pop = new new_population(taillePopulationParents);
	evaluerPopulation(pop);
	trierPopulation(pop);

	algo->meilleurSolution = retourneIndividu(pop, 0);
    algo->meilleurSolutionGlobale = retourneIndividu(pop,0);

	while ( !estFini(algo) ){
	    // compteur de génération
	    algo->generationsEffectuee++;
/*
	    if (algo->verbose){
		System.out.println("# =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
		System.out.println("# Population parent IN : "+pop);
	    }*/

	    // on execute une generation
	    pop = executerUneGeneration(algo, pop);

	    /*if (this.verbose)
		System.out.println("# Population parent OUT: "+pop);	*/

	    //  Récupération de la meilleure/pire solution
	    // (pop est sensé être trié)
        algo->meilleurSolution = retourneIndividu(pop, 0);
	    algo->meilleurFitness  = retourneFitness(algo->meilleurSolution);
	    algo->pireFitness      = retourneFitness(retourneIndividu(pop,algo->taillePopulationParents-1));
	    if (algo->meilleurFitness < retourneFitness(algo->meilleurSolutionGlobale))
            algo->meilleurSolutionGlobale = algo->meilleurSolution;

	    // On affiche le nnuméro de la generation, le nombre d'evaluation
	    // la fitness du meilleur et le meuilleur indiv et la diversité

	    /*System.out.println("" + Fitness.retourneNombreEvaluations() +
			       " " + algo->meilleurFitness +
			       " " + algo->pireFitness +
			       " " + pop.retourneFitnessMoyenne() +
			       " " + pop.retourneDiversite() +
			       " " + algo->generationsEffectuee);*/
	}

	return meilleurSolution;
}
