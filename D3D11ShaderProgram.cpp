#include "D3D11ShaderProgram.h"

Axiom::D3D11ShaderProgram::D3D11ShaderProgram(const D3D11Device* device, const ShaderBlob& blob)
	: m_inputLayout{ nullptr }
	, m_vertexShader{ nullptr }
	, m_pixelShader{ nullptr }
	, m_device{ device }
	, m_blob{ blob }
{
}

void Axiom::D3D11ShaderProgram::CreateVertexShader()
{
	const HRESULT hr = m_device->GetDevice()->CreateVertexShader(m_blob.data, m_blob.size, nullptr, &m_vertexShader);
	if (FAILED(hr));	// Todo - replace with asserts
}
