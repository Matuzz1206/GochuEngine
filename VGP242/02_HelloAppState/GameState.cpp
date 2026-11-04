#include "GameState.h"
using namespace GochuEngine::Input;
void GameState::Initialize()
{
	LOG("GAME STATE INITIALIZE");
}

void GameState::Update(float deltaTime)
{
	if (InputSystem::Get()->IsKeyPressed(KeyCode::SPACE))
	{
		GochuEngine::MainApp().ChangeState("MainState");
	}
}

void GameState::Terminate()
{

}