#include "FuzSet_RightShoulder.h"

float FuzSet_RightShoulder::CalculateDOM(float val) const
{
	//If input value equals peak value
	if (val >= m_dPeak && val <= m_dRight)
	{
		//DOM will always be 1
		return 1.0f;
	}
	//If input value falls on the ramp
	else if (val < m_dPeak && val > m_dLeft)
	{
		//DOM will be same ration to PeakDOM / PeakCrisp 
		float DOM = (val - m_dLeft) / (m_dPeak - m_dLeft);
		return DOM;
	}
	else //If input value is larger than right or smaller than left
	{
		//DOM will always be 0
		return 0.0f;
	}
}

