#include "vertexArray.h"

vertexArray::vertexArray()
{
	glGenVertexArrays(1, &m_id);
}

void vertexArray::addVertexBuffer(const bufferObject& VBO, const vertexAttributeList& attributeList)
{
	use();
	VBO.use();
	for (int i = 0; i < attributeList.attributes.size(); i++)
	{
		GLenum type = attributeList.attributes.at(i).isFloat == true ? GL_FLOAT : GL_INT;
		int index = attributeList.attributes.at(i).m_index >= 0 ? attributeList.attributes.at(i).m_index : i;
		glVertexAttribPointer(index, attributeList.attributes.at(i).count, type,
			GL_FALSE, attributeList.attributes.at(i).stride, (const void*)attributeList.attributes.at(i).offset);
		glEnableVertexAttribArray(index);
	}

	glBindVertexArray(0);
	glBindBuffer((GLenum)bufferType::vertexBuffer, 0);
}

void vertexArray::addIndexBuffer(const bufferObject& IBO)
{
	use();
	IBO.use();

	glBindVertexArray(0);
	glBindBuffer((GLenum)bufferType::indexBuffer, 0);
}

void vertexArray::use() const
{
	glBindVertexArray(m_id);
}

vertexArray::~vertexArray()
{
	if (m_id != 0)
		glDeleteVertexArrays(1, &m_id);
}
