#include "core/CrossoverOperation.hpp"
#include "core/EndCondition.hpp"
#include "core/FitnessFunction.hpp"
#include "core/ToStringFunction.hpp"
#include "core/GeneNode.hpp"
#include "core/EvolutionarySystem.hpp"
#include "core/Genome.hpp"
#include "core/PopulationNode.hpp"
#include "core/Individual.hpp"
#include "core/MutationOperation.hpp"
#include "core/LibraryNode.hpp"
#include "core/SelectionStrategy.hpp"
#include "core/PropertiesList.hpp"
#include "core/Property.hpp"
#include "core/FitnessPropagator.hpp"
#include "crossovers/CutAndSpliceCrossover.hpp"
#include "crossovers/NPointCrossover.hpp"
#include "crossovers/UniformCrossover.hpp"
#include "endconditions/FitnessMatchEnd.hpp"
#include "endconditions/MaxFitnessConvergenceEnd.hpp"
#include "systems/ESGeneration.hpp"
#include "systems/GAGeneration.hpp"
#include "systems/ReplacingGAGeneration.hpp"
#include "systems/SSGAGeneration.hpp"
#include "systems/niching/Crowding.hpp"
#include "mutations/BoundaryMutation.hpp"
#include "mutations/UniformMutation.hpp"
#include "selections/TournamentSelection.hpp"
#include "propagators/NonPropagator.hpp"
#include "propagators/DownPropagator.hpp"
#include "propagators/ApportioningPropagator.hpp"
#include "propagators/apportioning/AveragingPropagator.hpp"
#include "propagators/apportioning/SummingPropagator.hpp"
#include "propagators/apportioning/WeightedAveragePropagator.hpp"
#pragma once

// Legacy
typedef PopulationNode HierarchicalGenePool;
typedef GeneNode GenePool;
typedef EvolutionarySystem GenerationModel;
