#pragma once
#ifndef FUZ_RULE_H
#define FUZ_RULE_H
//--------------------------------------------------------------------------//
//																 			//
//	Name: FuzRule.h												 			//
//																 			//
//	Desc: A Fuzzy Rule holds CLONES of Fuzzy Terms that describe			//
//		  how the Fuzzy logic should be implemented.			 			//
//		  Ex: IF [Antecedent_A] AND [Antecedent_B]...THAN [Consequence_A]	//
//																 			//
//--------------------------------------------------------------------------//

#include "FuzTerm.h"
#include "FuzOperators.h"
#include "FuzSet_Base.h"

class FuzRule
{
public:
	//FuzRule Constructor, holds an [Antecedent] and a [Consequence]
	//which both are a CLONE of sets of Fuzzy Terms.
	FuzRule(FuzTerm& ant, FuzTerm& con) :
		m_pAntecedent(ant.Clone()), m_pConsequence(con.Clone()) {};

	~FuzRule() { delete m_pAntecedent; delete m_pConsequence; }

	//Sets the Confidence of Consequent DOM to Zero
	void SetConfidenceOfConsequentToZero() { m_pConsequence->ClearDOM(); }

	//This function updates the DOM (the confidence) of the consequent term with
	//the DOM of the antecedent term. 
	void Calculate() { m_pConsequence->ORwithDOM(m_pAntecedent->GetDOM()); }

	//Disallow clients to cpoy Fuzzy Rules
	FuzRule(const FuzRule&) = delete;
	FuzRule& operator=(const FuzRule&) = delete;

private:
	//Antecedent, usually a composite of several Fuzzy Sets and operators
	const FuzTerm* m_pAntecedent;

	//Consequence, usually a single fuzzy set, but can be several ANDed Sets
	FuzTerm* m_pConsequence;
};

#endif

