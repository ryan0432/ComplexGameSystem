#pragma once
#include "FuzTerm.h"

class FuzTerm;

class FuzRule
{
public:
	FuzRule(FuzTerm& ant, FuzTerm& con) :
		m_pAntecedent(ant.Clone()), m_pConsequence(con.Clone()) {};

	~FuzRule() { delete m_pAntecedent; delete m_pConsequence; }

	void SetConfidenceOfConsequentToZero() { m_pConsequence->ClearDOM(); }
	void Calculate() { m_pConsequence->ORwithDOM(m_pAntecedent->GetDOM()); }

	//Disallow clients to cpoy Fuzzy Rules
	FuzRule(const FuzRule&) = delete;
	FuzRule& operator=(const FuzRule&) = delete;

private:
	const FuzTerm* m_pAntecedent;
	FuzTerm* m_pConsequence;
};

