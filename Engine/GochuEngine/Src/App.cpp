#include "Precompiled.h"
#include "App.h"

using namespace GochuEngine;
using namespace GochuEngine::Core;
using namespace GochuEngine::Graphics;

void App::Run(const AppConfig& config)
{
	LOG("App Started");

	// initialize all singletons and window (staticinitialize)
	Window myWindow;
	myWindow.Initialize(
		GetModuleHandleA(nullptr),
		config.appName,
		config.winWidth,
		config.winHeight
	);
	auto handle = myWindow.GetWindowHandle();
	GraphicsSystem::StaticInitialize(handle, false);


	// initialize starting state

	// updates
	mIsRunning = true;
	while (mIsRunning)
	{
		myWindow.ProcessMessage();
		// updating all that needs updates
		if (!myWindow.IsActive())
		{
			Quit();
			continue;
		}
	}


	LOG("App Is Closing");
	//terminate last state

	//termiante all singletons

	GraphicsSystem::StaticTerminate();
	myWindow.Terminate();
}

void App::Quit()
{
	mIsRunning = false;
}

void App::ChangeState(const std::string& stateName)
{
	auto iter = mAppStates.find(stateName);
	if (iter != mAppStates.end())
	{
		mNextState = iter->second.get();
	}
}
