#include "shaderUnit.h"
#include <fstream>
#include <sstream>
#include <glad/glad.h>

shaderUnit::shaderUnit()
{
    m_id = 0;
}

shaderUnit::shaderUnit(const char* shaderFile, shaderType type)
{
    load(shaderFile, type);
    m_type = type;
}

void shaderUnit::load(const char* shaderFile, shaderType type)
{
    m_type = type;
    std::string sourceString = loadSource(shaderFile);

    const char* source = sourceString.c_str();


    m_id = glCreateShader((GLenum)type);
    glShaderSource(m_id, 1, &source, NULL);
    glCompileShader(m_id);
    checkErrors();

}

void shaderUnit::destroy()
{
    glDeleteShader(m_id);
    m_id = 0;
}

shaderUnit::~shaderUnit()
{
    if(m_id != 0)
        destroy();
}

std::string shaderUnit::loadSource(const char* filePath)
{

    std::ifstream file(filePath);
    std::stringstream source;

    if (!file.is_open())
    {
        std::cout << "couldn't open file " << filePath << "\n";
        return std::string("");
    }

    char line[300];

    while (file.getline(line, 300))
    {
        source << line << "\n";
    }

    file.close();
    return source.str();
}

void shaderUnit::checkErrors()
{
    int compileSuccess = true;
    glGetShaderiv(m_id, GL_COMPILE_STATUS, &compileSuccess);

    const char* t = (m_type == shaderType::vertex) ? "vertexShader" : "fragmetShader";

    if (!compileSuccess)
    {
        int len = 0;
        glGetShaderiv(m_id, GL_INFO_LOG_LENGTH, &len);
        char* infoLog = new char[len];
        glGetShaderInfoLog(m_id, len, NULL, infoLog);
        std::cout << "shader unit ( "<< t << ")with id " << m_id << ": failed to compile with the following error " << infoLog << "\n";
        delete[] infoLog;
    }
    
}

