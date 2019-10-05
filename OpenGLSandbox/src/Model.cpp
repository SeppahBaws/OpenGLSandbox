#include "pch.h"
#include "Model.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

Model::Model(const std::string& path)
{
	LoadMesh(path);
}

void Model::LoadMesh(const std::string& path)
{
	Assimp::Importer importer;

	const aiScene* pScene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
		// aiProcess_CalcTangentSpace | aiProcess_Triangulate |
		// aiProcess_JoinIdenticalVertices | aiProcess_SortByPType);

	if (!pScene || pScene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !pScene->mRootNode)
	{
		LOG_ERROR("Assimp Error: {0}", importer.GetErrorString());
		return;
	}

	LOG_INFO("Assimp model import successful!");

	ProcessNode(pScene->mRootNode, pScene);
}

void Model::ProcessNode(aiNode* pNode, const aiScene* pScene)
{
	// Process meshes
	for (unsigned int i = 0; i < pNode->mNumMeshes; i++)
	{
		aiMesh* pMesh = pScene->mMeshes[pNode->mMeshes[i]];
		m_Meshes.push_back(ProcessMesh(pMesh, pScene));
	}

	// Process sub-nodes
	for (unsigned int i = 0; i < pNode->mNumChildren; i++)
	{
		ProcessNode(pNode->mChildren[i], pScene);
	}
}

Mesh Model::ProcessMesh(aiMesh* pMesh, const aiScene* pScene)
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	// Vertices
	for (unsigned int i = 0; i < pMesh->mNumVertices; i++)
	{
		Vertex vertex{};
		vertex.position = { pMesh->mVertices[i].x, pMesh->mVertices[i].y, pMesh->mVertices[i].z };
		vertex.normal = { pMesh->mNormals[i].x, pMesh->mNormals[i].y, pMesh->mNormals[i].z };

		if (pMesh->mTextureCoords[0])
		{
			vertex.texCoord = { pMesh->mTextureCoords[0][i].x, pMesh->mTextureCoords[0][i].y };
		}
		else
		{
			LOG_WARN("Mesh: UV Coordinates not found! Defaulting to (0, 0)");
			vertex.texCoord = { 0.0f, 0.0f };
		}

		vertices.push_back(vertex);
	}

	// Indices
	for (unsigned int i = 0; i < pMesh->mNumFaces; i++)
	{
		aiFace face = pMesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}
	
	return Mesh{vertices, indices};
}
