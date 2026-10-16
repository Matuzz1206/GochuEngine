#include "Precompiled.h"
#include "App.h"

using namespace GochuEngine;
using namespace GochuEngine::Core;

void App::Run(const AppConfig& config)
{
	LOG("App Started");

	// initialize all singletons and window 
	Window myWindow;
	myWindow.Initialize(
		GetModuleHandleA(nullptr),
		config.appName,
		config.winWidth,
		config.winHeight
	);

	// initilize starting state

	// updates
	mIsRunning = true;
	while (mIsRunning)
	{
		myWindow.ProcessMessage();
		//updating all that needs updates
		if (!myWindow.IsActive())
		{
			Quit();
		}
	}

	LOG("App Is Closing");
	//terminate last state

	//termiante all singletons

	myWindow.Terminate();
}

void App::Quit()
{
	mIsRunning = false;
}