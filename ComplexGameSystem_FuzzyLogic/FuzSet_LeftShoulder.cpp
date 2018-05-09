#include "FuzSet_LeftShoulder.h"

float FuzSet_LeftShoulder::CalculateDOM(float val) const
{
	//Assert, make sure clients not to input silly values
	assert(m_dRight > m_dPeak && "FuzSet_LeftShoulder::CalculateDOM -> The [Right Value] should always greater than [Mid Value]");
	assert(m_dLeft < m_dPeak && "FuzSet_LeftShoulder::CalculateDOM -> The [Left Value] should always lesser than [Mid Value]");

	//If input value equals peak value
	if (val <= m_dPeak && val >= m_dLeft)
	{
		//DOM will always be 1
		return 1.0f;
	}
	//If input value falls on the ramp
	else if (val > m_dPeak && val < m_dRight)
	{
		//DOM will be same ration to PeakDOM / PeakCrisp
		float DOM = (m_dRight - val) / (m_dRight - m_dPeak);
		return DOM;
	}
	else //If input value is larger than right or smaller than right
	{
		//DOM will always be 0
		return 0.0f;
	}
}
