#ifndef FUZZY_RULE
#define FUZZY_RULE

#include "FuzzyTerm.h"

class FuzzyRule
{
private:
	const FuzzyTerm* m_pAntecedent;
	FuzzyTerm* m_pConsequence;

	FuzzyRule(const FuzzyRule&);
	FuzzyRule& operator=(const FuzzyRule&);

public:
	FuzzyRule(FuzzyTerm& ant, FuzzyTerm& con) :
		m_pAntecedent(ant.Clone()),
		m_pConsequence(con.Clone()) {}

	~FuzzyRule() { delete m_pAntecedent; delete m_pConsequence; }

	void SetConfidenceOfConsequentToZero() { m_pConsequence->ClearDOM(); }

	void Calculate() {
		m_pConsequence->ORWithDOM(m_pAntecedent->GetDOM());
	}
};

#endif