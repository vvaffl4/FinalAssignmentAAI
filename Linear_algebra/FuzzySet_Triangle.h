#ifndef FUZZYSET_TRIANGLE
#define FUZZYSET_TRIANGLE

#include "FuzzySet.h"

class FuzzySet_Triangle : public FuzzySet
{
private:
	//these values define the shape of the triangle
	double m_dPeakPoint;
	double m_dLeftOffset;
	double m_dRightOffset;

public:
	FuzzySet_Triangle(double mid, double lft, double rgt) :
		FuzzySet(mid), m_dPeakPoint(mid), m_dLeftOffset(lft), m_dRightOffset(rgt) {}

	//calculate DOM
	double CalculateDOM(double val)const;
};

#endif