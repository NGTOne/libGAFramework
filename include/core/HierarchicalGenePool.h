//This is a dual-purpose class for gene pools - it serves as a "base"
//GA, and also as a gene pool for individuals in hierarchical GAs
//Since these functions are, by and large, very similar, they can be
//combined together into one class
#include "SelectionStrategy.h"
#include <string>
#pragma once

class HierarchicalGenePool : public GenePool {
	private:

	protected:
	Individual ** myPopulation;

	int * populationFitnesses;

	int maxGenerations;
	int currentGeneration;

	int populationSize;

	//In case we already know the optimum - needs to be specified for
	//every level of the hierarchy in an HGA, or it effectively becomes
	//meaningless
	bool knownOptimum;
	int * optimumGenome;
	int optimumFitness;
	double epsilon;
	bool optimumFound;

	//Specifies how many generations should pass by "silently"
	//every time nextGeneration() is called - might be a useful parameter
	//for HGAs (to accelerate growth at the lower levels)
	int numIterationsPerGeneration;

	SelectionStrategy * myStrategy;

	public:

	void sortPopulation();

	//If we don't know the optimum
	HierarchicalGenePool(int newPopulationSize, Individual * templateIndividual, int myMaxGenerations, int numIterations, SelectionStrategy * newStrategy);

        HierarchicalGenePool(int newPopulationSize, Individual * templateIndividual, int myMaxGenerations, int numIterations, int newSeed, SelectionStrategy * newStrategy);

	//If we do know the optimum
	HierarchicalGenePool(int newPopulationSize, Individual * templateIndividual, int myMaxGenerations, int numIterations, SelectionStrategy * newStrategy, int optimalGenome[]);

        HierarchicalGenePool(int newPopulationSize, Individual * templateIndividual, int myMaxGenerations, int numIterations, int newSeed, SelectionStrategy * newStrategy, int optimalGenome[]);

	void init(int newPopulationSize, Individual * templateIndividual, int myMaxGenerations, int numIterations, SelectionStrategy * newStrategy);

	//Evaluates the fitnesses of the population of this particular
	//GenePool - basically a convenience thing
	void evaluateFitnesses();

	//Evaluates the fitnesses of a given population of individuals
	//Doesn't care what their genetic makeup is - uses their fitness
	//functions
	int * evaluateFitnesses(Individual ** populationToEval, int populationToEvalSize);

	//When we need a specific individual
	void * getIndex(int index);

	//Run one generation
	void nextGeneration();

	//For HGAs - if we want to run multiple generations of a lower-level
	//gene pool for every one of a higher-level one, this is how
	//Basically a loop wrapped around nextGeneration()
	void runGenerations();

	std::string toString();
};