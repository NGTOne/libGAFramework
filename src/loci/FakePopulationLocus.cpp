#include "loci/FakePopulationLocus.hpp"
#include "core/FakeGenome.hpp"
#include <sstream>

FakePopulationLocus::FakePopulationLocus(
	Genome * target,
	PopulationLocus * original,
	bool fakeGenome
) : PopulationLocus(original->getNode()) {
	this->target = (fakeGenome) ? new FakeGenome(target) : target;
	this->fakeGenome = fakeGenome;
}

FakePopulationLocus::FakePopulationLocus(
	Genome target,
	PopulationLocus * original
) : PopulationLocus(original->getNode()) {
	this->target = new FakeGenome(&target);
	this->fakeGenome = true;
}

FakePopulationLocus::FakePopulationLocus(
	FakePopulationLocus * target
) : PopulationLocus(target->getNode()) {
	this->fakeGenome = target->genomeIsFake();
	this->target = (this->fakeGenome) ?
		new FakeGenome(target->getIndex(0)) : target->getIndex(0);
}

FakePopulationLocus::~FakePopulationLocus() {
	if (this->fakeGenome) delete(this->target);
}

Genome * FakePopulationLocus::getIndex(unsigned int index) {
	return this->target;
}

unsigned int FakePopulationLocus::randomIndex() {
	return 0;
}

unsigned int FakePopulationLocus::topIndex() {
	return 0;
}

bool FakePopulationLocus::outOfRange(unsigned int i) {
	return false;
}

bool FakePopulationLocus::isFake() {
	return true;
}

bool FakePopulationLocus::genomeIsFake() {
	return this->fakeGenome;
}

std::string FakePopulationLocus::toString() {
	stringstream ss;
	ss << "Fake population locus with genome: "
		<< this->target->flatten()
		<< ".\n";

	return ss.str();
}

std::string FakePopulationLocus::flatten(unsigned int index) {
	return this->target->flatten();
}
