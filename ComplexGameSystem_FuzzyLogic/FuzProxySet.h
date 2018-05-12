#pragma once
#ifndef FUZ_PROXY_SET_H
#define FUZ_PROXY_SET_H
//--------------------------------------------------------------//
//																//
//	Name: FuzProxySet.h											//
//																//
//	Desc: A class that provides a proxy for an actual Fuzzy		//
//		  Set. Inherited from FuzTerm to create Fuzzy Rules.	//
//		  Due to its nature of a proxy of Fuzzy Set, its		//
//		  functions are inherited from FuzTerm yet all these	//
//		  functions are actually calling FuzSet_Base's.			//
//																//
//--------------------------------------------------------------//

#include "FuzTerm.h"
#include "FuzSet_Base.h"

class FuzAND;
class FuzOR;

class FuzProxySet : public FuzTerm
{
public:
	//FuzProxySet Constructor, holds an actual Fuzzy Set
	FuzProxySet(FuzSet_Base& fzSet) : m_Set(fzSet) {}

	//All terms have to implement a virtual constructor
	//When making calculation, cloning can prevent changing the orginal data
	FuzTerm* Clone() const { return new FuzProxySet(*this); }

	//Retrieves the degree of membership of the term
	float GetDOM()const { return m_Set.GetDOM(); }

	//Clears the degree of membership of the term
	void ClearDOM() { m_Set.ClearDOM(); }

	//Updates DOM of a consequent when a fuzzy rule gets launched
	void ORwithDOM(float val) { m_Set.ORwithDOM(val); }

private:
	FuzSet_Base& m_Set;
};

#endif