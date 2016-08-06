#ifndef CORE_GENES_Gene
#define CORE_GENES_Gene

#include "../Locus.hpp"
#include <boost/any.hpp>
#include "../utils/templates.hpp"

class Locus;

class Gene {
	private:

	protected:
	Locus * target;
	double index;

	bool valueOutOfRange(double newIndex);
	double getIndex();
	Locus * getTarget();

	Gene(Locus * target);
	Gene(Locus * target, double index);
	Gene(Gene * other);

	virtual void add(double addend)=0;
	virtual void set(double value)=0;

	public:
	template <typename T>
	T getValue();

	template<typename T, typename = EnableIf<std::is_arithmetic<T>>>
	void addToIndex(T addend);

	template<typename T, typename = EnableIf<std::is_arithmetic<T>>>
	void setIndex(T value);
};

template <typename T>
T Gene::getValue() {
	return boost::any_cast<T>(this->target->getIndex(this));
}

template<typename T, class>
void Gene::addToIndex(T addend) {
	this->add((double)addend);
}

template<typename T, class>
void Gene::setIndex(T value) {
	this->set((double)value);
}

#endif