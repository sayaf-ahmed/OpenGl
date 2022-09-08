#include "shader.h"
#include "glad/glad.h"
#include <glm/gtc/type_ptr.hpp>
shader::shader(const char* name)
{
	m_id = 0;
	m_name = name;
}

shader::shader(const shaderUnit& vs, const shaderUnit& fs, const char* name)
{
	m_name = name;
	loadMin(vs, fs);
}

void shader::loadMin(const shaderUnit& vs, const shaderUnit& fs)
{
	if (m_id != 0)
		glDeleteProgram(m_id);

	m_id = glCreateProgram();
	glAttachShader(m_id, vs.m_id);
	glAttachShader(m_id, fs.m_id);
	glLinkProgram(m_id);
	checkError();
}

void shader::loadComplete(const shaderUnit& vs, const shaderUnit& fs, const shaderUnit& gs, const shaderUnit& cs)
{
	if (m_id != 0)
		glDeleteProgram(m_id);

	m_id = glCreateProgram();
	glAttachShader(m_id, vs.m_id);
	glAttachShader(m_id, gs.m_id);
	glAttachShader(m_id, fs.m_id);
	if(cs.m_id !=0)
		glAttachShader(m_id, cs.m_id);
	glLinkProgram(m_id);
	checkError();

}

void shader::setUniform1f(const char* name, float value)
{
	int location = locateUniform(name);
	glUniform1f(location, value);
}

void shader::setUniform2f(const char* name, glm::vec2 value)
{
	int location = locateUniform(name);
	glUniform2f(location, value.x, value.y);
}

void shader::setUniform3f(const char* name, glm::vec3 value)
{
	int location = locateUniform(name);
	glUniform3f(location, value.x, value.y, value.z);
}

void shader::setUniform4f(const char* name, glm::vec4 value)
{
	int location = locateUniform(name);
	glUniform4f(location, value.x, value.y, value.z, value.w);
}

void shader::setUniform1i(const char* name, int value)
{
	int location = locateUniform(name);
	glUniform1i(location, value);
}

void shader::setUniform2i(const char* name, glm::ivec2 value)
{
	int location = locateUniform(name);
	glUniform2i(location, value.x, value.y);
}

void shader::setUniform3i(const char* name, glm::ivec3 value)
{
	int location = locateUniform(name);
	glUniform3i(location, value.x, value.y, value.z);
}

void shader::setUniform4i(const char* name, glm::ivec4 value)
{
	int location = locateUniform(name);
	glUniform4i(location, value.x, value.y, value.z, value.w);
}

void shader::setUniformMat2x2(const char* name, const glm::mat2x2& mat)
{
	int location = locateUniform(name);
	glUniformMatrix2fv(location, 1, GL_FALSE, glm::value_ptr(mat));
}

void shader::setUniformMat2x3(const char* name, const glm::mat2x3& mat)
{
	int location = locateUniform(name);
	glUniformMatrix2x3fv(location, 1, GL_FALSE, glm::value_ptr(mat));
}

void shader::setUniformMat2x4(const char* name, const glm::mat2x4& mat)
{
	int location = locateUniform(name);
	glUniformMatrix2x4fv(location, 1, GL_FALSE, glm::value_ptr(mat));
}

void shader::setUniformMat3x2(const char* name, const glm::mat3x2& mat)
{
	int location = locateUniform(name);
	glUniformMatrix3x2fv(location, 1, GL_FALSE, glm::value_ptr(mat));
}

void shader::setUniformMat3x3(const char* name, const glm::mat3x3& mat)
{
	int location = locateUniform(name);
	glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(mat));
}

void shader::setUniformMat3x4(const char* name, const glm::mat3x4& mat)
{
	int location = locateUniform(name);
	glUniformMatrix3x4fv(location, 1, GL_FALSE, glm::value_ptr(mat));
}

void shader::setUniformMat4x2(const char* name, const glm::mat4x2& mat)
{
	int location = locateUniform(name);
	glUniformMatrix4x2fv(location, 1, GL_FALSE, glm::value_ptr(mat));
}

void shader::setUniformMat4x3(const char* name, const glm::mat4x3& mat)
{
	int location = locateUniform(name);
	glUniformMatrix4x3fv(location, 1, GL_FALSE, glm::value_ptr(mat));
}

void shader::setUniformMat4x4(const char* name, const glm::mat4x4& mat)
{
	int location = locateUniform(name);
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat));
}

void shader::use() const
{
	glUseProgram(m_id);
}

shader::~shader()
{
	if(m_id != 0)
		glDeleteProgram(m_id);
}

int shader::locateUniform(const char* name)
{
	glUseProgram(m_id);
	int location = glGetUniformLocation(m_id, name);
	if (location == -1)
	{
		std::cout << "shaderError in " << m_name << " : the uniform " << name << " was not found\n";
		return -1;
	}
	return location;
}

void shader::checkError() const
{
	int linkSuccess = true;
	glGetProgramiv(m_id, GL_LINK_STATUS, &linkSuccess);

	if (!linkSuccess)
	{
		int len = 0;
		glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &len);
		char* infoLog = new char[len];
		glGetProgramInfoLog(m_id, len, NULL, infoLog);
		std::cout << "shaderError in " << m_name<< ": failed to compile with the following error > " << infoLog << "\n";
		delete[] infoLog;
	}
}
