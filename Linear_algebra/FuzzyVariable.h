#ifndef FUZZY_VARIABLE
#define FUZZY_VARIABLE

#include <map>
#include "FuzzySet.h"
#include "FzSet.h"

class FuzzySet;
class FzSet;
class FuzzyModule;

class FuzzyVariable
{
private:
	typedef std::map<std::string, FuzzySet*> MemberSets;

private:
	//disallow copies
	FuzzyVariable(const FuzzyVariable&);
	FuzzyVariable& operator=(const FuzzyVariable&);

private:
	//map of fuzzy sets
	MemberSets m_MemberSets;

	//min and max values
	double m_dMinRange;
	double m_dMaxRange;

	//this method is called whenever a set is added and sets the min & maxrange accordingly
	void AdjustRangeToFit(double min, double max);

	~FuzzyVariable();

	friend class FuzzyModule;

public:
	FuzzyVariable() :m_dMinRange(0.0), m_dMaxRange(0.0) {}

	//methods to add sets
	FzSet AddLeftShoulderSet(std::string name, double minBound, double peak, double maxBound);
	FzSet AddRightShoulderSet(std::string name, double minBound, double peak, double maxBound);
	FzSet AddTriangularSet(std::string name, double minBound, double peak, double maxBound);
	FzSet AddSingletonSet(std::string name, double minBound, double peak, double maxBound);

	//fuzzify value
	void Fuzzify(double val);

	//defuzzify with MaxAv
	double DeFuzzifyMaxAv()const;

	//defuzzify with centroid
	double DeFuzzifyCentroid(int NumSamples) const;
};

#endif