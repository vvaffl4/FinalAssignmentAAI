#ifndef FUZZY_SET
#define FUZZY_SET

#include <cmath>
#include <assert.h>

class FuzzySet
{
protected:
	//holds degree of membership
	double m_dDom;

	//max of the set's membership function (maxAv maximum)
	double m_dRepresentativeValue;

public:
	FuzzySet(double RepVal) :m_dDom(0.0), m_dRepresentativeValue(RepVal) {}

	//returns DOM for this set of the given value
	virtual double CalculateDOM(double val)const = 0;

	//idk what this does exactly
	void ORWithDOM(double val) { if (val > m_dDom) m_dDom = val; }

	//accessor methods
	double GetRepresentativeVal()const { return m_dRepresentativeValue; }
	void ClearDOM() { m_dDom = 0.0; }
	double GetDOM()const { return m_dDom; }
	void SetDOM(double val) {
		assert((val <= 1) && (val >= 0) && "<FuzzySet::SetDOM>: invalid value");
		m_dDom = val;
	}
};

#endif