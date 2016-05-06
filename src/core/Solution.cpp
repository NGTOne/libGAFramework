#include "core/Solution.hpp"
#include "core/Genome.hpp"
#include <cstdlib>
#include <chrono>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

Solution::Solution() {
	init(NULL, NULL);
}

Solution::Solution(Genome * genome) {
	init(genome, NULL);
	evaluateFitness();
}

Solution::Solution(Solution * copyTarget, bool randomize) {
	Genome * genome = new Genome(copyTarget->getGenome(), randomize);
	if (randomize) {
		init(genome, NULL);
		evaluateFitness();
	} else {
		init(genome, copyTarget->getProperties());
	}
}

Solution::Solution(Solution * copyTarget, int rawGenes[]) {
	Genome * genome = new Genome(copyTarget->getGenome(), rawGenes);
	init(genome, NULL);
	evaluateFitness();
}

Solution::~Solution() {
	if (genome != NULL) {
		delete(genome);
	}

	if (properties != NULL) {
		delete(properties);
	}
}

void Individual::init(GeneNode ** newGeneNodes, int newGenomeLength, CrossoverOperation * newCrossover, MutationOperation * newMutation, FitnessFunction * newFitness, ToStringFunction * newToString, unsigned newSpeciesID) {
	int * newGenome = (int*)malloc(sizeof(int)*newGenomeLength);

	properties = NULL;

	//This way, we don't actually need to know how many genes are in
	//each pool - it can be 2 or 2000
	for (int i = 0; i < newGenomeLength; i++) {
		newGenome[i] = newGeneNodes[i]->chooseRandomMember();
	}

	genome = new Genome(newGenome, newGenomeLength, newGeneNodes);

	free(newGenome);

        myCrossover = newCrossover;
        myMutation = newMutation;
        myFunction = newFitness;
	speciesID = newSpeciesID;
	myToString = newToString;

	if (myFunction == NULL) {
		fitnessOverridden = true;
		properties = new PropertiesList(); //Fitness of 0
	} else {
		fitnessOverridden = false;
	}
}

//Exactly what it says on the tin - wraps around the CrossoverOperation
//and spits out two offspring (which are new instances of Individual)
//Returns NULL if the two parents have different gene pools
Individual ** Individual::crossoverOperation(Individual * otherParent) {
	int firstKidsLength, secondKidsLength;
	Genome * otherGuysGenome;
	Genome ** kidsGenome;
	Individual ** kids = (Individual**)malloc(sizeof(Individual*)*2);
	int otherGuysLength;

	if (sameSpecies(otherParent) == false) {
		return NULL;
	}

	otherGuysGenome = otherParent->getGenome();

	kidsGenome = myCrossover->crossOver(genome, otherGuysGenome);

	kids[0] = new Individual(kidsGenome[0], myCrossover, myMutation, myFunction, myToString, speciesID);
	kids[1] = new Individual(kidsGenome[1], myCrossover, myMutation, myFunction, myToString, speciesID);
	
	delete(kidsGenome[0]);
	delete(kidsGenome[1]);
	free(kidsGenome);

	return kids;
}

//Wraps around the MutationOperation object and spits out a mutant
//version of this Individual (which is a new instance of Individual)
Individual * Individual::mutationOperation() {
	Genome * mutantGenome;
	int maxValues[genome->getGenomeLength()];

	GeneNode ** myGeneNodes = genome->getGeneNodes();

	for (int i = 0; i < genome->getGenomeLength(); i++) {
		maxValues[i] = myGeneNodes[i]->getPopulationSize()-1;
	}

	mutantGenome = myMutation->mutate(genome, maxValues);
	Individual * mutant = new Individual(mutantGenome, myCrossover, myMutation, myFunction, myToString, speciesID);

	delete(mutantGenome);

	return mutant;
}

int Individual::checkFitness() {
	PropertiesList * newProperties;

	if (fitnessOverridden == false) {
		newProperties = myFunction->checkFitness(genome->getGeneNodes(), genome->getGenome(), genome->getGenomeLength());

		if (properties != NULL) {
			delete(properties);
		}

		properties = newProperties;
		return newProperties->getFitness();
	} else {
		return getFitness();
	}
}

