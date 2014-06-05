#include "core/CrossoverOperation.hpp"
#include "core/EndCondition.hpp"
#include "core/FitnessFunction.hpp"
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
#include "crossovers/CutAndSpliceCrossover.hpp"
#include "crossovers/NPointCrossover.hpp"
#include "crossovers/UniformCrossover.hpp"
#include "endconditions/FitnessMatchEnd.hpp"
#include "generations/ESGeneration.hpp"
#include "generations/GAGeneration.hpp"
#include "generations/SSGAGeneration.hpp"
#include "mutations/BoundaryMutation.hpp"
#include "mutations/UniformMutation.hpp"
#include "selections/TournamentSelection.hpp"
#pragma once