#include "FuzOperators.h"
#include <limits>

////////////////////////
//------ FuzAND ------//
////////////////////////
FuzAND::FuzAND(const FuzAND& OriginalFuzAnd)
{
	for (auto i : OriginalFuzAnd.m_Terms)
	{
		m_Terms.push_back(i->Clone());
	}
}

FuzAND::~FuzAND()
{
	for (auto i : m_Terms)
	{
		delete i;
	}
	m_Terms.clear();
}

FuzAND::FuzAND(FuzTerm& term01, FuzTerm & term02)
{
	m_Terms.push_back(term01.Clone());
	m_Terms.push_back(term02.Clone());
}

FuzAND::FuzAND(FuzTerm& term01, FuzTerm & term02, FuzTerm & term03)
{
	m_Terms.push_back(term01.Clone());
	m_Terms.push_back(term02.Clone());
	m_Terms.push_back(term03.Clone());
}

FuzAND::FuzAND(FuzTerm& term01, FuzTerm & term02, FuzTerm & term03, FuzTerm & term04)
{
	m_Terms.push_back(term01.Clone());
	m_Terms.push_back(term02.Clone());
	m_Terms.push_back(term03.Clone());
	m_Terms.push_back(term04.Clone());
}

float FuzAND::GetDOM() const
{
	float min = std::numeric_limits<float>::max();

	for (auto i : m_Terms)
	{
		if (i->GetDOM() < min)
		{
			min = i->GetDOM();
		}
	}

	return min;
}

void FuzAND::ClearDOM()
{
	for (auto i : m_Terms)
	{
		i->ClearDOM();
	}
}

void FuzAND::ORwithDOM(float var)
{
	for (auto i : m_Terms)
	{
		if (i->GetDOM() < var)
		{
			i->ORwithDOM(var);
		}
	}
}

///////////////////////
//------ FuzOR ------//
///////////////////////
FuzOR::~FuzOR()
{
	for (auto i : m_Terms)
	{
		delete i;
	}
	m_Terms.clear();
}

FuzOR::FuzOR(const FuzOR & OriginalFuzOR)
{
	for (auto i : OriginalFuzOR.m_Terms)
	{
		m_Terms.push_back(i->Clone());
	}
}

FuzOR::FuzOR(FuzTerm& term01, FuzTerm & term02)
{
	m_Terms.push_back(term01.Clone());
	m_Terms.push_back(term02.Clone());
}

FuzOR::FuzOR(FuzTerm& term01, FuzTerm & term02, FuzTerm & term03)
{
	m_Terms.push_back(term01.Clone());
	m_Terms.push_back(term02.Clone());
	m_Terms.push_back(term03.Clone());
}

FuzOR::FuzOR(FuzTerm& term01, FuzTerm & term02, FuzTerm & term03, FuzTerm & term04)
{
	m_Terms.push_back(term01.Clone());
	m_Terms.push_back(term02.Clone());
	m_Terms.push_back(term03.Clone());
	m_Terms.push_back(term04.Clone());
}

float FuzOR::GetDOM() const
{
	float max = std::numeric_limits<float>::min();

	for (auto i : m_Terms)
	{
		if (i->GetDOM() > max)
		{
			max = i->GetDOM();
		}
	}

	return max;
}
