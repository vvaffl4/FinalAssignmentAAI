#include "stdafx.h"
#include "FuzzyModule.h"
#include "FuzzyTerm.h"
#include "FuzzyRule.h"
#include "FuzzyVariable.h"
#include <assert.h>


FuzzyModule::~FuzzyModule()
{
	VarMap::iterator curVar = m_Variables.begin();
	for (curVar; curVar != m_Variables.end(); ++curVar)
	{
		delete curVar->second;
	}

	std::vector<FuzzyRule*>::iterator curRule = m_Rules.begin();
	for (curRule; curRule != m_Rules.end(); ++curRule)
	{
		delete *curRule;
	}
}

void FuzzyModule::AddRule(FuzzyTerm& antecedent, FuzzyTerm& consequence) {
	m_Rules.push_back(new FuzzyRule(antecedent, consequence));
}

FuzzyVariable& FuzzyModule::CreateFLV(const std::string& VarName)
{
	m_Variables[VarName] = new FuzzyVariable();

	return *m_Variables[VarName];
}

