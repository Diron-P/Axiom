#ifndef D3D11_SHADER_PROGRAM_H
#define D3D11_SHADER_PROGRAM_H

#include "D3D11Device.h"

namespace Axiom
{
	struct ShaderBlob
	{
		char* data;
		unsigned long size;
	};

	class D3D11ShaderProgram
	{
	public:
		D3D11ShaderProgram(const D3D11Device* device, const ShaderBlob& blob);
		void CreateVertexShader();

		ID3D11InputLayout* m_inputLayout;
		ID3D11VertexShader* m_vertexShader;
		ID3D11PixelShader* m_pixelShader;

		const D3D11Device* m_device;
		const ShaderBlob& m_blob;
	};
}

#endif // !D3D11_SHADER_PROGRAM_H

