#include "MainState.h"

using namespace GochuEngine::Input;

void MainState::Initialize()
{
	LOG("MAIN STATE INITIALIZED");
}

void MainState::Update(float deltaTime)
{
	if (InputSystem::Get()->IsKeyPressed(KeyCode::SPACE))
	{
		GochuEngine::MainApp().ChangeState("GameState");
	}
}

void MainState::Terminate()
{
	LOG("MAIN STATE IS TERMINATED");
}