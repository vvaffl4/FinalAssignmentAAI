#ifndef FUZZY_MODULE
#define FUZZY_MODULE

#include <map>
#include <vector>
#include "FuzzyRule.h"
#include "FuzzyVariable.h";

class FuzzyModule
{
private:
	typedef std::map<std::string, FuzzyVariable*> VarMap;

public:
	enum DeFuzzifyType { max_av, centroid };

	enum {NumSamplesToUseForCentroid = 15};

private:
	//a map of asll fuzzy variables
	VarMap m_Variables;

	//a vector for all the rules
	std::vector<FuzzyRule*> m_Rules;

	inline void SetConfidencesOfConsequentsToZero();

public:

	~FuzzyModule();
	
	//create a new 'empty' fuzzy variable
	FuzzyVariable& CreateFLV(const std::string& VarName);

	//add rule
	void AddRule(FuzzyTerm& antecedent, FuzzyTerm& consequent);

	//call fuzzify of named FLV
	inline void Fuzzify(const std::string& NameOfFLV, double val);

	//return defuzzified, crisp value
	inline double DeFuzzify(const std::string& key, DeFuzzifyType method);
};

inline void FuzzyModule::Fuzzify(const std::string& NameOfFLV, double val)
{
	//first make sure the key exists
	assert((m_Variables.find(NameOfFLV) != m_Variables.end()) &&
		"<FuzzyModule::Fuzzify>:key not found");

	m_Variables[NameOfFLV]->Fuzzify(val);
}

inline double FuzzyModule::DeFuzzify(const std::string& NameOfFLV, DeFuzzifyType method) {
	//make sure named FLV exists
	assert((m_Variables.find(NameOfFLV) != m_Variables.end()) &&
		"<FuzzyModule::DefuzzifyMaxAv>:key not found");

	//clear DOMs
	SetConfidencesOfConsequentsToZero();

	//process rules
	std::vector<FuzzyRule*>::iterator curRule = m_Rules.begin();
	for (curRule; curRule != m_Rules.end(); ++curRule) {
		(*curRule)->Calculate();
	}

	//now defuzzify
	switch (method) {
	case centroid:
		return m_Variables[NameOfFLV]->DeFuzzifyCentroid(NumSamplesToUseForCentroid);
	case max_av:
		return m_Variables[NameOfFLV]->DeFuzzifyMaxAv();
	}

	return 0;
}

inline void FuzzyModule::SetConfidencesOfConsequentsToZero()
{
	std::vector<FuzzyRule*>::iterator curRule = m_Rules.begin();
	for (curRule; curRule != m_Rules.end(); ++curRule)
	{
		(*curRule)->SetConfidenceOfConsequentToZero();
	}
}

#endif