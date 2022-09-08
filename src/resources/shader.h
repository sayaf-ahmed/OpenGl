#pragma once
#include "../core/shaderUnit.h"
#include "../core/vec.h"
#include "../core/mat.h"

class shader
{
private:
	unsigned int m_id;
	const char* m_name;

public:
	shader(const char* name);

	shader(const shaderUnit& vs, const shaderUnit& fs, const char* name);

	void loadMin(const shaderUnit& vs, const shaderUnit& fs);

	void loadComplete(const shaderUnit& vs, const shaderUnit& fs, const shaderUnit& gs, const shaderUnit& cs);


	void setUniform1f(const char* name, float value);
	void setUniform2f(const char* name, glm::vec2 value);
	void setUniform3f(const char* name, glm::vec3 value);
	void setUniform4f(const char* name, glm::vec4 value);

	void setUniform1i(const char* name, int value);
	void setUniform2i(const char* name, glm::ivec2 value);
	void setUniform3i(const char* name, glm::ivec3 value);
	void setUniform4i(const char* name, glm::ivec4 value);

	void setUniformMat2x2 (const char* name, const glm::mat2x2& mat);
	void setUniformMat2x3 (const char* name, const glm::mat2x3& mat);
	void setUniformMat2x4 (const char* name, const glm::mat2x4& mat);
	void setUniformMat3x2 (const char* name, const glm::mat3x2& mat);
	void setUniformMat3x3 (const char* name, const glm::mat3x3& mat);
	void setUniformMat3x4 (const char* name, const glm::mat3x4& mat);
	void setUniformMat4x2 (const char* name, const glm::mat4x2& mat);
	void setUniformMat4x3 (const char* name, const glm::mat4x3& mat);
	void setUniformMat4x4 (const char* name, const glm::mat4x4& mat);


	void use() const;
	~shader();


private:
	int locateUniform(const char* name);
	void checkError()const;
};

