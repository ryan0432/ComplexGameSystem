#include "FuzSet_Singleton.h"

float FuzSet_Singleton::CalculateDOM(float val) const
{
	if (val >= m_dLeft && val <= m_dRight)
	{
		return 1.0f;
	}
	else
	{
		return 0.0f;
	}
}
