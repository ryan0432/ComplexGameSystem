#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "FuzzyModule.h"
#include <iosfwd>
#include <string>


class ComplexGameSystem_FuzzyLogicApp : public aie::Application
{
public:

	ComplexGameSystem_FuzzyLogicApp();
	virtual ~ComplexGameSystem_FuzzyLogicApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;

private:
	FuzzyModule m_FuzzyModule;
	void InitializeFuzzyModule();
	void ControlUnit();
	std::ostream & PrintStatusScores(std::ostream& os);
	float m_staminaScore;
	float m_hydrationScore;
	float m_resourceScore;
};