#include <random>
#include <chrono>
#include <sstream>
#include "crossovers/UniformCrossover.hpp"

using namespace std;

UniformCrossover::UniformCrossover(double crossoverChance) : CrossoverOperation() {
	crossoverRate = crossoverChance;
}

UniformCrossover::UniformCrossover(double crossoverChance, unsigned newSeed) : CrossoverOperation(newSeed) {
	crossoverRate = crossoverChance;
}

Genome ** UniformCrossover::crossOver(Genome * firstGenome, Genome * secondGenome) {
	int shortestGenome;

	int firstGenomeLength = firstGenome->getGenomeLength();
	int secondGenomeLength = secondGenome->getGenomeLength();

	int * genomeOne = firstGenome->getGenome();
	int * genomeTwo = secondGenome->getGenome();

	if (firstGenomeLength > secondGenomeLength) {
		shortestGenome = secondGenomeLength;
	} else {
		shortestGenome = firstGenomeLength;
	}

	//We're generating two children - each one uses the same crossover
	//points, but draws from the parents in a different order
	int ** children = (int**)malloc(sizeof(int*)*2);

	children[0] = (int*)malloc(sizeof(int)*shortestGenome);
	children[1] = (int*)malloc(sizeof(int)*shortestGenome);

	uniform_real_distribution<double> distribution(0, 1);

	for (int i = 0; i < shortestGenome; i++) {
		if (distribution(generator) <= crossoverRate) {
			children[0][i] = genomeTwo[i];
			children[1][i] = genomeOne[i];
		} else {
			children[0][i] = genomeTwo[i];
			children[1][i] = genomeOne[i];
		}
	}

	Genome ** returnChildren = (Genome**)malloc(sizeof(Genome*)*2);

	returnChildren[0] = new Genome(children[0], shortestGenome, firstGenome->getGeneNodes());
	returnChildren[1] = new Genome(children[1], shortestGenome, secondGenome->getGeneNodes());

	free(children[0]);
	free(children[1]);
	free(children);

	return returnChildren;
}

string UniformCrossover::toString() {
	string returnString = "";
	stringstream ss;

	ss << "Type: Uniform Crossover\nRandom Seed: " << seed << "\nCrossover Rate: " << crossoverRate << "\n";

	returnString = ss.str();

	return returnString;
}
