#include "core/meta/MetaPopulationFactory.hpp"
#include "core/PopulationNode.hpp"
#include "core/Apportionment.hpp"
#include "core/ObjectiveFunction.hpp"
#include "core/meta/MetaPopulationObjective.hpp"
#include "core/meta/MetaPopulationApportionment.hpp"
#include "loci/PopulationLocus.hpp"

PopulationNode * MetaPopulationFactory::createMeta(
	PopulationNode * metaNode,
	std::vector<ObjectiveFunction *> flattenedObjectives,
	PopulationNode * topNode,
	Apportionment * topNodeApportionment,
	std::vector<std::tuple<
		PopulationNode *,
		Apportionment *
	>> secondaryNodes
) {
	std::vector<Locus*> newLoci;
	newLoci.push_back(new PopulationLocus(topNode));
	for (unsigned int i = 0; i < secondaryNodes.size(); i++)
		newLoci.push_back(new PopulationLocus(
			std::get<0>(secondaryNodes[i])
		));

	metaNode->setLoci(newLoci);

	metaNode->setObjectives({});
	for (unsigned int i = 0; i < flattenedObjectives.size(); i++)
		metaNode->addObjective(
			new MetaPopulationObjective(flattenedObjectives[i])
		);

	for (unsigned int i = 0; i < secondaryNodes.size(); i++)
		std::get<0>(secondaryNodes[i])->addObjective(
			new MetaPopulationApportionment(
				metaNode,
				std::get<1>(secondaryNodes[i])
			)
		);

	return metaNode;
}