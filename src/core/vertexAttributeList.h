#pragma once
#include <vector>

class vertexAttributeList
{
private:
	int m_offset = 0;
	int m_stride = 0;
	struct vertexAttribute
	{
		int offset = 0;
		int stride = 0;
		int count = 0;
		bool isFloat = 0;
		int m_index;
	};

	std::vector<vertexAttribute> attributes;
public:
	vertexAttributeList()
	{}

	void addFloats(int count, int index);
	void addInts(int count, int index);

	friend class vertexArray;
};