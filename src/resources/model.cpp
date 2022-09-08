#include "model.h"

model::model(const char* path)
{
	loadModel(path);
}

void model::draw(shader* s)
{
	for (int i = 0; i < m_meshes.size(); i++)
		m_meshes[i]->draw(s, m_loadedTextures);
}

std::vector<texInfo> model::loadTexture(aiMaterial* mat, aiTextureType texType, std::string textureName)
{
	textureProperties genericProps;
	genericProps.type = textureDimensions::texture_2D;
	genericProps.minFilter = textureMinFiltering::linearMipMapNearest;
	genericProps.magFilter = textureMagFiltering::linear;
	genericProps.useMipMap = true;
	genericProps.wrapS = textureWrapping::edgeClamp;
	genericProps.wrapT = textureWrapping::edgeClamp;

	std::vector<texInfo> textureInfos;
	int count = mat->GetTextureCount(texType);

	int start = (int)m_loadedTextures.size();

	for (int i = 0; i < count; i++)
	{
		aiString texPath;
		mat->GetTexture(texType, i, &texPath);

		texInfo t;
		std::string str = texPath.C_Str();

		int textureIndex = isLoaded((m_directory + "/" + str).c_str());

		if (textureIndex >= 0)
		{
			t.path = m_directory + "/" + texPath.C_Str();
			t.textureIndex = textureIndex;
			t.type = textureName;
		}
		else
		{
			
			texture* Texture = new texture((m_directory + "/" + texPath.C_Str()).c_str(), genericProps);
			t.path = (m_directory + "/" + texPath.C_Str());
			t.textureIndex = start + i;
			t.type = textureName;
			m_loadedTextures.push_back(Texture);
			m_loadedPaths.push_back(t.path);
			textureInfos.push_back(t);
		}

	}

	return textureInfos;
	
}

void model::processNode(aiNode* node, const aiScene* scene)
{
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* m = scene->mMeshes[node->mMeshes[i]];
		processMesh(m, scene);
	}

	for (unsigned int j = 0; j < node->mNumChildren; j++)
	{
		aiNode* n = node->mChildren[j];
		processNode(n, scene);
	}
}

void model::processMesh(aiMesh* m, const aiScene* scene)
{
	std::vector<vertex> verts;
	std::vector<unsigned int> ind;
	std::vector<texInfo> textureInfos;

	for (unsigned int i = 0; i < m->mNumVertices; i++)
	{
		aiVector3D position = m->mVertices[i], normal = m->mNormals[i];
		aiVector3D uv;
		if (m->mTextureCoords[0])
			uv = m->mTextureCoords[0][i];
		vertex v;
		v.position = { position.x, position.y, position.z };
		v.normal = { normal.x, normal.y, normal.z };
		v.uv = { uv.x, uv.y };
		verts.push_back(v);
	}


	for (int i = 0; i < m->mNumFaces; i++)
	{
		aiFace f = m->mFaces[i];

		for (int j = 0; j < f.mNumIndices; j++)
			ind.push_back(f.mIndices[j]);
	}

	if (m->mMaterialIndex >= 0)
	{
		aiMaterial* mat = scene->mMaterials[m->mMaterialIndex];

		std::vector<texInfo> diff = loadTexture(mat, aiTextureType_DIFFUSE, "texture_diffuse");
		std::vector<texInfo> spec = loadTexture(mat, aiTextureType_SPECULAR, "texture_specular");

		textureInfos.insert(textureInfos.end(), diff.begin(), diff.end());
		textureInfos.insert(textureInfos.end(), spec.begin(), spec.end());
	}

	mesh* Mesh = new mesh(verts, ind, textureInfos);

	m_meshes.push_back(Mesh);
}

void model::loadModel(const std::string& path)
{
	Assimp::Importer importer; 

	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
		return;
	}
	m_directory = path.substr(0, path.find_last_of('/'));

	processNode(scene->mRootNode, scene);
}

int model::isLoaded(const char* path)
{
	for (int i = 0; i < m_loadedPaths.size(); i++)
	{
		if (strcmp(path, m_loadedPaths[i].c_str()) <=0)
			return i;
	}

	return -1;
}

model::~model()
{
	for (int i = 0; i < m_loadedTextures.size(); i++)
		delete m_loadedTextures[i];

	for (int i = 0; i < m_meshes.size(); i++)
		delete m_meshes[i];
}
