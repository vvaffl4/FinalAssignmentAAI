#ifndef FUZZY_OPERATORS
#define FUZZY_OPERATORS

#include <vector>
#include <assert.h>
#include "FuzzyTerm.h"

class FzAND : public FuzzyTerm
{
private:
	std::vector<FuzzyTerm*> m_Terms;

	FzAND& operator=(const FzAND&);

public:
	~FzAND();

	FzAND(const FzAND& fa);

	FzAND(FuzzyTerm& op1, FuzzyTerm& op2);
	FzAND(FuzzyTerm& op1, FuzzyTerm& op2, FuzzyTerm& op3);
	FzAND(FuzzyTerm& op1, FuzzyTerm& op2, FuzzyTerm& op3, FuzzyTerm& op4);


	FuzzyTerm* Clone()const { return new FzAND(*this); }

	double GetDOM()const;
	void  ClearDOM();
	void  ORWithDOM(double val);
};

class FzOR : public FuzzyTerm
{
private:

	//an instance of this class may AND together up to 4 terms
	std::vector<FuzzyTerm*> m_Terms;

	//no assignment op necessary
	FzOR& operator=(const FzOR&);

public:

	~FzOR();

	//copy ctor
	FzOR(const FzOR& fa);

	//ctors accepting fuzzy terms.
	FzOR(FuzzyTerm& op1, FuzzyTerm& op2);
	FzOR(FuzzyTerm& op1, FuzzyTerm& op2, FuzzyTerm& op3);
	FzOR(FuzzyTerm& op1, FuzzyTerm& op2, FuzzyTerm& op3, FuzzyTerm& op4);

	//virtual ctor
	FuzzyTerm* Clone()const { return new FzOR(*this); }

	double GetDOM()const;

	//unused
	void ClearDOM() { assert(0 && "<FzOR::ClearDOM>: invalid context"); }
	void ORWithDOM(double val) { assert(0 && "<FzOR::ORwithDOM>: invalid context"); }
};

#endif