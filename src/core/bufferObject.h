#pragma once
#include <glad/glad.h>
enum class bufferType
{
	none = -1,
	vertexBuffer = 0x8892,
	indexBuffer = 0x8893,
	uniformBuffer = 0x8A11

};

enum class dataUsage
{
	staticDraw = 0x88E4, 
	staticRead = 0x88E5, 
	staticCopy = 0x88E6, 
	dynamicDraw = 0x88E8,
	dynamicRead = 0x88E9,
	dynamicCopy = 0x88EA
	
};
class bufferObject
{
private:
	unsigned int m_id;
	bufferType m_type;
	int m_size;
public:


	bufferObject(bufferType type);

	void loadData(const void* data, const size_t dataSize, dataUsage usage);

	void use() const;

	void destroy();

	int getSize() const;

	~bufferObject();


	friend class vertexArray;
	
};

