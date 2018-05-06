#pragma once
#include <map>
#include <memory>

class FzSet;
class FuzzyModule;
class FuzSetBase;
class FuzLinguVar
{
private:
	friend class FuzzyModule;

	typedef std::map< std::string, std::unique_ptr<FuzSetBase> > MemberSets;

	FuzLinguVar(const FuzLinguVar&);
	FuzLinguVar& operator=(const FuzLinguVar&);

	MemberSets m_MemberSets;

	float m_dMinRange;
	float m_dMaxRange;

	void AdjustRangeToFit(float min, float max);

public:
	FuzLinguVar() :m_dMinRange(0.0f), m_dMaxRange(0.0f) {}

};

