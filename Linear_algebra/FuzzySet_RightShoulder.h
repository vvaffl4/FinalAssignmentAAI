#ifndef FUZZYSET_RIGHTSHOULDER
#define FUZZYSET_RIGHTSHOULDER

#include "FuzzySet.h"

class FuzzySet_RightShoulder : public FuzzySet
{
private:
	double m_dPeakPoint;
	double m_dLeftOffset;
	double m_dRightOffset;

public:
	FuzzySet_RightShoulder(double peak, double left, double right) :
		FuzzySet(((peak + right) + peak) / 2),
		m_dPeakPoint(peak),
		m_dLeftOffset(left),
		m_dRightOffset(right) {}

	double CalculateDOM(double val) const;
};

#endif