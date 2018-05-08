#pragma once
#include "FuzTerm.h"
#include "assert.h"
#include <vector>
#include <initializer_list>

class FuzAND : public FuzTerm
{
private:
	std::vector<FuzTerm*> m_Terms;

	//Copy constructor
	FuzAND(const FuzAND& OriginalFuzAnd);

public:
	~FuzAND();
	//Prevent assignment
	FuzAND & operator=(const FuzAND&) = delete;

	//Constructors taking in Fuzzy Terms
	FuzAND(FuzTerm& term01, FuzTerm& term02);
	FuzAND(FuzTerm& term01, FuzTerm& term02, FuzTerm& term03);
	FuzAND(FuzTerm& term01, FuzTerm& term02, FuzTerm& term03, FuzTerm& term04);

	//ANDing is to get the [Smallest] DOM in all DOMs in current term array
	float GetDOM() const;
	void ClearDOM();
	void ORwithDOM(float var);

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
	FuzOR & operator=(const FuzOR&) = delete;

	//Constructors taking in Fuzzy Terms
	FuzOR(FuzTerm& term01, FuzTerm& term02);
	FuzOR(FuzTerm& term01, FuzTerm& term02, FuzTerm& term03);
	FuzOR(FuzTerm& term01, FuzTerm& term02, FuzTerm& term03, FuzTerm& term04);

	//ORing is to get the [Biggest] DOM in all DOMs in current term array
	float GetDOM() const;

	FuzTerm* Clone() const { return new FuzOR(*this); }

	//Unused functions.
	//For ORing, no need to rewrite DOMs, only need to find the higher DOM
	//and returned it for processing.
	//However, a pure virtual class's functions should be all inherited.
	//Assert unused functions to stop clients using them.
	void ClearDOM() { assert(0 && "ClearDOM() is a invalid function for ORing"); }
	void ORwithDOM(float var) { assert(0 && "ORwithDOM() is a invalid function for ORing"); }
};

