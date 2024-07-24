#include "ModelImporter.h"
#include "Mesh.h"
#include "DDSReader.h"

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

Axiom::Mesh* Axiom::ProcessMesh(aiMesh* srcMesh, const aiScene* scene)
{
	Mesh* dstMesh = new Mesh();
	dstMesh->m_numVertices = srcMesh->mNumVertices;

	dstMesh->m_vertices = (Vector3*)malloc(sizeof(Vector3) * dstMesh->m_numVertices);
	dstMesh->m_normals = (Vector3*)malloc(sizeof(Vector3) * dstMesh->m_numVertices);
	dstMesh->m_textureCoords = (Vector2*)malloc(sizeof(Vector2) * dstMesh->m_numVertices);

	for (unsigned int i = 0; i < dstMesh->m_numVertices; ++i)
	{
		// Cache mesh attributes.
		aiVector3D pos = srcMesh->mVertices[i];
		aiVector3D norm = srcMesh->mNormals[i];
		aiVector3D texCoord = srcMesh->mTextureCoords[0][i];

		// Copy positions.
		dstMesh->m_vertices[i].Set(pos.x, pos.y, pos.z);

		// Copy normals.
		dstMesh->m_normals[i].Set(norm.x, norm.y, norm.z);

		// Copy texture coords.
		dstMesh->m_textureCoords[i].Set(texCoord.x, texCoord.y);
	}

	// Copy indices.
	dstMesh->m_numIndices = 3 * srcMesh->mNumFaces;
	dstMesh->m_indices = new unsigned int[dstMesh->m_numIndices];

	for (unsigned int i = 0; i < srcMesh->mNumFaces; ++i)
	{
		aiFace face = srcMesh->mFaces[i];
		memcpy(dstMesh->m_indices + i * 3, face.mIndices, sizeof(unsigned int) * face.mNumIndices);
	}

	// Copy materials.

	// Copy embedded textures.
	if (scene->HasTextures())
	{
		for (unsigned int i = 0; i < scene->mNumTextures; ++i)
		{
			aiTexture* texture = scene->mTextures[i];
			if (texture->mHeight == 0)
			{
				// Compressed
				if (texture->achFormatHint == "dds")
				{
					// Decode dds texture.
					//DecodeHeader();
				}

				if (texture->achFormatHint == "jpg")
				{
					
				}
			}
			else
			{
				// Uncompressed
			}
		}
	}

	return dstMesh;
}
