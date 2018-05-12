#pragma once
#ifndef FUZSET_SINGLETON_H
#define FUZSET_SINGLETON_H
//-------------------------------------------------------------//
//															   //
//	Name: FuzSet_Singleton.h								   //
//															   //
//	Desc: A Fuzzy Set in [Singleton] shape.					   //
//		  Degree Of Membership (DOM) range: 0.0f ~ 1.0f		   //
//		  crisp value principle: m_dLeft < m_dPeak < m_dRight  //
//															   //
//-------------------------------------------------------------//

#include "FuzSet_Base.h"

class FuzSet_Singleton : public FuzSet_Base
{
public:
	//Whenever a Singleton FuzSet is create, thee following infos have
	//to be input. Left, Peak and Right crisp values
	//The Peak(mid) value will be the Representative Value
	FuzSet_Singleton(float lft, float mid, float rgt) :
		FuzSet_Base(mid), m_dLeft(lft), m_dPeak(mid), m_dRight(rgt) {};
	float CalculateDOM(float val) const;

private:
	float m_dLeft;
	float m_dPeak;
	float m_dRight;
};

#endif
