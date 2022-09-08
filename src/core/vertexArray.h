#pragma once
#include "bufferObject.h"
#include "vertexAttributeList.h"

class vertexArray
{
private:
	unsigned int m_id;

public:
	vertexArray();

	void addVertexBuffer(const bufferObject& VBO, const vertexAttributeList& attributeList);

	void addIndexBuffer(const bufferObject& IBO);

	void use() const;

	~vertexArray();
};

