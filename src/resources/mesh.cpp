#include "mesh.h"

mesh::mesh(const std::vector<vertex>& verts, const std::vector<unsigned int>& indices, const std::vector<texInfo>& textures)
{
	m_vertices = verts;
	m_indices = indices;
	m_textureIndices = textures;
	setUp();
}

void mesh::draw(shader* s, const std::vector<texture*> loadedTextures) const
{
	s->use();
	int diffNum = 0 , specNum = 0;
	for (int i = 0; i < m_textureIndices.size(); i++)
	{
		std::string texNum;
		std::string texType;

		texInfo t = m_textureIndices[i];
		texture* tex = loadedTextures[t.textureIndex];
		tex->use(i);
		if (t.type == "texture_diffuse")
			texNum = std::to_string(diffNum++);
		else
			texNum = std::to_string(specNum++);
		texType = t.type;

		s->setUniform1i(("objMaterial." + texType + texNum).c_str(), i);
	}
	m_vao.use();
	glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, NULL);
}

void mesh::setUp()
{
	vertexAttributeList vboLayout;
	vboLayout.addFloats(3, -1);
	vboLayout.addFloats(3, -1);
	vboLayout.addFloats(2, -1);
	m_vao.use();
	m_vbo.loadData(&m_vertices[0], m_vertices.size() * sizeof(vertex), dataUsage::staticDraw);
	m_ibo.loadData(&m_indices[0], m_indices.size() * sizeof(unsigned int), dataUsage::staticDraw);
	m_vao.addVertexBuffer(m_vbo, vboLayout);
	m_vao.addIndexBuffer(m_ibo);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}
