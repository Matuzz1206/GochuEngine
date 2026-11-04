#include <GochuEngine/Inc/GochuEngine.h>
#include "MainState.h"
#include "GameState.h"

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	GochuEngine::AppConfig config;
	config.appName = L"Hello App State";

	GochuEngine::App& myApp = GochuEngine::MainApp();
	myApp.AddState<MainState>("MainState");
	myApp.AddState<GameState>("GameState");
	myApp.Run(config);

	return 0;
}