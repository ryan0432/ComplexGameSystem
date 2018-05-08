#include "FuzzyModule.h"
#include "FuzVariable.h"
#include "FuzRule.h"
#include "FuzTerm.h"
#include "assert.h"
#include <memory>

FuzVariable& FuzzyModule::CreateFLV(const std::string& VarName)
{
	//New a shared pointer in std::map, Method 1
	//m_FuzVars[VarName] = std::make_shared<FuzVariable>(new FuzVariable());
	//Traditional pointer operation, Method2
	m_FuzVars[VarName] = new FuzVariable();
	return *m_FuzVars[VarName];
}

void FuzzyModule::AddFuzRule(FuzTerm& antecedent, FuzTerm& consequence)
{
	//Create a new Fuzzy Rule and push it into the back of the vector array
	m_FuzRules.push_back(new FuzRule(antecedent, consequence));
}

inline void FuzzyModule::Fuzzify(const std::string & NameOfFLV, float val)
{
	//Make sure fuzzy variable that clients expect to defuzzify exists in the map
	assert(m_FuzVars.find(NameOfFLV) != m_FuzVars.end() && "Input Fuzzy Variable doesn't exist");
	
	//Clear the DOMs of all consequents in every Fuzzy Rule
	SetConfsOfConsqToZero();
	
	//Recalculate (updates) all DOMs of the consequents base on the DOM of the antecedent term
	for (auto i : m_FuzRules)
	{
		i->Calculate();
	}
	
	//Call Fuzzify function for each FLV
	m_FuzVars[NameOfFLV]->Fuzzify(val);
}

inline float FuzzyModule::DefuzzifyMaxAV(const std::string& NameOfFLV)
{
	//Make sure fuzzy variable that clients expect to defuzzify exists in the map
	assert(m_FuzVars.find(NameOfFLV) != m_FuzVars.end() && "Input Fuzzy Variable doesn't exist");
	
	//Defuzzify appointed FLV with MaxAV
	m_FuzVars[NameOfFLV]->DeFuzzifyMaxAV();
}

inline float FuzzyModule::DeFuzzifyCentroid(const std::string & NameOfFLV, CentroidAccuracy accuracy)
{
	//Make sure fuzzy variable that clients expect to defuzzify exists in the map
	assert(m_FuzVars.find(NameOfFLV) != m_FuzVars.end() && "Input Fuzzy Variable doesn't exist");
	
	//Defuzzify appointed FLV with Centroid based on accuracy
	switch (accuracy)
	{
	case LOW_5:
		m_FuzVars[NameOfFLV]->DeFuzzifyCentroid(LOW_5);
		break;
	case MID_10:
		m_FuzVars[NameOfFLV]->DeFuzzifyCentroid(MID_10);
		break;
	case HIGH_15:
		m_FuzVars[NameOfFLV]->DeFuzzifyCentroid(HIGH_15);
		break;
	case EXTREME_20:
		m_FuzVars[NameOfFLV]->DeFuzzifyCentroid(EXTREME_20);
		break;
	}

	return 0.0f;
}

inline void FuzzyModule::SetConfsOfConsqToZero()
{
	for (auto i : m_FuzRules)
	{
		i->SetConfidenceOfConsequentToZero();
	}
}

FuzzyModule::~FuzzyModule()
{
	//delete all Fuzzy Variables in the map
	for (auto i : m_FuzVars)
	{
		//i.second, the second section of std::pair, which is the pointer
		delete i.second;
	}
	//delete all Fuzzy Rules in the vector array
	for(auto i : m_FuzRules)
	{
		delete i;
	}
	//clear the vector array
	m_FuzRules.clear();
}
