#include "Mesh.h"
#include "ModelImporter.h"

void Axiom::LoadModel(const char* fileName)
{
	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(fileName,
		aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType);

	if (scene != nullptr)
	{
		Mesh* meshes = nullptr;
		ProcessNode(scene->mRootNode, scene, meshes);
	}
}

void Axiom::ProcessNode(aiNode* node, const aiScene* scene, Mesh* meshes)
{
	for (unsigned int i = 0; i < node->mNumMeshes; ++i)
	{
		// Process geometry.
		meshes = ProcessMesh(scene->mMeshes[node->mMeshes[i]], scene);
	}

	for (unsigned int i = 0; i < node->mNumChildren; ++i)
	{
		aiNode* child = node->mChildren[i];
		ProcessNode(child, scene, meshes);
	}
}

Axiom::Mesh* Axiom::ProcessMesh(aiMesh* assimpMesh, const aiScene* scene)
{
	Mesh* mesh = new Mesh();
	mesh->m_numVertices = assimpMesh->mNumVertices;
	mesh->m_vertices = (Vector3*)malloc(sizeof(Vector3) * mesh->m_numVertices);

	// Copy vertices.
	if (mesh->m_vertices != nullptr)
	{
		memcpy(mesh->m_vertices, assimpMesh->mVertices, sizeof(Vector3) * mesh->m_numVertices);
	}

	// Copy indices.
	mesh->m_numIndices = 3 * assimpMesh->mNumFaces;
	mesh->m_indices = new unsigned int[mesh->m_numIndices];

	for (unsigned int i = 0; i < assimpMesh->mNumFaces; ++i)
	{
		aiFace face = assimpMesh->mFaces[i];
		memcpy(mesh->m_indices + i * 3, face.mIndices, sizeof(unsigned int) * face.mNumIndices);
	}

	// Copy normals.
	if (assimpMesh->mNormals != nullptr)
	{
		mesh->m_normals = (Vector3*)malloc(sizeof(Vector3) * mesh->m_numVertices);
		if (mesh->m_normals != nullptr)
		{
			memcpy(mesh->m_normals, assimpMesh->mNormals, sizeof(Vector3) * mesh->m_numVertices);
		}
	}

	// Copy UV coords.

	return mesh;
}
