#include "DiamondState.h"

using namespace GochuEngine::Graphics;
using namespace GochuEngine::Input;

void DiamondState::Initialize()
{
	// Diamond: 4 triangles around the center
	// top-right
	m_vertices.push_back({ {  0.0f,  0.0f, 0.0f }, GochuEngine::Colors::White });
	m_vertices.push_back({ {  0.0f,  0.8f, 0.0f }, GochuEngine::Colors::Blue });
	m_vertices.push_back({ {  0.5f,  0.0f, 0.0f }, GochuEngine::Colors::Magenta });
	// bottom-right
	m_vertices.push_back({ {  0.0f,  0.0f, 0.0f }, GochuEngine::Colors::White });
	m_vertices.push_back({ {  0.5f,  0.0f, 0.0f }, GochuEngine::Colors::Magenta });
	m_vertices.push_back({ {  0.0f, -0.8f, 0.0f }, GochuEngine::Colors::Green });
	// bottom-left
	m_vertices.push_back({ {  0.0f,  0.0f, 0.0f }, GochuEngine::Colors::White });
	m_vertices.push_back({ {  0.0f, -0.8f, 0.0f }, GochuEngine::Colors::Green });
	m_vertices.push_back({ { -0.5f,  0.0f, 0.0f }, GochuEngine::Colors::Yellow });
	// top-left
	m_vertices.push_back({ {  0.0f,  0.0f, 0.0f }, GochuEngine::Colors::White });
	m_vertices.push_back({ { -0.5f,  0.0f, 0.0f }, GochuEngine::Colors::Yellow });
	m_vertices.push_back({ {  0.0f,  0.8f, 0.0f }, GochuEngine::Colors::Blue });

	auto device = GraphicsSystem::Get()->GetDevice();

	D3D11_BUFFER_DESC bufferDesc{};
	bufferDesc.ByteWidth = static_cast<UINT>(m_vertices.size()) * sizeof(Vertex);
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem = m_vertices.data();

	HRESULT hr = device->CreateBuffer(&bufferDesc, &initData, &m_vertexBuffer);
	ASSERT(SUCCEEDED(hr), "Failed to create vertex buffer");

	std::filesystem::path shaderFilePath = L"../../Assets/Shaders/DoColor.fx";

	DWORD shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;
	ID3DBlob* shaderBlob = nullptr;
	ID3DBlob* errorBlob = nullptr;
	hr = D3DCompileFromFile(
		shaderFilePath.c_str(),
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"VS", "vs_5_0",
		shaderFlags, 0,
		&shaderBlob,
		&errorBlob
	);
	if (errorBlob != nullptr && errorBlob->GetBufferPointer() != nullptr)
	{
		LOG("%s", static_cast<const char*>(errorBlob->GetBufferPointer()));
	}
	ASSERT(SUCCEEDED(hr), "Failed to compile vertex shader");

	hr = device->CreateVertexShader(
		shaderBlob->GetBufferPointer(),
		shaderBlob->GetBufferSize(),
		nullptr,
		&m_vertexShader);
	ASSERT(SUCCEEDED(hr), "Failed to create vertex shader");

	std::vector<D3D11_INPUT_ELEMENT_DESC> vertexLayout;
	vertexLayout.push_back({ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT });
	vertexLayout.push_back({ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT });

	hr = device->CreateInputLayout(
		vertexLayout.data(),
		static_cast<UINT>(vertexLayout.size()),
		shaderBlob->GetBufferPointer(),
		shaderBlob->GetBufferSize(),
		&m_inputLayout
	);
	ASSERT(SUCCEEDED(hr), "Failed to create input layout");
	SafeRelease(shaderBlob);
	SafeRelease(errorBlob);

	hr = D3DCompileFromFile(
		shaderFilePath.c_str(),
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"PS", "ps_5_0",
		shaderFlags, 0,
		&shaderBlob,
		&errorBlob);
	if (errorBlob != nullptr && errorBlob->GetBufferPointer() != nullptr)
	{
		LOG("%s", static_cast<const char*>(errorBlob->GetBufferPointer()));
	}
	ASSERT(SUCCEEDED(hr), "Failed to compile pixel shader");

	hr = device->CreatePixelShader(
		shaderBlob->GetBufferPointer(),
		shaderBlob->GetBufferSize(),
		nullptr,
		&m_pixelShader);
	ASSERT(SUCCEEDED(hr), "Failed to create pixel shader");
	SafeRelease(shaderBlob);
	SafeRelease(errorBlob);
}

void DiamondState::Update(float deltaTime)
{
	if (InputSystem::Get()->IsKeyPressed(KeyCode::SPACE))
	{
		MainApp().ChangeState("HeartState");
	}
}

void DiamondState::Render()
{
	auto context = GraphicsSystem::Get()->GetContext();

	// bind all the buffers
	context->VSSetShader(m_vertexShader, nullptr, 0);
	context->IASetInputLayout(m_inputLayout);
	context->PSSetShader(m_pixelShader, nullptr, 0);

	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// draw
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	context->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);
	context->Draw(static_cast<UINT>(m_vertices.size()), 0);
}

void DiamondState::Terminate()
{
	m_vertices.clear();
	SafeRelease(m_pixelShader);
	SafeRelease(m_inputLayout);
	SafeRelease(m_vertexShader);
	SafeRelease(m_vertexBuffer);
}