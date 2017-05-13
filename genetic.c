#include "genetic.h"

///////////////////////////////////// INDIVIDU
s_individu * new_individu()
{
    s_individu * new_indiv = (s_individu *) malloc (sizeof(s_individu));
    new_indiv->genes = (int *)malloc(sizeof(int)*TAILLE_GENOME);
    new_indiv->fitness = 0;
    new_indiv->aevaluer = true;
    return new_indiv;

}
int retourneGene(s_individu * individu, int index)
{
    if (index >= 0 && index < TAILLE_GENOME)
        return individu->genes[index];
    return 0;
}

void fixerGene(s_individu * individu, int index, int valeur) {
    if (index >= 0 && index < TAILLE_GENOME)
    {
        individu->genes[index] = valeur;
        individu->aevaluer = true;
    }
}

void echangerGene(s_individu * individu, int i1, int i2) {
    if (i1 >= 0 && i1 < TAILLE_GENOME && i2 >= 0 && i2 < TAILLE_GENOME) {
        int res = individu->genes[i1];
        individu->genes[i1] = individu->genes[i2];
        individu->genes[i2] = res;
    } else {
        printf("Erreur, changement de gene non valide.\n");
    }
}

int retourneTaille() {
    return TAILLE_GENOME;
}

s_solution * retourneSolution(s_individu * individu)
{
    s_solution * S = new_solution(PROBLEME);
    int i, m1 = individu->genes[0];
    for (i = 1; i <= m1; i++)
    {
        ajouter_tache_s(S, 0, individu->genes[i]);
    }
    for (i = m1+1; i < TAILLE_GENOME; i++)
    {
        ajouter_tache_s(S, 1, individu->genes[i]);
    }
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
        printf("%d|",retourneGene(individu, i));
    }
    printf(" = %d\n", individu->fitness);
}

int compareIndividu(s_individu * indiv1,s_individu * indiv2){
	return retourneFitness(indiv1) - retourneFitness(indiv2) ;
}

int retourneDistanceAvec(s_individu * indiv1,s_individu * indiv2){
	int dist = 0, i;
	for (i = 0; i < TAILLE_GENOME; i++)
	    if(retourneGene(indiv1,i) != retourneGene(indiv2,i))
            dist ++;
	return dist;
}

void freeIndividu(s_individu * individu) {
    free(individu->genes);
    free(individu);
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

s_population * new_generate_population(int nb_max)
{
    s_population * pop = (s_population *) malloc (sizeof(s_population));
    pop->individus = (s_individu **) malloc (sizeof(s_individu *)*nb_max);
    pop->nb_pop_max = nb_max;
    pop->nb_individus = nb_max;
    int i,j, r;

    for (i = 0; i < nb_max; i++) {
        s_individu * indiv = new_individu();
        int taille = retourneTaille(indiv);
        int ttaches = taille -1;
        int taches[ttaches];
        for (j = 0; j < taille -1; j++)
            taches[j] = 0;
        int taillem1 = rand() % taille;
        fixerGene(indiv, 0, taillem1);
        for (j = 1; j <= taillem1; j++) {
            do {
                r = rand()%(ttaches);
            } while (taches[r] != 0) ;
            fixerGene(indiv, j, r);
            taches[r] = 1;
        }
        for (j = taillem1+1; j < taille; j++) {
            do {
                r = rand()%(ttaches);
            } while (taches[r] != 0) ;
            fixerGene(indiv, j, r);
            taches[r] = 1;
        }
        pop->individus[i] = indiv;
    }
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

s_individu * extraireIndividu(s_population * pop, int index)
{
    if (index < pop->nb_individus) {
        s_individu * res = pop->individus[index];
        pop->individus[index] = NULL;
        return res;
    }
    return NULL;
}

void insererIndividu(s_population * pop, s_individu * indiv, int index)
{
    if (index < pop->nb_individus) {
        pop->individus[index] = indiv;
    }
}

int retourneTaillePopulation(s_population * pop)
{
    return pop->nb_individus;
}

void ajouterIndividu(s_population * pop, s_individu * ind)
{
    if (pop->nb_individus < pop->nb_pop_max) {
        pop->individus[pop->nb_individus] = ind;
        pop->nb_individus++;
    }
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
            if ( compareIndividu(pop->individus[j-1], pop->individus[j]) > 0) {
                swapIndividu(pop, j, j-1 );
            }
        }
    }
}

