#include "light.h"
#include <glm/gtc/matrix_transform.hpp>

light::light(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
	:m_position(position), m_rotation(rotation), m_scale(scale)
{
	m_updateMat = true;
}

void light::setPosition(const glm::vec3& newPosition)
{
	m_position = newPosition;
	m_updateMat = true;

}

void light::setRotation(const glm::vec3& newRotation)
{
	m_rotation = newRotation;
	m_updateMat = true;

}

void light::setScale(const glm::vec3& newScale)
{
	m_scale = newScale;
	m_updateMat = true;
}

void light::setColor(const glm::vec3& color)
{
	m_diffuse = glm::vec3(0.5) * color;
	m_ambient = glm::vec3(0.2) * m_diffuse;
	m_specular = color;
	m_color = color;

}

glm::vec3 light::getPosition() const
{
	return m_position;
}

glm::vec3 light::getRotation() const
{
	return m_rotation;
}

glm::vec3 light::getColor() const
{
	return m_color;
}

glm::vec3 light::getAmbient() const
{
	return m_ambient;
}

glm::vec3 light::getDiffuse() const
{
	return m_diffuse;
}

glm::vec3 light::getSpecular() const
{
	return m_specular;
}

glm::mat4x4 light::getMatrix()
{
	if (m_updateMat)
		updateMatrix();
	return m_modelMat;
}

void light::updateMatrix()
{
	glm::mat4x4 scale = glm::scale(glm::mat4x4(1.0), m_scale);

	glm::mat4x4 rotX = glm::rotate(glm::mat4x4(1.0), m_rotation.x, {1, 0, 0});
	glm::mat4x4 rotY = glm::rotate(glm::mat4x4(1.0), m_rotation.y, {0, 1, 0});
	glm::mat4x4 rotZ = glm::rotate(glm::mat4x4(1.9), m_rotation.z, {0, 0, 1});

	glm::mat4x4 trans = glm::translate(glm::mat4x4(1.0), m_position);

	m_modelMat = trans * scale;
}
