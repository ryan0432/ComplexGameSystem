#include "FuzVariable.h"
#include "FuzzyModule.h"
#include "FuzOperators.h"
#include "FuzSet_Base.h"
#include "FuzSet_Triangle.h"
#include "FuzSet_LeftShoulder.h"
#include "FuzSet_RightShoulder.h"
#include "FuzSet_Singleton.h"
#include "FuzProxySet.h"
#include "assert.h"

FuzVariable::~FuzVariable()
{
	for (auto i : m_MemberSets)
	{
		delete i.second;
	}
}

void FuzVariable::AdjustRangeToFit(float minBound, float maxBound)
{
	if (minBound < m_dMinRange)
	{
		m_dMinRange = minBound;
	}

	if (maxBound > m_dMaxRange)
	{
		m_dMaxRange = maxBound;
	}
}

FuzProxySet FuzVariable::AddLeftShoulderSet(std::string name, float minBound, float peak, float maxBound)
{
	m_MemberSets[name] = new FuzSet_LeftShoulder(minBound, peak, maxBound);
	AdjustRangeToFit(minBound, maxBound);
	return FuzProxySet(*m_MemberSets[name]);
}

FuzProxySet FuzVariable::AddTriangleSet(std::string name, float minBound, float peak, float maxBound)
{
	m_MemberSets[name] = new FuzSet_Triangle(minBound, peak, maxBound);
	AdjustRangeToFit(minBound, maxBound);
	return FuzProxySet(*m_MemberSets[name]);
}

FuzProxySet FuzVariable::AddRightShoulderSet(std::string name, float minBound, float peak, float maxBound)
{
	m_MemberSets[name] = new FuzSet_RightShoulder(minBound, peak, maxBound);
	AdjustRangeToFit(minBound, maxBound);
	return FuzProxySet(*m_MemberSets[name]);
}

FuzProxySet FuzVariable::AddSingletonSet(std::string name, float minBound, float peak, float maxBound)
{
	m_MemberSets[name] = new FuzSet_Singleton(minBound, peak, maxBound);
	AdjustRangeToFit(minBound, maxBound);
	return FuzProxySet(*m_MemberSets[name]);
}
