#pragma once
#include <GochuEngine/Inc/GochuEngine.h>

class DoSomethingState : public GochuEngine::AppState
{
public:
	void Initialize() override;
	void Update(float deltaTime) override;
	void Render() override;
	void Terminate() override;

private:
	struct Vertex
	{
		GochuEngine::Math::Vector3 position = GochuEngine::Math::Vector3::Zero;
		GochuEngine::Color color = GochuEngine::Colors::White;
	};
	using Vertices = std::vector<Vertex>;
	Vertices m_vertices;

	ID3D11Buffer* m_vertexBuffer = nullptr;
	ID3D11VertexShader* m_vertexShader = nullptr;
	ID3D11InputLayout* m_inputLayout = nullptr;
	ID3D11PixelShader* m_pixelShader = nullptr;
};