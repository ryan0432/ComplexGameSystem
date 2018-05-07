#pragma once
#include <map>

class FuzzyModule;
class FuzSetBase;
class FzSet;
class FuzVariable
{
private:

	typedef std::map<std::string, FuzSetBase*> MemberSets;

	//Disallow clients to cpoy Fuzzy Linguistic Variable
	FuzVariable(const FuzVariable&);
	FuzVariable& operator=(const FuzVariable&);

	MemberSets m_MemberSets;

	float m_dMinRange;
	float m_dMaxRange;

	void AdjustRangeToFit(float min, float max);

	//Clients will get a reference of fuzzy variable when an instance is created
	//via FuzzyModule::CreateFLV(). To prevent clients from deleting the instance,
	//the destructor of FuzLinguVar class should be private and Fuzzy Module class
	//should be a friend class so its private functions can be accessed.
	~FuzVariable();
	friend class FuzzyModule;

public:
	FuzVariable() :m_dMinRange(0.0f), m_dMaxRange(0.0f) {}

	FzSet AddLeftShoulderSet(std::string name, float minBound, float peak, float maxBound);
	FzSet AddTriangleSet(std::string name, float minBound, float peak, float maxBound);
	FzSet AddRightShoulderSet(std::string name, float minBound, float peak, float maxBound);
	FzSet AddSingletonSet(std::string name, float minBound, float peak, float maxBound);

	//Fizzify a value by calculation its DOM in each of this Fuzzy Variable's subsets
	void Fuzzify(float val);

	float DeFuzzifyMaxAV() const;

	float DeFuzzifyCentroid(int centroidAccuracy) const;

};