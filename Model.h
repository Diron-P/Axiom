#ifndef MODEL_H
#define MODEL_H

#include "Math/Vector3.h"

namespace Axiom
{
	using namespace Math;

	class Model
	{
	public:
		Model();
		Model(const char* fileName);
		Model(unsigned int numVertices, unsigned int numIndices);
		~Model();

	private:
		unsigned int m_numVertices{ 0 };
		unsigned int m_numIndices{ 0 };
		Vector3* vertices{ nullptr };
		unsigned int* indices{ nullptr };
	};
}

#endif // !MODEL_H

