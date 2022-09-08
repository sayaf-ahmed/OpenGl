#pragma once
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "mesh.h"
class model
{
private:
	std::vector<texture*>m_loadedTextures;
	std::vector<mesh*> m_meshes;
	std::vector<std::string> m_loadedPaths;
	std::string m_directory;
public:

	model(const char* path);

	void draw(shader* s);
	~model();

private:
	std::vector<texInfo> loadTexture(aiMaterial* mat, aiTextureType texType, std::string textureName);
	void processNode(aiNode* node, const aiScene* scene);
	void processMesh(aiMesh* m, const aiScene* scene);

	void loadModel(const std::string& path);
	int isLoaded(const char* path);

};