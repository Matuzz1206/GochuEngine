#include <GochuEngine/Inc/GochuEngine.h>
#include "DoSomethingState.h"
#include "DiamondState.h"
#include "HeartState.h"

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	GochuEngine::AppConfig config;
	config.appName = L"Hello Shapes";

	GochuEngine::App& myApp = GochuEngine::MainApp();
	myApp.AddState<DoSomethingState>("DoSomethingState");   // first state added = starts first
	myApp.AddState<DiamondState>("DiamondState");
	myApp.AddState<HeartState>("HeartState");
	myApp.Run(config);
	return 0;
}