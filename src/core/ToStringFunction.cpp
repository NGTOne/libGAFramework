#include "core/ToStringFunction.hpp"

ToStringFunction::~ToStringFunction() {}

bool ToStringFunction::isNested() {
	return false;
}

void ToStringFunction::registerInternalObjects(
	NodeGarbageCollector & collector
) {}
