#include "FuzVariable.h"
#include "FuzOperators.h"
#include "FuzSet_Base.h"
#include "FuzSet_Triangle.h"
#include "FuzSet_LeftShoulder.h"
#include "FuzSet_RightShoulder.h"
#include "FuzSet_Singleton.h"
#include "FuzProxySet.h"
#include "assert.h"
#include <iostream>


FuzVariable::~FuzVariable()
{
	for (auto i : m_MemberSets)
	{
		delete i.second;
	}
}

void FuzVariable::AdjustRangeToFit(float minBound, float maxBound)
{
	//If input value is lesser than current min range,
	//stretch the current min range to fit.
	if (minBound < m_dMinRange) { m_dMinRange = minBound; }
		
	//If input value is greater than current max range,
	//stretch the current max range to fit.
	if (maxBound > m_dMaxRange) { m_dMaxRange = maxBound; }
}

FuzProxySet FuzVariable::AddLeftShoulderSet(std::string name, float minBound, float peak, float maxBound)
{
	//Assert, make sure clients not to input silly values.
	AddFuzSetDebug(minBound, peak, maxBound);
	//Create a new [Left Shoulder] Fuzzy Set and assign a name to it.
	m_MemberSets[name] = new FuzSet_LeftShoulder(minBound, peak, maxBound);
	//Adjust the min/max range of the Fuzzy Variable.
	AdjustRangeToFit(minBound, maxBound);

	return FuzProxySet(*m_MemberSets[name]);
}

FuzProxySet FuzVariable::AddTriangleSet(std::string name, float minBound, float peak, float maxBound)
{
	//Assert, make sure clients not to input silly values.
	AddFuzSetDebug(minBound, peak, maxBound);
	//Create a new [Triangle] Fuzzy Set and assign a name to it.
	m_MemberSets[name] = new FuzSet_Triangle(minBound, peak, maxBound);
	//Adjust the min/max range of the Fuzzy Variable.
	AdjustRangeToFit(minBound, maxBound);
	
	return FuzProxySet(*m_MemberSets[name]);
}

FuzProxySet FuzVariable::AddRightShoulderSet(std::string name, float minBound, float peak, float maxBound)
{
	//Assert, make sure clients not to input silly values
	AddFuzSetDebug(minBound, peak, maxBound);
	//Create a new [Right Shoulder] Fuzzy Set and assign a name to it.
	m_MemberSets[name] = new FuzSet_RightShoulder(minBound, peak, maxBound);
	//Adjust the min/max range of the Fuzzy Variable.
	AdjustRangeToFit(minBound, maxBound);

	return FuzProxySet(*m_MemberSets[name]);
}

FuzProxySet FuzVariable::AddSingletonSet(std::string name, float minBound, float peak, float maxBound)
{
	//Assert, make sure clients not to input silly values
	AddFuzSetDebug(minBound, peak, maxBound);
	//Create a new [Singleton] Fuzzy Set and assign a name to it.
	m_MemberSets[name] = new FuzSet_Singleton(minBound, peak, maxBound);
	//Adjust the min/max range of the Fuzzy Variable.
	AdjustRangeToFit(minBound, maxBound);
	return FuzProxySet(*m_MemberSets[name]);
}

void FuzVariable::Fuzzify(float val)
{
	//Assert, make sure clients not to input silly values
	assert(val >= m_dMinRange && "FuzVariable::Fuzzify -> Input value is out of minimum range.");
	assert(val <= m_dMaxRange && "FuzVariable::Fuzzify -> Input value is out of maximum range.");

	//For each fuzzy set
	for (auto i : m_MemberSets)
	{
		//Clear the stored DOM.
		i.second->ClearDOM();
		//Set DOM to calculated value.
		//Ex: 300.0f of hunger in the set of [NotReally], DOM is 0.5f
		//based on the graph.
		i.second->SetDOM(i.second->CalculateDOM(val));
	}
}

//Defuzzify the value by averaging the maxima (representative value)
//of the sets that launched.
//Equation: Output = sum (maxima * DOM) / sum (DOMs)
float FuzVariable::DeFuzzifyMaxAV() const
{
	//Setup the numerator and denominator
	float numerator = 0.0f;
	float denominator = 0.0f;

	//For each subset
	for (auto i : m_MemberSets)
	{
		//Add up all [Representative Value] * DOM as numerator
		numerator += i.second->GetRepVal() * i.second->GetDOM();
		//Add up all DOMs as denominator
		denominator += i.second->GetDOM();
	}

	//To prevent value divided by, if denominator is 0
	//return 0
	if (denominator == 0.0f) return 0.0f;

	//return Defuzzified value
	return numerator / denominator;
}

float FuzVariable::DeFuzzifyCentroid(unsigned int sampleNumber) const
{
	//Setup the range for each step
	float StepRange = (m_dMaxRange - m_dMinRange) / (float)sampleNumber;
	//Setup the sum of total area
	float TotalArea = 0.0f;
	//Setup the sum for each step
	float SumPerStep = 0.0f;

	//for each sample step
	for (unsigned int samp = 1; samp <= sampleNumber; samp++)
	{
		//Look into each set at the step point
		for (auto i : m_MemberSets)
		{
			//Set up a contribution value
			float contribution = 0.0f;
			//Calculate the DOM at current step
			float calculatedDOM = i.second->CalculateDOM(m_dMinRange + samp * StepRange);
			//Get the current DOM of the set
			float currDOM = i.second->GetDOM();
			//Compare these two and copy the lower one to contribution value
			if (calculatedDOM > currDOM) { contribution = currDOM; }
			else { contribution = calculatedDOM; }
			//Add contribution to TotalArea
			TotalArea += contribution;
			//Add current value at the step range times contribution to SumPerStep
			SumPerStep += (m_dMinRange + samp * StepRange) * contribution;
		}
	}

	//To prevent value divided by, if denominator is 0
	//return 0
	if (TotalArea == 0.0f) { return 0.0f; }
	//return Defuzzified value
	return SumPerStep / TotalArea;
}

void FuzVariable::AddFuzSetDebug(float minBound, float peak, float maxBound) const
{
	//Assert, make sure clients not to input silly values
	//priciple: minBound < peak < maxBound
	assert(maxBound > peak && "FuzVariable::AddFuzSetDebug -> The [Right Value] should always greater than [Mid Value]");
	assert(minBound < peak && "FuzVariable::AddFuzSetDebug -> The [Left Value] should always lesser than [Mid Value]");
	assert(maxBound > minBound && "FuzVariable::AddFuzSetDebug -> The [Right Value] should always greater than [Left Value]");
	assert(minBound < maxBound && "FuzVariable::AddFuzSetDebug -> The [Left Value] should always lesser than [Right Value]");
}

std::ostream& FuzVariable::PrintDOMs(std::ostream& os)
{
	for (auto i : m_MemberSets)
	{
		os << "\n" << i.first << " is " << i.second->GetDOM();
	}

	os << "\nMin Range: " << m_dMinRange << "\nMaxRange: " << m_dMaxRange;

	return os;
}
