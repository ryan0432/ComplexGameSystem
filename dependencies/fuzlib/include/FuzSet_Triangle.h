#pragma once
#ifndef FUZSET_TRIANGLE_H
#define FUZSET_TRIANGLE_H
//-------------------------------------------------------------//
//															   //
//	Name: FuzSet_Triangle.h									   //
//															   //
//	Desc: A Fuzzy Set in [Triangle] shape.					   //
//		  Degree Of Membership (DOM) range: 0.0f ~ 1.0f		   //
//		  crisp value principle: m_dLeft < m_dPeak < m_dRight  //
//															   //
//-------------------------------------------------------------//

#include "FuzSet_Base.h"

class FuzSet_Triangle : public FuzSet_Base
{
public:
	//Whenever a Triangle FuzSet is create, thee following infos have
	//to be input. Peak, Left and Right crisp values
	//The Peak(mid) value will be the Representative Value
	FuzSet_Triangle(float lft, float mid, float rgt) :
		FuzSet_Base(mid), m_dLeft(lft), m_dPeak(mid), m_dRight(rgt) {};

	//Inherited from FuzSet_Base, returns a DOM,
	//relative to input crisp value
	float CalculateDOM(float val) const;

private:
	float m_dLeft;
	float m_dPeak;
	float m_dRight;
};

#endif

