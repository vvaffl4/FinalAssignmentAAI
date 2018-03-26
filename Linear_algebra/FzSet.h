#ifndef FZSET
#define FZSET

#include "FuzzyTerm.h"
#include "FuzzySet.h"

class FzAND;

class FzSet : public FuzzyTerm
{

private:

	//a reference to the fuzzy set this proxy represents
	FuzzySet &m_Set;

public:

	FzSet(FuzzySet& fs) :m_Set(fs) {}

	FuzzyTerm* Clone()const { return new FzSet(*this); }
	double     GetDOM()const { return m_Set.GetDOM(); }
	void       ClearDOM() { m_Set.ClearDOM(); }
	void       ORWithDOM(double val) { m_Set.ORWithDOM(val); }
};

#endif