#include "core/meta/MetaPopulationFactory.hpp"
#include "core/PopulationNode.hpp"
#include "core/Apportionment.hpp"
#include "core/ObjectiveFunction.hpp"
#include "core/meta/MetaPopulationObjective.hpp"
#include "core/meta/MetaPopulationApportionment.hpp"
#include "core/meta/MetaPopulationToString.hpp"
#include "loci/PopulationLocus.hpp"
#include "exception/InvalidBlanketException.hpp"

#include <set>

std::vector<PopulationNode*> MetaPopulationFactory::getAllHierarchicalNodes(
	std::vector<PopulationNode*> nodes
) {
	std::set<Locus*> constructiveLoci;
	std::vector<PopulationNode*> unmatchedNodes;
	for (unsigned int i = 0; i < nodes.size(); i++) {
		constructiveLoci = nodes[i]->getConstructiveLoci();
		for (auto k : constructiveLoci)
			unmatchedNodes.push_back(
				((PopulationLocus*)k)->getNode()
			);
	}

	return unmatchedNodes;
}

bool MetaPopulationFactory::isCompleteBlanket(
	std::vector<PopulationNode*> nodes
) {
	std::vector<PopulationNode*> unmatchedNodes =
		MetaPopulationFactory::getAllHierarchicalNodes(nodes);

	unsigned int i = 0, k = 0;
	bool matched;
	while (i < nodes.size()) {
		matched = false;
		while (k < unmatchedNodes.size() && !unmatchedNodes.empty()) {
			if (unmatchedNodes[k] == nodes[i]) {
				unmatchedNodes.erase(
					unmatchedNodes.begin() + k
				);
				nodes.erase(nodes.begin() + i);
				i = k = 0;
				matched = true;
			} else {
				k++;
			}
		}
		k = 0;
		if (!matched) i++;
	}

	// Implies that we only have one root node
	return unmatchedNodes.empty() && nodes.size() == 1;
}

bool MetaPopulationFactory::isValidBlanket(
	PopulationNode * topNode,
	std::vector<PopulationNode*> secondaryNodes
) {
	std::vector<PopulationNode*> nodes = secondaryNodes;
	nodes.push_back(topNode);

	if (!MetaPopulationFactory::isCompleteBlanket(nodes)) return false;

	return true;
}

PopulationNode * MetaPopulationFactory::createMeta(
	PopulationNode * metaNode,
	std::vector<ObjectiveFunction *> flattenedObjectives,
	ToStringFunction * flattenedToString,
	PopulationNode * topNode,
	std::tuple<
		ApportionmentFunction *,
		AggregationFunction *
	> topNodeApportionment,
	std::vector<std::tuple<
		PopulationNode *,
		ApportionmentFunction *,
		AggregationFunction *
	>> secondaryNodes
) {
	std::vector<PopulationNode*> secondaryPopNodes;
	for (unsigned int i = 0; i < secondaryNodes.size(); i++)
		secondaryPopNodes.push_back(std::get<0>(secondaryNodes[i]));
	if (!MetaPopulationFactory::isValidBlanket(topNode, secondaryPopNodes))
		throw InvalidBlanketException();

	std::vector<Locus*> newLoci;
	newLoci.push_back(new PopulationLocus(topNode));
	for (unsigned int i = 0; i < secondaryNodes.size(); i++)
		newLoci.push_back(new PopulationLocus(
			std::get<0>(secondaryNodes[i])
		));

	metaNode->setLoci(newLoci);

	// The normal varieties won't work on a meta-population anyways
	metaNode->setObjectives({});
	metaNode->setToString(new MetaPopulationToString(flattenedToString));

	for (unsigned int i = 0; i < flattenedObjectives.size(); i++)
		metaNode->addObjective((ObjectiveFunction*)
			new MetaPopulationObjective(flattenedObjectives[i])
		);

	topNode->addObjective(new MetaPopulationApportionment(
		metaNode,
		std::get<0>(topNodeApportionment),
		std::get<1>(topNodeApportionment)
	));

	for (unsigned int i = 0; i < secondaryNodes.size(); i++)
		std::get<0>(secondaryNodes[i])->addObjective(
			(ObjectiveFunction*)new MetaPopulationApportionment(
				metaNode,
				std::get<1>(secondaryNodes[i]),
				std::get<2>(secondaryNodes[i])
			)
		);

	return metaNode;
}
