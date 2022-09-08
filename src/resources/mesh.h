#pragma once
#include "../core/vec.h"
#include <string>
#include <vector>
#include "../resources/shader.h"
#include "../core/bufferObject.h"
#include "../core/vertexArray.h"
#include "../resources/texture.h"
struct vertex
{
	glm::vec3 position, normal;
	glm::vec2 uv;
};

struct texInfo
{
	unsigned int textureIndex = -1;
	std::string type = "";
	std::string path = "";
};
class mesh
{
private:
	std::vector<vertex>m_vertices;
	std::vector<unsigned int> m_indices;
	std::vector<texInfo> m_textureIndices;
	vertexArray m_vao;
	bufferObject m_vbo = bufferObject(bufferType::vertexBuffer),
	      	     m_ibo = bufferObject(bufferType::indexBuffer);

public:
	mesh(const std::vector<vertex>&verts, const std::vector<unsigned int>& indices,
		 const std::vector<texInfo>& textures);


	void draw(shader* s, const std::vector<texture*>loadedTextures)const;
private:
	void setUp();
};

