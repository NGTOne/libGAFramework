#include "endconditions/IterationCountEnd.hpp"

IterationCountEnd::IterationCountEnd(unsigned int maxIterations) {
	this->maxIterations = maxIterations;
}

bool IterationCountEnd::checkCondition(
	vector<Genome*> genomes,
	vector<float> fitnesses,
	unsigned int currentIteration
) {
	return currentIteration >= this->maxIterations;
}
