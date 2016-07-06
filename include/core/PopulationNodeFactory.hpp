#include "PopulationNode.hpp"
#include <cstdarg>
#pragma once

class PopulationNodeFactory {
	private:

	protected:

	public:
	template <typename NodeType, typename... params>
	static PopulationNode * createNode(
		unsigned int populationSize,
		std::vector<Locus*> loci,
		std::vector<ObjectiveFunction*> objectives,
		ToStringFunction * populationToString,
		std::vector<EndCondition*> conditions,
		std::string nodeName,
		unsigned int accelerationFactor,
		params... as
	);
};

template<typename NodeType, typename... params>
static PopulationNode * createNode(
	unsigned int populationSize,
	std::vector<Locus*> loci,
	std::vector<ObjectiveFunction*> objectives,
	ToStringFunction * populationToString,
	std::vector<EndCondition*> conditions,
	std::string nodeName,
	unsigned int accelerationFactor,
	params... as
) {
	return new NodeType(
		populationSize,
		loci,
		objectives,
		populationToString,
		conditions,
		nodeName,
		accelerationFactor,
		as...
	);
}
