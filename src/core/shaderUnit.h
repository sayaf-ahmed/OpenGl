#pragma once
#include <iostream>
enum class shaderType
{
	vertex = 0x8b31,
	fragment = 0x8b30,
	geometry = 0x8dd9,
	compute = 0x91b9
};
class shaderUnit
{
private:
	unsigned int m_id = 0;
	shaderType m_type;
public:
	shaderUnit();
	shaderUnit(const char* shaderFile, shaderType type);

	void load(const char* shaderFile, shaderType type);

	void destroy();

	~shaderUnit();
private:
	std::string loadSource(const char* filePath);

	void checkErrors();

	friend class shader;
};

