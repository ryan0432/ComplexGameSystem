#pragma once
#include "FuzTerm.h"
#include "FuzSet_Base.h"

class FuzAND;

class FuzProxySet : public FuzTerm
{
public:
	FuzProxySet(FuzSet_Base& fs) : m_Set(fs) {}
	FuzTerm* Clone() const { return new FuzProxySet(*this); }
	float GetDOM()const { return m_Set.GetDOM(); }
	void ClearDOM() { m_Set.ClearDOM(); }
	void ORwithDOM(float val) { m_Set.ORwithDOM(val); }

private:
	FuzSet_Base& m_Set;
};