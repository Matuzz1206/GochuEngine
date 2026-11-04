#include <GochuEngine/Inc/GochuEngine.h>
#include "DoSomethingState.h"
#include "DoColorState.h"

int WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	GochuEngine::AppConfig config;
	config.appName = L"HelloShapes";

	GochuEngine::App& myApp = GochuEngine::MainApp();
	myApp.AddState<DoSomethingState>("DoSomethingState");
	myApp.AddState<DoColorState>("DoColorState");
	myApp.Run(config);

	return 0;
}