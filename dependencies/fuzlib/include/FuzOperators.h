#pragma once
#ifndef FUZ_OPERATORS_H
#define FUZ_OPERATORS_H
//--------------------------------------------------------------------------//
//																 			//
//	Name: FuzOperators.h												 	//
//																 			//
//	Desc: A collection of Fuzzy Terms by [AND] and [OR] operators.			//
//		  These classes are used to create a Fuzzy Rule Base.				//
//		  Ex: IF [Antecedent_A] AND [Antecedent_B]...THAN [Consequence_A]	//
//																 			//
//--------------------------------------------------------------------------//

#include "FuzTerm.h"
#include "assert.h"
#include <vector>

class FuzAND : public FuzTerm
{
private:
	std::vector<FuzTerm*> m_Terms;

	//Copy constructor
	FuzAND(const FuzAND& OriginalFuzAnd);

public:
	~FuzAND();
	//Prevent assignment
	FuzAND& operator=(const FuzAND&) = delete;

	//Constructors taking in Fuzzy Terms
	FuzAND(FuzTerm& term01, FuzTerm& term02);
	FuzAND(FuzTerm& term01, FuzTerm& term02, FuzTerm& term03);
	FuzAND(FuzTerm& term01, FuzTerm& term02, FuzTerm& term03, FuzTerm& term04);

	//ANDing is to get the [Smallest] DOM in all DOMs in current term array
	float GetDOM() const;

	//Retrieves the degree of membership of the term
	void ClearDOM();

	//Updates DOM of a consequent when a fuzzy rule gets launched
	void ORwithDOM(float var);

	//All terms have to implement a virtual constructor
	//When making calculation, cloning can prevent changing the orginal data
	FuzTerm* Clone() const { return new FuzAND(*this); }
};

class FuzOR : public FuzTerm
{
private:
	std::vector<FuzTerm*> m_Terms;

	//Copy constructor
	FuzOR(const FuzOR& OriginalFuzOR);

public:
	~FuzOR();
	//Prevent assignment
	FuzOR& operator=(const FuzOR&) = delete;

	//Constructors taking in Fuzzy Terms
	FuzOR(FuzTerm& term01, FuzTerm& term02);
	FuzOR(FuzTerm& term01, FuzTerm& term02, FuzTerm& term03);
	FuzOR(FuzTerm& term01, FuzTerm& term02, FuzTerm& term03, FuzTerm& term04);

	//ORing is to get the [Biggest] DOM in all DOMs in current term array
	float GetDOM() const;

	//All terms have to implement a virtual constructor
	//When making calculation, cloning can prevent changing the orginal data
	FuzTerm* Clone() const { return new FuzOR(*this); }

	//Unused functions.
	//For ORing, no need to rewrite DOMs, only need to find the higher DOM
	//and returned it for processing.
	//However, a pure virtual class's functions should be all inherited.
	//Assert unused functions to stop clients using them.
	void ClearDOM() { assert(0 && "FuzOR::ClearDOM() is a invalid function for ORing"); }
	void ORwithDOM(float var) { assert(0 && "FuzOR::ORwithDOM() is a invalid function for ORing"); }
};

#endif

