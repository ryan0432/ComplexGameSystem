#include "FuzSet_Singleton.h"

float FuzSet_Singleton::CalculateDOM(float val) const
{
	assert(m_dRight > m_dPeak && "FuzSet_Singleton::CalculateDOM -> The [Right Value] should always greater than [Mid Value]");
	assert(m_dLeft < m_dPeak && "FuzSet_Singleton::CalculateDOM -> The [Left Value] should always lesser than [Mid Value]");

	if (val >= m_dLeft && val <= m_dRight)
	{
		return 1.0f;
	}
	else
	{
		return 0.0f;
	}
}
