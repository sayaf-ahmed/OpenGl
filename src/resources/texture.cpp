#include "texture.h"
#include "stbi_image.h"
#include <iostream>

texture::texture()
	:width(0), height(0), channels(0), m_filePath((char*)"")
{
	m_id = 0;
}

texture::texture(const char* filePath, const textureProperties& props)
{
	load(filePath, props);
}

void texture::load(const char* filePath, const textureProperties& props)
{
	if (m_id == 0)
		destroy();
	glGenTextures(1, &m_id);

	m_filePath = new char[strlen(filePath) + 1];
	memcpy(m_filePath, filePath, strlen(filePath) + 1);
	m_properties = props;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* textureData = stbi_load(filePath, &width, &height, &channels, 0);
	if (textureData == NULL)
	{
		std::cout << "texture creation failed: the image (" << filePath << ") couldn't be found/opened\n";
		destroy();
		return;
	}
	GLenum format = 0;
	switch (channels)
	{
	case 1:
		format = GL_RED;
		break;
	case 2:
		format = GL_RG;
		break;
	case 3:
		format = GL_RGB;
		break;
	case 4:
		format = GL_RGBA;
		break;
	default:
		break;
	}
	glActiveTexture(GL_TEXTURE0);
	glBindTexture((GLenum)m_properties.type, m_id);
	switch (m_properties.type)
	{
	case textureDimensions::texture_1D:
		glTexImage1D(GL_TEXTURE_1D, 0, format, width, 0, format, GL_UNSIGNED_BYTE, textureData);
		break;
	case textureDimensions::texture_2D:
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, textureData);
		break;
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (GLenum)m_properties.wrapS);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (GLenum)m_properties.wrapT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (GLenum)m_properties.minFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (GLenum)m_properties.magFilter);


	if (m_properties.useBoarder)
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, m_properties.boarderCol);

	if (m_properties.useMipMap)
		glGenerateMipmap((GLenum)m_properties.type);


	stbi_image_free(textureData);

	glBindTexture((GLenum)m_properties.type, 0);

}

void texture::setProperties(const textureProperties& props)
{
	load(m_filePath, props);
}

void texture::create(int width, int height, const textureProperties& props)
{
	this->width = width;
	this->height = height;
	this->m_properties = props;
	glGenTextures(1, &m_id);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture((GLenum)m_properties.type, m_id);
	m_filePath = new char[20];
	switch (m_properties.type)
	{
	case textureDimensions::texture_1D:
		glTexImage1D(GL_TEXTURE_1D, 0, GL_RGB, width, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		break;
	case textureDimensions::texture_2D:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		break;
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (GLenum)m_properties.wrapS);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (GLenum)m_properties.wrapT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (GLenum)m_properties.minFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (GLenum)m_properties.magFilter);


	if (m_properties.useBoarder)
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, m_properties.boarderCol);

	if (m_properties.useMipMap)
		glGenerateMipmap((GLenum)m_properties.type);



	glBindTexture((GLenum)m_properties.type, 0);
}

void texture::createDepthTexture(int width, int height, const textureProperties& props)
{
	this->width = width;
	this->height = height;
	this->m_properties = props;
	glGenTextures(1, &m_id);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture((GLenum)m_properties.type, m_id);
	m_filePath = new char[20];
	switch (m_properties.type)
	{
	case textureDimensions::texture_1D:
		glTexImage1D(GL_TEXTURE_1D, 0, GL_DEPTH_COMPONENT24, width, 0, GL_DEPTH_COMPONENT24, GL_UNSIGNED_INT, NULL);
		break;
	case textureDimensions::texture_2D:
		glTexImage2D(GL_TEXTURE_2D, 0,	GL_DEPTH_COMPONENT24, width, height, 0, GL_DEPTH_COMPONENT24, GL_UNSIGNED_INT, NULL);
		break;
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (GLenum)m_properties.wrapS);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (GLenum)m_properties.wrapT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (GLenum)m_properties.minFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (GLenum)m_properties.magFilter);


	if (m_properties.useBoarder)
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, m_properties.boarderCol);

	if (m_properties.useMipMap)
		glGenerateMipmap((GLenum)m_properties.type);



	glBindTexture((GLenum)m_properties.type, 0);
}

void texture::createStencilTexture(int width, int height, const textureProperties& props)
{
	this->width = width;
	this->height = height;
	this->m_properties = props;
	glGenTextures(1, &m_id);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture((GLenum)m_properties.type, m_id);
	m_filePath = new char[20];
	switch (m_properties.type)
	{
	case textureDimensions::texture_1D:
		glTexImage1D(GL_TEXTURE_1D, 0, GL_STENCIL_INDEX8, width, 0, GL_STENCIL_INDEX8, GL_UNSIGNED_BYTE, NULL);
		break;
	case textureDimensions::texture_2D:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_STENCIL_INDEX8, width, height, 0, GL_STENCIL_INDEX8, GL_UNSIGNED_BYTE, NULL);
		break;
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (GLenum)m_properties.wrapS);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (GLenum)m_properties.wrapT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (GLenum)m_properties.minFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (GLenum)m_properties.magFilter);


	if (m_properties.useBoarder)
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, m_properties.boarderCol);

	if (m_properties.useMipMap)
		glGenerateMipmap((GLenum)m_properties.type);



	glBindTexture((GLenum)m_properties.type, 0);
}

void texture::createCombineDepthStencil(int width, int height, const textureProperties& props)
{
	this->width = width;
	this->height = height;
	this->m_properties = props;

	glGenTextures(1, &m_id);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture((GLenum)m_properties.type, m_id);
	m_filePath = new char[20];
	switch (m_properties.type)
	{
	case textureDimensions::texture_1D:
		glTexImage1D(GL_TEXTURE_1D, 0, GL_DEPTH24_STENCIL8, width, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
		break;
	case textureDimensions::texture_2D:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, width, height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
		break;
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (GLenum)m_properties.wrapS);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (GLenum)m_properties.wrapT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (GLenum)m_properties.minFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (GLenum)m_properties.magFilter);


	if (m_properties.useBoarder)
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, m_properties.boarderCol);

	if (m_properties.useMipMap)
		glGenerateMipmap((GLenum)m_properties.type);



	glBindTexture((GLenum)m_properties.type, 0);
}

void texture::use(int slot)
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture((GLenum)m_properties.type, m_id);
}

void texture::destroy()
{
	glDeleteTextures(1, &m_id);
	m_id = 0;
}

unsigned int texture::getId() const
{
	return m_id;
}

texture::~texture()
{
	if(m_id!=0)
		glDeleteTextures(1, &m_id);
	delete[] m_filePath;
}
