#include <random>
#include <sstream>
#include "nodes/EANode/systems/SSGA.hpp"

using namespace std;

SSGA::SSGA(SelectionStrategy * strategy) : EvolutionarySystem(strategy) {
	this->niching = NULL;
}

SSGA::SSGA(
	SelectionStrategy * strategy,
	unsigned int seed
) : EvolutionarySystem(strategy, seed) {
	this->niching = NULL;
}
SSGA::SSGA(
	SelectionStrategy * strategy,
	NichingStrategy * niching
) : EvolutionarySystem(strategy) {
	this->niching = niching;
}

SSGA::SSGA(
	SelectionStrategy * strategy,
	NichingStrategy * niching,
	unsigned int seed
) : EvolutionarySystem(strategy, seed) {
	this->niching = niching;
}

vector<Genome*> SSGA::breedMutateSelect(
	vector<Genome*> initialPopulation,
	vector<float> & populationFitnesses,
	CrossoverOperation * cross,
	MutationOperation * mutation,
	vector<ObjectiveFunction*> objectives,
	std::string speciesNode
) {
	vector<Genome*> finalPopulation(initialPopulation.size(), NULL);
	vector<unsigned int> parentIndices;
	vector<Genome*> parents, children;

	for (int i = 0; i < 2; i++) {
		parentIndices.push_back(this->getParent(
			initialPopulation,
			populationFitnesses
		));
		parents.push_back(initialPopulation[parentIndices[i]]);
	}

	children = this->produceChildren(
		parents,
		cross,
		mutation,
		speciesNode
	);

	vector<unsigned int> replacementIndices = parentIndices;
	if (niching != NULL)
		replacementIndices = this->niching->getIndices(
			initialPopulation,
			children
		);

	vector<float> newFitnesses;

	for (unsigned int i = 0; i < children.size(); i++) {
		newFitnesses.push_back(this->evaluateFitness(
			children[i],
			objectives
		));

		if (newFitnesses[i]
			> populationFitnesses[replacementIndices[i]]
		) {
			finalPopulation[replacementIndices[i]] = children[i];
			populationFitnesses[replacementIndices[i]]
				= newFitnesses[i];
		} else {
			delete(children[i]);
		}
	}

	for (unsigned int i = 0; i < finalPopulation.size(); i++)
		if (finalPopulation[i] == NULL)
			finalPopulation[i] = new Genome(initialPopulation[i]);

	return finalPopulation;
}

bool SSGA::hasNiching() {
	return true;
}

NichingStrategy * SSGA::getNiching() {
	return this->niching;
}