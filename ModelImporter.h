#ifndef MODEL_IMPORTER_H
#define MODEL_IMPORTER_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Axiom
{
	class Mesh;

	void LoadModel(const char* fileName);
	void ProcessNode(aiNode* node, const aiScene* scene, Mesh* meshes);
	Mesh* ProcessMesh(aiMesh* mesh, const aiScene* scene);
}

#endif // !MODEL_IMPORTER_H
