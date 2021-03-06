#include <libHierGA/HierGA.hpp>
#include <string>
#pragma once

class LongestFragmentFitness : public ObjectiveFunction {
	private:

	protected:

	public:
	LongestFragmentFitness();
	Fitness checkFitness(Genome* target);
};

class LongestFragmentToString : public HierarchicalToString {
	private:

	protected:

	public:
	LongestFragmentToString(
		HierarchicalToString::mode printMode
			= HierarchicalToString::flatten
	);
	std::string stringifySegment(std::vector<Gene*> segment);
};

class LongestFragmentApportionment : public ApportionmentFunction {
	private:

	protected:

	public:
	double apportionFitness(
		Genome* recipient,
		Genome* provider,
		unsigned int recipientStartIndex,
		std::vector<unsigned int> relevantRecipientIndices,
		Fitness providerFitness
	);
};
