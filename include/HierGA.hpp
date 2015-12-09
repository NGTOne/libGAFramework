#include "core/CrossoverOperation.hpp"
#include "core/EndCondition.hpp"
#include "core/FitnessFunction.hpp"
#include "core/ToStringFunction.hpp"
#include "core/GenePool.hpp"
#include "core/GenerationModel.hpp"
#include "core/Genome.hpp"
#include "core/HierarchicalGenePool.hpp"
#include "core/Individual.hpp"
#include "core/MutationOperation.hpp"
#include "core/NonHierarchicalGenePool.hpp"
#include "core/SelectionStrategy.hpp"
#include "core/PropertiesList.hpp"
#include "core/Property.hpp"
#include "core/FitnessPropagator.hpp"
#include "crossovers/CutAndSpliceCrossover.hpp"
#include "crossovers/NPointCrossover.hpp"
#include "crossovers/UniformCrossover.hpp"
#include "endconditions/FitnessMatchEnd.hpp"
#include "endconditions/MaxFitnessConvergenceEnd.hpp"
#include "generations/ESGeneration.hpp"
#include "generations/GAGeneration.hpp"
#include "generations/ReplacingGAGeneration.hpp"
#include "generations/SSGAGeneration.hpp"
#include "generations/niching/Crowding.hpp"
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
