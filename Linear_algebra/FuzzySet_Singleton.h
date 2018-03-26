#ifndef FUZZYSET_SINGLETON
#define FUZZYSET_SINGLETON

#include "FuzzySet.h"

class FuzzySet_Singleton : public FuzzySet
{
private:

	//the values that define the shape of this FLV
	double   m_dMidPoint;
	double   m_dLeftOffset;
	double   m_dRightOffset;

public:

	FuzzySet_Singleton(double       mid,
		double       lft,
		double       rgt) :FuzzySet(mid),
		m_dMidPoint(mid),
		m_dLeftOffset(lft),
		m_dRightOffset(rgt)
	{}

	//this method calculates the degree of membership for a particular value
	double     CalculateDOM(double val)const;
};

#endif