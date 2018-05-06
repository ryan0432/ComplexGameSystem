#pragma once
#include "FuzSetBase.h"
class FuzSet_RightShoulder : public FuzSetBase
{
public:
	//Whenever a Right Shoulder FuzSet is create, thee following infos have
	//to be input. Peak and Left crisp values
	//The the Representative Value is the average of the values at the
	//beginning and end of the plateau for Left and Right Shoulder Sets
	FuzSet_RightShoulder(float mid, float lft) :
		FuzSetBase((mid + lft) / 2), m_dPeak(mid), m_dLeft(lft) {};

	//Inherited from FuzSetBase, returns a DOM,
	//relative to input crisp value
	float CalculateDOM(float val) const;

private:
	float m_dPeak;
	float m_dLeft;

};

