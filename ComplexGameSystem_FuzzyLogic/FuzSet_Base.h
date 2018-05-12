#pragma once
#ifndef FUZSET_BASE_H
#define FUZSET_BASE_H
//------------------------------------------------------------------------------//
//																 			   	//
//	Name: FuzSet_Base.h												 		   	//
//																 			   	//
//	Desc: A class that provides the base data structure and functionalities of	//
//		  a Fuzzy Set. This base model will be drived into different shapes. 	//
//																 			   	//
//------------------------------------------------------------------------------//

#include "assert.h"
#include <string>

class FuzSet_Base
{
protected:
	//A fuzzy set holds a Degree of Membership (DOM)
	//range: 0 ~ 1, which is the Y Axis in graph
	float m_dDOM;

	//A representative value is a crsip value where the
	//peak DOM projects on X Axis.
	//For a [Triangular] set, the value will be relative to
	//the [PEAK]
	//For a [Trapezoidal] set, the value will be relative to
	//the [MID of PLATEAU]
	float m_dRepresentativeVal;

public:
	//There is no default constructor for this base class.
	//A client needs to provide a Representative Value to create
	//an Fuzzy Set object
	FuzSet_Base(float RepVal) : m_dDOM(0.0f), m_dRepresentativeVal(RepVal) {};

	//Any class derived from this base Fuzzy Set class MUST take
	//in this function to caculate a certain crisp value's DOM
	//This function returns the DOM in the set relative to given value.
	//Note: This only RETURNS the DOM, not to set the DOM.
	//This function is setup for CENTROID Defuzzification for sampling.
	virtual float CalculateDOM(float val) const = 0;

	//If this Fuzzy Set is part of a consequent FLV and launched by a rule,
	//then this function sets the DOM, which is a confidence level, to the
	//maximum of the parameter value or the set's existing m_dDOM value.
	void ORwithDOM(float val) { if (val > m_dDOM) m_dDOM = val; }

	float GetRepVal() const { return m_dRepresentativeVal; };
	void ClearDOM() { m_dDOM = 0.0f; }
	float GetDOM() const { return m_dDOM; }
	void SetDOM(float val) { assert(val <= 1.0f && "Input value exceeds FLV limit (1.0f)");
							 assert(val >= 0.0f && "Input value is belows FLV limit (0.0f)");
							 m_dDOM = val; }

};

#endif
