#pragma once

#include "Mesh.h"

struct aiNode;
struct aiMesh;
struct aiScene;

class Model
{
public:
	Model(const std::string& path);

	inline std::vector<Mesh> GetMeshes() const { return m_Meshes; }
	
private:
	void LoadMesh(const std::string& path);
	void ProcessNode(aiNode* pNode, const aiScene* pScene);
	Mesh ProcessMesh(aiMesh* pMesh, const aiScene* pScene);

private:
	std::vector<Mesh> m_Meshes;
};
