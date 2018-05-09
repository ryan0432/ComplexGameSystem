#pragma once
#include "FuzSet_Base.h"
class FuzSet_LeftShoulder : public FuzSet_Base
{
public:
	//Whenever a Left Shoulder FuzSet is create, thee following infos have
	//to be input. Left, Peak and Right crisp values.
	//The the Representative Value is the average of the values at the
	//beginning and end of the plateau for Left and Right Shoulder Sets
	FuzSet_LeftShoulder(float lft, float mid, float rgt) :
		FuzSet_Base((mid + lft) / 2), m_dLeft(lft), m_dPeak(mid), m_dRight(rgt) {};

	//Inherited from FuzSet_Base, returns a DOM,
	//relative to input crisp value
	float CalculateDOM(float val) const;

private:
	float m_dLeft;
	float m_dPeak;
	float m_dRight;
};

