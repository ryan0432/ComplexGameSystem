#pragma once
class FuzTerm
{
public:

	virtual ~FuzTerm() {};

	//All terms have to implement a virtual constructor
	virtual FuzTerm* Clone() const = 0;
	//Retrieves the degree of membership of the term
	virtual float GetDOM() const = 0;
	//Clears the degree of membership of the term
	virtual void ClearDOM() = 0;
	//Updates DOM of a consequent when a fuzzy rule gets launched
	virtual void ORwithDOM(float val) = 0;
};

