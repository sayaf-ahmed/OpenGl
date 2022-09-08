#include "vertexAttributeList.h"

void vertexAttributeList::addFloats(int count, int index)
{

	vertexAttribute newAttribute;
	newAttribute.offset = m_offset;
	newAttribute.stride = m_stride + count * sizeof(float);
	newAttribute.count = count;
	newAttribute.isFloat = true;
	if (index >= 0)
		newAttribute.m_index = index;
	else
		newAttribute.m_index = -1;

	m_stride += count * sizeof(float);
	for (vertexAttribute& v : attributes)
	{
		v.stride = m_stride;
	}

	m_offset += count * sizeof(float);

	attributes.push_back(newAttribute);
}

void vertexAttributeList::addInts(int count, int index)
{
	vertexAttribute newAttribute;
	newAttribute.offset = m_offset;
	newAttribute.stride = m_stride + count * sizeof(int);
	newAttribute.count = count;
	newAttribute.isFloat = true;
	if (index >= 0)
		newAttribute.m_index = index;
	else
		newAttribute.m_index = -1;
	m_stride += count * sizeof(int);
	for (vertexAttribute& v : attributes)
	{
		v.stride = m_stride;
	}

	m_offset += count * sizeof(int);

	attributes.push_back(newAttribute);
}