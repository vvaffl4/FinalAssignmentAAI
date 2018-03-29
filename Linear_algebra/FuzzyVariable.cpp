#include "FuzzyVariable.h"
#include <assert.h>
#include "FuzzySet_Triangle.h"
#include "FuzzySet_LeftShoulder.h"
#include "FuzzySet_RightShoulder.h"
#include "FuzzySet_Singleton.h"
#include "utils.h"


//FuzzyVariable::FuzzyVariable()
//{
//}
//
//
//FuzzyVariable::~FuzzyVariable()
//{
//}


FuzzyVariable::~FuzzyVariable() {
	MemberSets::iterator it;
	for (it = m_MemberSets.begin(); it != m_MemberSets.end(); ++it) {
		delete it->second;
	}
}

//fuzzify
//takes a crisp value and calculates its DOM for each set in the variable
void FuzzyVariable::Fuzzify(double val) {
	//make sure the value is within the bounds
	assert((val >= m_dMinRange) && (val <= m_dMaxRange) && 
		"<FuzzyVariable::Fuzzify>: value out of range");

	//for each set, calculate the DOM
	MemberSets::const_iterator curSet;
	for (curSet = m_MemberSets.begin(); curSet != m_MemberSets.end(); ++curSet) {
		curSet->second->SetDOM(curSet->second->CalculateDOM(val));
	}
}

//DeFuzzifyMaxAv
//averages maxima
//output = sum(maxima * DOM) / sum(DOMs)
double FuzzyVariable::DeFuzzifyMaxAv()const {
	double bot = 0.0;
	double top = 0.0;

	MemberSets::const_iterator curSet;
	for (curSet = m_MemberSets.begin(); curSet != m_MemberSets.end(); ++curSet) {
		bot += curSet->second->GetDOM();

		top += curSet->second->GetRepresentativeVal() * curSet->second->GetDOM();
	}

	//can't divide by 0
	if (isEqual(0, bot)) return 0.0;

	return top / bot;
}

//DeFuzzifyCentroid
//to be implemented
double FuzzyVariable::DeFuzzifyCentroid(int NumSamples)const {
	return 0;
}


#pragma region Set adding methods

FzSet FuzzyVariable::AddTriangularSet(std::string name, double minBound, double peak, double maxBound) {
	m_MemberSets[name] = new FuzzySet_Triangle(peak, peak-minBound, maxBound - peak);

	AdjustRangeToFit(minBound, maxBound);

	return FzSet(*m_MemberSets[name]);
}

FzSet FuzzyVariable::AddLeftShoulderSet(std::string name, double minBound, double peak, double maxBound) {
	m_MemberSets[name] = new FuzzySet_LeftShoulder(peak, peak - minBound, maxBound - peak);

	AdjustRangeToFit(minBound, maxBound);

	return FzSet(*m_MemberSets[name]);
}

FzSet FuzzyVariable::AddRightShoulderSet(std::string name, double minBound, double peak, double maxBound) {
	m_MemberSets[name] = new FuzzySet_RightShoulder(peak, peak - minBound, maxBound - peak);

	AdjustRangeToFit(minBound, maxBound);

	return FzSet(*m_MemberSets[name]);
}

FzSet FuzzyVariable::AddSingletonSet(std::string name, double minBound, double peak, double maxBound) {
	m_MemberSets[name] = new FuzzySet_Singleton(peak, peak - minBound, maxBound - peak);

	AdjustRangeToFit(minBound, maxBound);

	return FzSet(*m_MemberSets[name]);
}

#pragma endregion

//AdjustRangeToFit
void FuzzyVariable::AdjustRangeToFit(double minBound, double maxBound) {
	if (minBound < m_dMinRange) m_dMinRange = minBound;
	if (maxBound > m_dMaxRange) m_dMaxRange = maxBound;
}