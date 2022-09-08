#include "bufferObject.h"



bufferObject::bufferObject(bufferType type)
	:m_type(type), m_size(0)
{
	glGenBuffers(1, &m_id);
}


void bufferObject::loadData(const void* data, const size_t dataSize, dataUsage usage)
{
	glBindBuffer((GLenum)m_type, m_id);
	glBufferData((GLenum)m_type, dataSize, data, (GLenum)usage);
	m_size = dataSize;
}

void bufferObject::use() const
{
	glBindBuffer((GLenum)m_type, m_id);
}

void bufferObject::destroy()
{
	glDeleteBuffers(1, &m_id);
	m_id = 0;
}

int bufferObject::getSize()const 
{
	return m_size;
}

bufferObject::~bufferObject()
{
	if(m_id !=0)
		glDeleteBuffers(1, &m_id);

}
