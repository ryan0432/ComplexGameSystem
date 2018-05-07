#pragma once
#include <map>
#include <vector>

class FuzVariable;
class FuzRule;
class FuzTerm;

//enum class to choose which type of Defuzz method
//they want to use
enum class DefuzType
{
	MAX_AV,
	CENTROID
};

class FuzzyModule
{
public:
	//Create a new "empty" fuzzy linguistic variable and returns
	//a reference to it.
	FuzVariable & CreateFLV(const std::string& VarName);

	//Add a Fuzzy Rule to the module
	void AddFuzRule(FuzTerm& antecedent, FuzTerm& consequence);

	//Fuzzify a crisp val by the FLV called
	inline void Fuzzify(const std::string& NameOfFLV, float val);

	//Defuzzify a Fuzzy Set and return a crisp value
	inline float Defuzzify(const std::string& key, DefuzType method);

	~FuzzyModule();
	
private:
	//Define map type to class
	typedef std::map<std::string, FuzVariable*> FLVMap;

	//Declare a fuzzy linquistic varieble map to store all FLVs
	FLVMap m_FuzVars;

	//Declare a dynamic array (vector) to store all Fuzzy Rules
	std::vector<FuzRule*> m_FuzRules;

	//Set confidences in each consquests to 0. Will be used by Defuzzfy()
	inline void SetConfsOfConsqToZero();
};

