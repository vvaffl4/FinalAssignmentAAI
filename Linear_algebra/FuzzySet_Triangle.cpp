#include "FuzzySet_Triangle.h"
#include "utils.h"


//FuzzySet_Triangle::FuzzySet_Triangle()
//{
//}
//
//
//FuzzySet_Triangle::~FuzzySet_Triangle()
//{
//}

double FuzzySet_Triangle::CalculateDOM(double val)const {
	//test whether offsets are 0
	if ((isEqual(m_dRightOffset, 0.0) && (isEqual(m_dPeakPoint, val))) ||
		(isEqual(m_dLeftOffset, 0.0) && (isEqual(m_dPeakPoint, val)))) {
		return 1.0;
	}

	//find DOM if left of center
	if ((val <= m_dPeakPoint) && (val >= m_dPeakPoint - m_dLeftOffset)) {
		double grad = 1.0 / m_dLeftOffset;

		return grad * (val - (m_dPeakPoint - m_dLeftOffset));
	}

	//find DOM if right of center
	else if ((val > m_dPeakPoint) && (val < (m_dPeakPoint + m_dRightOffset))) {
		double grad = 1.0 / -m_dRightOffset;

		return grad * (val - m_dPeakPoint) + 1.0;
	}

	//out of range, return 0
	else {
		return 0;
	}
}