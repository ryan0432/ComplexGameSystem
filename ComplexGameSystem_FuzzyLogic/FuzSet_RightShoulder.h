#pragma once
#ifndef FUZSET_RIGHTSHOULDER_H
#define FUZSET_RIGHTSHOULDER_H
//-------------------------------------------------------------//
//															   //
//	Name: FuzSet_RightShoulder.h							   //
//															   //
//	Desc: A Fuzzy Set in [Right Shoulder] shape.			   //
//		  Degree Of Membership (DOM) range: 0.0f ~ 1.0f		   //
//		  crisp value principle: m_dLeft < m_dPeak < m_dRight  //
//															   //
//-------------------------------------------------------------//

#include "FuzSet_Base.h"

class FuzSet_RightShoulder : public FuzSet_Base
{
public:
	//Whenever a Right Shoulder FuzSet is create, thee following infos have
	//to be input. Peak and Left crisp values
	//The the Representative Value is the average of the values at the
	//beginning and end of the plateau for Left and Right Shoulder Sets
	FuzSet_RightShoulder(float lft, float mid, float rgt) :
		FuzSet_Base((mid + rgt) / 2), m_dLeft(lft), m_dPeak(mid), m_dRight(rgt) {};

	//Inherited from FuzSet_Base, returns a DOM,
	//relative to input crisp value
	float CalculateDOM(float val) const;

private:
	float m_dLeft;
	float m_dPeak;
	float m_dRight;
};

#endif
