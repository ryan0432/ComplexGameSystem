#pragma once
#include "FuzSetBase.h"
class FuzSet_Triangle : public FuzSetBase
{
public:
	//Whenever a Triangle FuzSet is create, thee following infos have
	//to be input. Peak, Left and Right crisp values
	//The Peak(mid) value will be the Representative Value
	FuzSet_Triangle(float mid, float lft, float rgt) :
		FuzSetBase(mid), m_dPeak(mid), m_dRight(rgt), m_dLeft(lft) {};

	//Inherited from FuzSetBase, returns a DOM,
	//relative to input crisp value
	float CalculateDOM(float val) const;

private:
	float m_dPeak;
	float m_dRight;
	float m_dLeft;

};

