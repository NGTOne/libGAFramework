#include <libGAFramework/GAFramework.hpp>
#include <string>
#pragma once

class OneMaxFitness : public FitnessFunction {
	private:

	protected:

	public:
	OneMaxFitness();
	PropertiesList * checkFitness(GenePool ** pools, int * indexes, int genomeLength);

	std::string toString(GenePool ** pools, int * indexes, int genomeLength);
};
