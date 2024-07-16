#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h> 

#include "Model.h"
#include "Math/Vector3.h"

Axiom::Model::Model()
{
}

Axiom::Model::Model(const char* fileName)
{
	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(fileName,
		aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType);

	// Can only handle one mesh for now.
	if (scene != nullptr && scene->mNumMeshes == 1)
	{
		aiMesh* mesh = scene->mMeshes[0];

		m_numVertices = mesh->mNumVertices;
		vertices = new Vector3[m_numVertices];

		for (int i = 0; i < m_numVertices; ++i)
		{
			aiVector3D vertex = mesh->mVertices[i];
			vertices[i].Set(vertex.x, vertex.y, vertex.z);
		}
	}
}

Axiom::Model::Model(unsigned int numVertices, unsigned int numIndices)
	: m_numVertices{numVertices}
	, m_numIndices{numIndices}
{
	vertices = new Vector3[m_numVertices];
	indices = new unsigned int[m_numIndices];
}

Axiom::Model::~Model()
{
	delete[] vertices;
	delete[] indices;
}
