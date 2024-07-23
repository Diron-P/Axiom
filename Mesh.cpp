#include "Mesh.h"

Axiom::Mesh::Mesh()
{
}

Axiom::Mesh::~Mesh()
{
	delete[] m_vertices;
	delete[] m_normals;
	delete[] m_textureCoords;
	delete[] m_indices;
}
