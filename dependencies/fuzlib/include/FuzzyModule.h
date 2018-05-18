#ifndef FUZZY_MODULE_H
#define FUZZY_MODULE_H
#pragma once
//-----------------------------------------------------------------------------//
//																 			   //
//	Name: FuzzyModule.h												 		   //
//																 			   //
//	Desc: A collection of Fuzzy Variables and the Rules that operates them.	   //
//		  It is the centre operating system that operates Fuzzy Logic system.  //
//																 			   //
//-----------------------------------------------------------------------------//

#include <map>
#include <vector>
#include <iosfwd>
#include <string>

#include "FuzSet_Base.h"
#include "FuzVariable.h"
#include "FuzRule.h"
#include "FuzProxySet.h"
#include "FuzOperators.h"

enum CentroidAccuracy
{
	LOW_5 = 5,
	MID_10 = 10,
	HIGH_15 = 15,
	EXTREME_20 = 20
};

class FuzzyModule
{
public:
	//Create a new "empty" fuzzy linguistic variable and returns
	//a reference to it.
	FuzVariable& CreateFLV(const std::string& VarName);

	//Add a Fuzzy Rule to the module
	void AddFuzRule(FuzTerm& antecedent, FuzTerm& consequence);

	//Fuzzify a crisp val by the FLV called
	void Fuzzify(const std::string& NameOfFLV, float val);

	//Defuzzify a Fuzzy Variable and return a crisp value with MaxAV method
	float DefuzzifyMaxAV(const std::string& NameOfFLV);

	//Defuzzify a Fuzzy Variable and return a crisp value with MaxAV method
	float DeFuzzifyCentroid(const std::string& NameOfFLV, CentroidAccuracy accuracy);

	//Print the DOMs of all the variables in the module to an output stream
	std::ostream& PrintAllDOMs(std::ostream& os);

	~FuzzyModule();
	
private:
	//Define map type to class
	typedef std::map<std::string, FuzVariable*> FLVMap;
	//Use shared pointers instead of traditional pointers
	//typedef std::map< std::string, std::shared_ptr<FuzVariable> > FLVMap;

	//Declare a fuzzy linquistic varieble map to store all FLVs
	FLVMap m_FuzVars;

	//Declare a dynamic array (vector) to store all Fuzzy Rules
	std::vector<FuzRule*> m_FuzRules;

	//Set confidences in each consquests to 0. Will be used by Defuzzify()
	void SetConfsOfConsqToZero();
};

#endif
