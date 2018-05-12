#ifndef FUZ_VARIABLE_H
#define FUZ_VARIABLE_H
#pragma once
//-----------------------------------------------------------------//
//																   //
//	Name: FuzVariable.h											   //
//																   //
//	Desc: A class that defines a Fuzzy Linguistic Variable (FLV).  //
//		  An FLV comprises of a number of fuzzy sets.			   //
//		  It can be drawen as a graph like below.				   //
//		  https://goo.gl/q8bjXA									   //
//		  It is the very basic element of a Fuzzy Rule.			   //
//																   //
//-----------------------------------------------------------------//

#include <map>
#include <iosfwd>
#include <string>

class FuzzyModule;
class FuzSet_Base;
class FuzProxySet;

class FuzVariable
{
private:

	typedef std::map<std::string, FuzSet_Base*> MemberSets;
	
	//Stores added Fuzzy Sets as subsets
	MemberSets m_MemberSets;

	//Setup the min and max range of this Fuzzy Variable
	float m_dMinRange;
	float m_dMaxRange;

	//Adjust current Fuzzy Variable's boundaries to meet assigned min/max value.
	void AdjustRangeToFit(float minBound, float maxBound);

	//Clients will get a reference of fuzzy variable when an instance is created
	//via FuzzyModule::CreateFLV(). To prevent clients from deleting the instance,
	//the destructor of FuzLinguVar class should be private and Fuzzy Module class
	//should be a friend class so its private functions can be accessed.
	~FuzVariable();
	friend class FuzzyModule;

public:
	//FuzVariable Constructor (float minRange, float maxRange)
	FuzVariable() : m_dMinRange(0.0f), m_dMaxRange(0.0f) {}

	//Add a [Left Shoulder] Fuzzy Set to the Fuzzy Variable.
	FuzProxySet AddLeftShoulderSet(std::string name, float minBound, float peak, float maxBound);
	
	//Add a [Triangle] Fuzzy Set to the Fuzzy Variable.
	FuzProxySet AddTriangleSet(std::string name, float minBound, float peak, float maxBound);
	
	//Add a [Right Shoulder] Fuzzy Set to the Fuzzy Variable.
	FuzProxySet AddRightShoulderSet(std::string name, float minBound, float peak, float maxBound);
	
	//Add a [Singleton] Fuzzy Set to the Fuzzy Variable.
	FuzProxySet AddSingletonSet(std::string name, float minBound, float peak, float maxBound);

	//Fizzify a value by calculation its DOM in each of this Fuzzy Variable's subsets
	void Fuzzify(float val);

	//Defuzzify the value by averaging the maxima (representative value)
	//of the sets that launched.
	//Equation: Output = sum (maxima * DOM) / sum (DOMs)
	float DeFuzzifyMaxAV() const;

	//Defuzzify the value by averaging the sampled representative value
	//of the sets that launched. 
	//Equation: Output = sum (sampled value * DOM) / sum (lower DOMs)
	float DeFuzzifyCentroid(unsigned int sampleNumber) const;

	//Assert, make sure clients not to input silly values when add a Fuzzy Set.
	//priciple: minBound < peak < maxBound
	void AddFuzSetDebug(float minBound, float peak, float maxBound) const;

	//Print DOMs for all subsets in the Fuzzy Variable
	std::ostream& PrintDOMs(std::ostream& os);

	//Disallow clients to shallow copy a Fuzzy Variable by creating instance
	FuzVariable(const FuzVariable&) = delete;
	//Disallow clients to shallow copy a Fuzzy Variable by assigning
	FuzVariable& operator=(const FuzVariable&) = delete;
};

#endif