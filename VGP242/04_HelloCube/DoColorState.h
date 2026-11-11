#pragma once

#include <GochuEngine/Inc/GochuEngine.h>

class DoColorState : public GochuEngine::AppState
{
public:
	void Initialize() override;
	void Update(float deltaTime) override;
	void Render() override;
	void Terminate() override;
private:
	using Vertices = std::vector<GochuEngine::Graphics::VertexPC>;
	Vertices m_vertices;

	GochuEngine::Graphics::MeshBuffer m_meshBuffer;
	GochuEngine::Graphics::VertexShader m_vertexShader;
	GochuEngine::Graphics::PixelShader m_pixelShader;
	GochuEngine::Graphics::Camera m_camera;
	GochuEngine::Graphics::ConstantBuffer m_transformBuffer;
};