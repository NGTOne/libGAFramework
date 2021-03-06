#include "core/meta/MetaPopulationToString.hpp"
#include "core/meta/BlanketResolver.hpp"
#include "core/utils/HierGC.hpp"
#include "core/eval/HierarchicalToString.hpp"

MetaPopulationToString::MetaPopulationToString(
	ToStringFunction * flattenedToString
) {
	this->flattenedToString = flattenedToString;
}

void MetaPopulationToString::registerInternalObjects() {
	ToStringFunction::registerInternalObjects();
	HierGC::registerObject(this->flattenedToString);
}

std::string MetaPopulationToString::toString(Genome* genome) {
	if (
		this->flattenedToString->isHierarchical() &&
			((HierarchicalToString*)this->flattenedToString)
				->getPrintMode()
			!= HierarchicalToString::flatten
	) {
		return this->flattenedToString->toString(genome);
	} else {
		Genome resolved = BlanketResolver::resolveBlanket(genome);
		return this->flattenedToString->toString(&resolved);
	}
}

bool MetaPopulationToString::isNested() {
	return true;
}

std::vector<ToStringFunction*> MetaPopulationToString::getNested() {
	std::vector<ToStringFunction*> inner;
	if (this->flattenedToString->isNested())
		inner = ((MetaPopulationToString*)this->flattenedToString)
			->getNested();
	inner.push_back(this->flattenedToString);
	return inner;
}
