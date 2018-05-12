#pragma once
#ifndef FUZSET_LEFTSHOULDER_H
#define FUZSET_LEFTSHOULDER_H
//-------------------------------------------------------------//
//															   //
//	Name: FuzSet_LeftShoulder.h								   //
//															   //
//	Desc: A Fuzzy Set in [Left Shoulder] shape.				   //
//		  Degree Of Membership (DOM) range: 0.0f ~ 1.0f		   //
//		  crisp value principle: m_dLeft < m_dPeak < m_dRight  //
//															   //
//-------------------------------------------------------------//

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

#endif