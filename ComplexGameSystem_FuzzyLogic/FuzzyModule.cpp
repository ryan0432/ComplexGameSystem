#include "FuzzyModule.h"
#include "FuzVariable.h"
#include "FuzRule.h"
#include "FuzTerm.h"

FuzVariable& FuzzyModule::CreateFLV(const std::string& VarName)
{
	//New a unique pointer in std::map, Method 1
	//m_FuzLinguVars[VarName] = std::unique_ptr<FuzLinguVar>(new FuzLinguVar());
	//New a unique pointer in std::map, Method 2
	//m_FuzLinguVars[VarName] = std::make_unique<FuzLinguVar>();
	//Traditional pointer operation, Method3
	m_FuzVars[VarName] = new FuzVariable();
	return *m_FuzVars[VarName];
}

void FuzzyModule::AddFuzRule(FuzTerm & antecedent, FuzTerm & consequence)
{
	//m_FuzRules.push_back( std::unique_ptr<FuzRule>( new FuzRule(antecedent, consequence) ) );
}

inline void FuzzyModule::Fuzzify(const std::string & NameOfFLV, float val)
{
}

inline float FuzzyModule::Defuzzify(const std::string & key, DefuzType method)
{
	return 0.0f;
}

inline void FuzzyModule::SetConfsOfConsqToZero()
{
}

FuzzyModule::~FuzzyModule()
{
	//TODO: clean up all pointers in
	//1. m_FuzLinguVars
	//2. m_FuzVars
}
