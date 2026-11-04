#pragma once
#include <GochuEngine/Inc/GochuEngine.h>

class MainState : public GochuEngine::AppState
{
public:
	void Initialize() override;
	void Update(float deltaTime) override;
	void Terminate() override;
};