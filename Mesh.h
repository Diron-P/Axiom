#ifndef MESH_H
#define MESH_H

#include "Math/Vector2.h"
#include "Math/Vector3.h"

namespace Axiom
{
	using namespace Math;

	class Mesh
	{
	public:
		Mesh();
		//Mesh(unsigned int numVertices, unsigned int numIndices);
		~Mesh();

		unsigned int m_numVertices{ 0 };
		unsigned int m_numIndices{ 0 };

		Vector3* m_vertices{ nullptr };
		Vector3* m_normals{nullptr};
		Vector2* m_textureCoords{nullptr};
		unsigned int* m_indices{ nullptr };
	};
}

#endif // !MESH_H
