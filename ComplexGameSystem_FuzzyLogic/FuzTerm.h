#ifndef FUZ_TERM_H
#define FUZ_TERM_H
#pragma once
//---------------------------------------------------------------//
//																 //
//	Name: FuzTerm.h												 //
//																 //
//	Desc: An abstract class to provide an interface for classes  //
//		  able to be used as a term in a Fuzzy Rule.			 //
//		  Ex: IF [Antecedent] THAN [Consequence]				 //
//																 //
//---------------------------------------------------------------//

class FuzTerm
{
public:

	virtual ~FuzTerm() {};

	//All terms have to implement a virtual constructor
	//When making calculation, cloning can prevent changing the orginal data
	virtual FuzTerm* Clone() const = 0;

	//Retrieves the degree of membership of the term
	virtual float GetDOM() const = 0;

	//Clears the degree of membership of the term
	virtual void ClearDOM() = 0;

	//Updates DOM of a consequent when a fuzzy rule gets launched
	virtual void ORwithDOM(float val) = 0;
};

#endif
