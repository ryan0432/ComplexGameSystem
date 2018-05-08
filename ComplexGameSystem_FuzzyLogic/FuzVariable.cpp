#include "FuzVariable.h"
#include "FuzzyModule.h"
#include "FuzSet_Base.h"

FuzVariable::~FuzVariable()
{
	for (auto i : m_MemberSets)
	{
		delete i.second;
	}
}

void FuzVariable::AdjustRangeToFit(float minBound, float maxBound)
{
	if (m_dMinRange < minBound)
	{
		m_dMinRange = minBound;
	}

	if (m_dMaxRange > maxBound)
	{
		m_dMaxRange = maxBound;
	}
}
