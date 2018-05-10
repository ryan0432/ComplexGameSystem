#include "ComplexGameSystem_FuzzyLogicApp.h"
#include "vld.h"

int main()
{
	// allocation
	auto app = new ComplexGameSystem_FuzzyLogicApp();

	// initialise and loop
	app->run("AIE", 1280, 720, false);

	// deallocation
	delete app;

	return 0;
}