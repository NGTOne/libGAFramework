#include <string>
#include <vector>
#include <random>
#include <boost/any.hpp>
#pragma once

class Locus {
	private:

	protected:
	std::vector<boost::any> population;
	std::mt19937 generator;
	unsigned seed;

	Locus();
	Locus(std::vector<boost::any> population);
	void init(unsigned seed);
	void setPopulation(std::vector<boost::any> population);

	public:
	~Locus();

	virtual int randomIndex();
	virtual int topIndex();
	virtual bool outOfRange(unsigned int i);
	virtual bool isConstructive();
	virtual std::string toString()=0;
	virtual std::string flatten(int index)=0;
	boost::any getIndex(int index);
};

