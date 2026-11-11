#include "Precompiled.h"
#include "ConstantBuffer.h"
#include "GraphicsSystem.h"


using namespace GochuEngine;
using namespace GochuEngine::Graphics;

GochuEngine::Graphics::ConstantBuffer::~ConstantBuffer()
{
	ASSERT(m_constantBuffer == nullptr, "ConstantBuffer: terminate must be called");
}

void GochuEngine::Graphics::ConstantBuffer::Initialize(uint32_t bufferSize)
{
	auto device = GraphicsSystem::Get()->GetDevice();

	D3D11_BUFFER_DESC desc{};
	desc.ByteWidth = bufferSize;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;
	desc.StructureByteStride = 0;

	HRESULT hr = device->CreateBuffer(&desc, nullptr, &m_constantBuffer);
	ASSERT(SUCCEEDED(hr), "ConstantBuffer: failed to create constant buffer");
}

void GochuEngine::Graphics::ConstantBuffer::Terminate()
{
	SafeRelease(m_constantBuffer);
}

void GochuEngine::Graphics::ConstantBuffer::Update(const void* data) const
{
	auto context = GraphicsSystem::Get()->GetContext();
	context->UpdateSubresource(m_constantBuffer, 0, nullptr, data, 0, 0);
}

void GochuEngine::Graphics::ConstantBuffer::BindVS(uint32_t slot) const
{
	auto context = GraphicsSystem::Get()->GetContext();
	context->VSSetConstantBuffers(slot, 1, &m_constantBuffer);
}

void GochuEngine::Graphics::ConstantBuffer::BindPS(uint32_t slot) const
{
	auto context = GraphicsSystem::Get()->GetContext();
	context->PSSetConstantBuffers(slot, 1, &m_constantBuffer);
}