int Individual::getFitness() {
	return properties->getFitness();
}

PropertiesList * Individual::getProperties() {
	return properties;
}

//Necessary for verifying whether or not two Individuals are of the same
//species
unsigned Individual::getSpeciesID() {
	return speciesID;
}

Individual * Individual::deepCopy() {
	PropertiesList * newPropertiesList = new PropertiesList();
	Genome * newGenome = new Genome(genome->getGenome(), genome->getGenomeLength(), genome->getGeneNodes());

	PropertyBase ** myProperties = properties->getProperties();
	int numProperties = properties->getNumProperties();

	for (int i = 0; i < numProperties; i++) {
		PropertyBase * propertyCopy = myProperties[i]->makeCopy();
		newPropertiesList->addProperty(propertyCopy);
	}

	newPropertiesList->setFitness(properties->getFitness());

	Individual * myCopy = new Individual(newGenome, myCrossover, myMutation, myFunction, speciesID, newPropertiesList, myToString, fitnessOverridden);

	return myCopy;
}

Individual * Individual::copyWithNewGenome(Genome * newGenome) {
	Individual * myCopy = new Individual(
		newGenome,
		myCrossover,
		myMutation,
		myFunction,
		myToString,
		speciesID
	);

	return myCopy;
}

//For populating PopulationNodes - basically, use this Individual as a
//template, just generate a new genome for it
Individual * Individual::makeRandomCopy() {
	Individual * myCopy = new Individual(genome->getGeneNodes(), genome->getGenomeLength(), myCrossover, myMutation, myFunction, myToString, speciesID);

	return myCopy;
}

//In case we need to copy a given Individual's gene pool/function set, but with
//a new genome
//WARNING - THIS IS VERY DANGEROUS IF DONE MANUALLY
//If the chromosomes in newGenome are out of range for their gene pools, bad
//things will happen
Individual * Individual::makeSpecifiedCopy(int newGenome[]) {
	Genome * tempGenome = new Genome(newGenome, genome->getGenomeLength(), genome->getGeneNodes());

	Individual * myCopy = new Individual(tempGenome, myCrossover, myMutation, myFunction, myToString, speciesID);

	delete(tempGenome);

	return myCopy;
}

GeneNode ** Individual::getGeneNodeList() {
	return genome->getGeneNodes();
}

//Necessary for crossover
Genome * Individual::getGenome() {
	return genome;
}

void Individual::setFitness(int newFitness) {
	fitnessOverridden = true;

	properties->setFitness(newFitness);
}

void Individual::setArtificiality(bool newArtificiality) {
	fitnessOverridden = newArtificiality;
}

//In a hierarchical GA, it's important to know whether or not two individuals
//are from the same part of the hierarchy before attempting to breed them
//Comparing which gene pools they draw from provides an easy way to do this
bool Individual::sameSpecies(Individual * otherIndividual) {
	unsigned otherGuysID;

	otherGuysID = otherIndividual->getSpeciesID();

	if (speciesID == otherGuysID) {
		return true;
	} else {
		return false;
	}
}

int Individual::getGenomeLength() {
	return genome->getGenomeLength();
}

bool Individual::usesComponent(Individual * component) {
	GeneNode ** pools;
	int i, genomeLength, *indexes;

	pools = genome->getGeneNodes();
	genomeLength = genome->getGenomeLength();
	indexes = genome->getGenome();

	for (i = 0; i < genomeLength; i++) {
		if (pools[i]->getIndex(indexes[i]) == component) return true;
	}
	return false;
}

string Individual::toGenomeString() {
	return myToString->toString(genome->getGeneNodes(), genome->getGenome(), genome->getGenomeLength());
}

string Individual::toString() {
	string returnString;
	stringstream ss;

	ss << "Genome: " << toGenomeString() << "\nCrossover information:\n" << myCrossover->toString() << "Mutation information:\n" << myMutation->toString() << "Species ID: " << speciesID << "\n";

	returnString = ss.str();

	return returnString;
}