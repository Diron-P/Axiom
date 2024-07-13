#include "D3D11Buffer.h"

Axiom::D3D11Buffer::D3D11Buffer(D3D11Device* device, D3D11_BIND_FLAG type, const bool isStaging)
	: m_buffer{ nullptr }
	, m_device{ device }
{
	D3D11_BUFFER_DESC desc = {};
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.ByteWidth = 0;
	desc.BindFlags = type;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;

	if (isStaging)
	{
		desc.Usage = D3D11_USAGE_STAGING;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE;
	}

	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem = nullptr;

	HRESULT hr = m_device->GetDevice()->CreateBuffer(&desc, &initData, &m_buffer);
}

Axiom::D3D11Buffer::~D3D11Buffer()
{
	if (m_buffer != nullptr)
	{
		m_buffer->Release();
		m_buffer = nullptr;
	}
}
