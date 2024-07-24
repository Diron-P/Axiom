#include "Mesh.h"

Axiom::Mesh::Mesh()
{
}

//Axiom::Mesh::Mesh(unsigned int numVertices, unsigned int numIndices)
//	: m_numVertices{numVertices}
//	, m_numIndices{numIndices}
//	, m_vertices{new Vector3[m_numVertices]}
//	, m_indices{new unsigned int[m_numIndices]}
//{
//}

Axiom::Mesh::~Mesh()
{
	delete[] m_vertices;
	delete[] m_normals;
	delete[] m_textureCoords;
	delete[] m_indices;
}
