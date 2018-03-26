#ifndef FUZZY_TERM
#define FUZZY_TERM


class FuzzyTerm
{
public:
	virtual ~FuzzyTerm() {}

	virtual FuzzyTerm* Clone()const = 0;

	virtual double GetDOM()const = 0;

	virtual void ClearDOM() = 0;

	virtual void ORWithDOM(double val) = 0;
};

#endif