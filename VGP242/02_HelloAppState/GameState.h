#pragma once

#include <GochuEngine/Inc/GochuEngine.h>

class GameState : public GochuEngine::AppState
{
public:
	void Initialize() override;
	void Update(float deltaTime) override;
	void Terminate() override;
};