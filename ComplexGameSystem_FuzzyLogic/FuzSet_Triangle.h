#pragma once
#include "FuzSet_Base.h"
class FuzSet_Triangle : public FuzSet_Base
{
public:
	//Whenever a Triangle FuzSet is create, thee following infos have
	//to be input. Peak, Left and Right crisp values
	//The Peak(mid) value will be the Representative Value
	FuzSet_Triangle(float mid, float lft, float rgt) :
		FuzSet_Base(mid), m_dPeak(mid), m_dRight(rgt), m_dLeft(lft) {};

	//Inherited from FuzSet_Base, returns a DOM,
	//relative to input crisp value
	float CalculateDOM(float val) const;

private:
	float m_dPeak;
	float m_dRight;
	float m_dLeft;
};

