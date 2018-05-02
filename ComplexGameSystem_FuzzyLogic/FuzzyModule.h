#pragma once
#include <map>
#include <vector>
#include <memory>

class FuzLinguVar;
class FuzRule;
class FuzTerm;

//enum class to choose which type of Defuzz method
//they want to use
enum class DefuzType
{
	MAX_AV,
	CENTROID
};

//enum class for clients to choose how accurate
//they want the Defuzz process to be
enum class CentroidAccuracy
{
	LOW_05 = 5,
	MID_10 = 10,
	HIGH_15 = 15,
	EXTREME_20 = 20
};

class FuzzyModule
{
public:
	//Create a new "empty" fuzzy variable and returns a reference to it.
	FuzLinguVar& CreateFLV(const std::string& VarName);
	//Add a Fuzzy Rule to the module
	void AddFuzRule(FuzTerm& antecedent, FuzTerm& consequence);
	//Fuzzify a crisp val by the FLV called
	inline void Fuzzify(const std::string& NameOfFLV, double val);
	//Defuzzify a Fuzzy Set and return a crisp value
	inline float Defuzzify(const std::string& key, DefuzType method);
	
private:
	//Define map type to class
	typedef std::map< std::string, std::unique_ptr<FuzLinguVar> > FLVMap;
	//Declare a fuzzy linquistic varieble map to store all FLVs
	FLVMap m_FuzLinguVars;

	//Declare a dynamic array (vector) to store all Fuzzy Rules
	std::vector< std::unique_ptr<FuzRule> > m_FuzRules;
	//Set confidences in each consquests to 0. Will be used by Defuzzfy()
	inline void SetConfsOfConsqToZero();
};

