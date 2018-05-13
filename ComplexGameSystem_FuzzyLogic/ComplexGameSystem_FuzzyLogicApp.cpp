#include "ComplexGameSystem_FuzzyLogicApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include <iostream>
#include <string>

ComplexGameSystem_FuzzyLogicApp::ComplexGameSystem_FuzzyLogicApp()
{
	
}

ComplexGameSystem_FuzzyLogicApp::~ComplexGameSystem_FuzzyLogicApp()
{
	
}

bool ComplexGameSystem_FuzzyLogicApp::startup()
{
	m_2dRenderer = new aie::Renderer2D();

	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);

	InitializeFuzzyModule();
	m_staminaScore = 0.0;
	m_hydrationScore = 0.0f;
	m_resourceScore = 0.0;

	return true;
}

void ComplexGameSystem_FuzzyLogicApp::shutdown()
{
	delete m_font;
	delete m_2dRenderer;
}

void ComplexGameSystem_FuzzyLogicApp::update(float deltaTime)
{
	m_FuzzyModule.Fuzzify("Stamina", m_staminaScore);
	m_FuzzyModule.Fuzzify("Hydration", m_hydrationScore);

	ControlUnit();

	m_FuzzyModule.PrintAllDOMs(std::cout);
	PrintStatusScores(std::cout);
	system("cls");
}

void ComplexGameSystem_FuzzyLogicApp::draw()
{
	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	
	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}

void ComplexGameSystem_FuzzyLogicApp::InitializeFuzzyModule()
{
	FuzVariable& Stamina = m_FuzzyModule.CreateFLV("Stamina");
	FuzProxySet& Stamina_LOW = Stamina.AddLeftShoulderSet("Stamina_LOW", 0, 25, 50);
	FuzProxySet& Stamina_MID = Stamina.AddTriangleSet("Stamina_MID", 25, 50, 75);
	FuzProxySet& Stamina_HIGH = Stamina.AddRightShoulderSet("Stamina_HIGH", 50, 75, 100);

	FuzVariable& Hydration = m_FuzzyModule.CreateFLV("Hydration");
	FuzProxySet& Hydration_LOW = Hydration.AddLeftShoulderSet("Hydration_LOW", 0, 25, 50);
	FuzProxySet& Hydration_MID = Hydration.AddTriangleSet("Hydration_MID", 25, 50, 75);
	FuzProxySet& Hydration_HIGH = Hydration.AddRightShoulderSet("Hydration_HIGH", 50, 75, 100);

	FuzVariable& ResourceDesirability = m_FuzzyModule.CreateFLV("ResourceDesirability");
	FuzProxySet& ResourceDesirability_LOW = ResourceDesirability.AddLeftShoulderSet("ResourceDesirability_LOW", 0, 25, 50);
	FuzProxySet& ResourceDesirability_MID = ResourceDesirability.AddTriangleSet("ResourceDesirability_MID", 25, 50, 75);
	FuzProxySet& ResourceDesirability_HIGH = ResourceDesirability.AddRightShoulderSet("ResourceDesirability_HIGH", 50, 75, 100);

	m_FuzzyModule.AddFuzRule(Stamina_LOW, ResourceDesirability_HIGH);
	m_FuzzyModule.AddFuzRule(Stamina_MID, ResourceDesirability_MID);
	m_FuzzyModule.AddFuzRule(Stamina_HIGH, ResourceDesirability_LOW);
	m_FuzzyModule.AddFuzRule(Hydration_LOW, ResourceDesirability_HIGH);
	m_FuzzyModule.AddFuzRule(Hydration_MID, ResourceDesirability_MID);
	m_FuzzyModule.AddFuzRule(Hydration_HIGH, ResourceDesirability_LOW);
}

void ComplexGameSystem_FuzzyLogicApp::ControlUnit()
{
	// input example
	aie::Input* input = aie::Input::getInstance();

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();

	if (input->wasKeyPressed(aie::INPUT_KEY_UP))
		if (m_staminaScore <= 95.0f)
			m_staminaScore += 5.0f;

	if (input->wasKeyPressed(aie::INPUT_KEY_DOWN))
		if (m_staminaScore >= 5.0f)
			m_staminaScore -= 5.0f;

	if (input->wasKeyPressed(aie::INPUT_KEY_RIGHT))
		if (m_hydrationScore <= 95.0f)
			m_hydrationScore += 5.0f;

	if (input->wasKeyPressed(aie::INPUT_KEY_LEFT))
		if (m_hydrationScore >= 5.0f)
			m_hydrationScore -= 5.0f;

	if (input->wasKeyPressed(aie::INPUT_KEY_Q))
		m_resourceScore = m_FuzzyModule.DefuzzifyMaxAV("ResourceDesirability");

	if (input->wasKeyPressed(aie::INPUT_KEY_W))
		m_resourceScore = m_FuzzyModule.DeFuzzifyCentroid("ResourceDesirability", EXTREME_20);
}

std::ostream & ComplexGameSystem_FuzzyLogicApp::PrintStatusScores(std::ostream & os)
{
	os << "\n------------- Crisp Value -------------\n";
	os << "\nStamina   : " << m_staminaScore;
	os << "\nHydration : " << m_hydrationScore;
	os << "\nResource  : " << m_resourceScore;
	os << "\n\n";
	os << "\nPress [UP]    to add Stamina,   [DOWN] to reduce.";
	os << "\nPress [RIGHT] to add Hydration, [LEFT] to reduce.";
	os << "\n";
	os << "\nPress [Q]     to Defuzzify in   [MAX AVERAGE] mode.";
	os << "\nPress [W]     to Defuzzify in   [CENTROID]    mode.";
	os << std::endl;

	return os;
}
