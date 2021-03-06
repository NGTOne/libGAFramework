#include "objectives/noisy/fitness-noise/GaussianFitnessNoiseSource.hpp"
#include "core/utils/HierRNG.hpp"

GaussianFitnessNoiseSource::GaussianFitnessNoiseSource(
	double stdDev
) : FitnessNoiseSource() {
	this->init(0, stdDev);
}

GaussianFitnessNoiseSource::GaussianFitnessNoiseSource(
	double mean,
	double stdDev
) : FitnessNoiseSource() {
	this->init(mean, stdDev);
}

void GaussianFitnessNoiseSource::init(double mean, double stdDev) {
	this->mean = mean;
	this->stdDev = stdDev;
}

Fitness GaussianFitnessNoiseSource::addNoise(Fitness cleanFitness) {
	return this->noisify(cleanFitness, [this](double component) -> double {
		return component + HierRNG::gaussian(this->mean, this->stdDev);
	});
}
