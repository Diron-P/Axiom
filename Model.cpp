#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h> 

#include "Model.h"

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
		vertices = (Vector3*)malloc(sizeof(Vector3) * m_numVertices);

		if (vertices != nullptr)
		{
			memcpy(vertices, mesh->mVertices, sizeof(Vector3) * m_numVertices);
		}

		m_numIndices = 3 * mesh->mNumFaces;
		indices = new unsigned int[m_numIndices];

		for (unsigned int i = 0; i < mesh->mNumFaces; ++i)
		{
			aiFace face = mesh->mFaces[i];
			memcpy(indices + i * 3, face.mIndices, sizeof(unsigned int) * face.mNumIndices);
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
