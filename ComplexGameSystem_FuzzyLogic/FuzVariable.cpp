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
