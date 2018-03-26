#include "stdafx.h"
#include "FuzzySet_RightShoulder.h"
#include "utils.h"


//FuzzySet_RightShoulder::FuzzySet_RightShoulder()
//{
//}
//
//
//FuzzySet_RightShoulder::~FuzzySet_RightShoulder()
//{
//}

double FuzzySet_RightShoulder::CalculateDOM(double val)const {
	//check if offset isn't 0
	if (isEqual(0, m_dLeftOffset) && isEqual(val, m_dPeakPoint)) {
		return 1.0;
	}

	//finc DOM if left of center
	if ((val <= m_dPeakPoint) && val >= (m_dPeakPoint - m_dLeftOffset)) {
		double grad = 1.0 / m_dLeftOffset;

		return grad * (val - (m_dPeakPoint - m_dLeftOffset));
	}

	//right of center
	else if (val > m_dPeakPoint) {
		return 1.0;
	}

	//out of range
	else {
		return 0.0;
	}
}