void populationToString(s_population * pop)
{
    int i;
    for (i = 0; i < pop->nb_individus; i++) {
        if ( pop->individus[i] != NULL)
            individuToString(pop->individus[i]);
    }
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

void freePopulation(s_population * pop)
{
    free(pop->individus);
    free(pop);
}

void freeAllPopulation(s_population * pop)
{
    int i;
    for (i = 0; i < pop->nb_individus; i++) {
        if( pop->individus[i] != NULL)
            freeIndividu(pop->individus[i]);
    }
    free(pop->individus);
    free(pop);
}
//ALGORITHME

s_algorithme * init_algorithme()
{
    s_algorithme * algo = (s_algorithme *) malloc (sizeof(s_algorithme));
    algo->taillePopulationParents = 10;
    algo->taillePopulationEnfants = 50;
    algo->tailleTournoi = 5;
    algo->tauxMutation = 0.8;
    algo->maxGenerations  = 50000;
    algo->maxEvaluations  = 300;
    algo->verbose   = false;
    algo->generationsEffectuee = 0;
    algo->meilleurFitness  = 0xffff;
    algo->pireFitness = 0;
    return algo;
}

bool estFini(s_algorithme * algo) {
	if(algo->generationsEffectuee >= algo->maxGenerations)
	    return true;
	return false;
}

int chercheValeurLibre(int * taches, int taille)
{
    int i, r = rand() % taille;
    for (i = r; i < taille; i++){
        if (taches[i] == 0)
            return i;
    }
    for (i = 0; i < r; i++){
        if (taches[i] == 0)
            return i;
    }
    return -1;
}

s_individu * croisementUniforme(s_individu * i1, s_individu * i2)
{
    s_individu * indiv = new_individu();
    int taches[TAILLE_GENOME-1], i;
    for (i = 0; i < TAILLE_GENOME-1; i++)
        taches[i] = 0;
    double r = (double)(rand() % 16383)/16383.0;
    int v;
    if (r < 0.5) {
        v = retourneGene(i1, 0);
        fixerGene(indiv, 0, v);
    }
    else {
        v = retourneGene(i2, 0);
        fixerGene(indiv, 0, v);
    }
    for (i = 1; i < TAILLE_GENOME; i++) {
        r = (double)(rand() % 16383)/16383.0;
        if (r < 0.5) {
            v = retourneGene(i1, i);
            fixerGene(indiv, i, v);
        }
        else {
            v = retourneGene(i2, i);
            fixerGene(indiv, i, v);
        }
        taches[v]++;
    }
    for (i = 1; i < TAILLE_GENOME; i++) {
        int v = retourneGene(indiv, i);
        if (taches[v] > 1) {
            int nv = chercheValeurLibre(taches, TAILLE_GENOME - 1);
            fixerGene(indiv, i, nv);
            taches[v]--;
            taches[nv]++;
        }
    }
    return indiv;
}

void mutation (s_algorithme * algo, s_individu * indiv)
{
    int i = 0;
    double r = (double)(rand() % 16383)/16383.0;
    if (r < algo->tauxMutation) {
        i = (rand()%TAILLE_GENOME);
        fixerGene(indiv, 0, i);
    }
    for (i = 1; i < TAILLE_GENOME; i++) {
        r = (double)(rand() % 16383)/16383.0;
        if (r < algo->tauxMutation) {
            int j = i + (rand() % (TAILLE_GENOME-i));
            echangerGene(indiv, i, j);
        }
    }
}

s_population * remplacement(s_algorithme * algo, s_population * parents, s_population * enfants)
{
    	int taille =algo->taillePopulationParents;
    	s_population * nouveau = new_population(taille);
    	trierPopulation(parents);
    	trierPopulation(enfants);
    	int i, k = 0, l = 0;
    	for (i = 0; i < taille; i++) {
    		s_individu * best_p = retourneIndividu(parents, k);
    		s_individu * best_e = retourneIndividu(enfants, l);
    		if (retourneFitness(best_p) < retourneFitness(best_e)) {
    			ajouterIndividu(nouveau, extraireIndividu(parents, k));
    			k++;
    		} else {
    			ajouterIndividu(nouveau, extraireIndividu(enfants, l));
    			l++;
    		}
    	}
    	freeAllPopulation(parents);
    	freeAllPopulation(enfants);
    	return nouveau;
}

s_individu * selectionTournoi(s_algorithme * algo, s_population * pop)
{
    	int taille = algo->tailleTournoi, i, r;
    	if ( taille > retourneTaillePopulation(pop))
            taille = retourneTaillePopulation(pop);
    	int indexs[taille];
        s_population * candidats = new_population(taille);
    	s_individu * candidat;
    	for (i = 0; i < taille; i++)
    	{
    	    do {
                r = rand() % retourneTaillePopulation(pop);
                candidat = extraireIndividu(pop, r);
    	    } while (candidat == NULL) ;
    	    indexs[i] = r;
    		ajouterIndividu(candidats, candidat);
    	}
    	for (i = 0; i < taille; i++)
            insererIndividu(pop,retourneIndividu(candidats,i), indexs[i]);
    	trierPopulation(candidats);
    	s_individu * res = retourneIndividu(candidats, 0);
    	freePopulation(candidats);
    	return res;
}

s_population * creerEnfants(s_algorithme * algo, s_population * parents)
{

    int i;
    s_population * enfants = new_population(algo->taillePopulationEnfants);
    for (i = 0; i < algo->taillePopulationEnfants; i++)
    {
        s_individu * c1, * c2;
        c1 = selectionTournoi(algo, parents);
        c2 = selectionTournoi(algo, parents);
        s_individu * enfant = croisementUniforme(c1,c2);
        mutation(algo, enfant);
        ajouterIndividu(enfants, enfant);
    }
    return enfants;
}

s_population * executerUneGeneration(s_algorithme * algo, s_population * parents)
{
    s_population * enfants = creerEnfants(algo, parents);
    evaluerPopulation(enfants);
    s_population * survivants = remplacement(algo, parents, enfants);
    return survivants;
}

s_individu * executerAlgortihme(s_algorithme * algo)
{
    printf("Generation population. ");
    s_population * pop = new_generate_population(algo->taillePopulationParents);
    printf("Evaluation population. \n");
	evaluerPopulation(pop);
    printf("Trie population.\n");
	trierPopulation(pop);
    populationToString(pop);

	algo->meilleurSolution = retourneIndividu(pop, 0);
    algo->meilleurSolutionGlobale = retourneIndividu(pop,0);

	while ( !estFini(algo) ){
        //printf("Nouvelle generation :\n");
	    // compteur de génération
	    algo->generationsEffectuee++;


	    pop = executerUneGeneration(algo, pop);
        /*printf("Resultat:\n");
        populationToString(pop);
        printf("Generation terminee\n");*/


        algo->meilleurSolution = retourneIndividu(pop, 0);
	    algo->meilleurFitness  = retourneFitness(algo->meilleurSolution);
	    printf("Meilleur Fitness : %d\n", algo->meilleurFitness);
	    algo->pireFitness      = retourneFitness(retourneIndividu(pop,algo->taillePopulationParents-1));


	}
	return algo->meilleurSolution;
}
