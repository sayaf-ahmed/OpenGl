#include "object.h"
#include <glm/gtc/matrix_transform.hpp>

object::object(const glm::vec3& pos, const glm::vec3& scale, const glm::vec3& rot)
	:m_position(pos), m_scale(scale), m_rotation(rot), m_shader(nullptr), m_model(nullptr)
{
}

glm::vec3 object::getPosition() const
{
	return m_position;
}

glm::vec3 object::getScale() const
{
	return m_scale;
}

glm::vec3 object::getRotation() const
{
	return m_rotation;
}

void object::setPosition(const glm::vec3& newPos)
{
	m_position = newPos;
}

void object::setScale(const glm::vec3& newScale)
{
	m_scale = newScale;
}

void object::setRotation(const glm::vec3& newRotation)
{
	m_rotation = newRotation;
}

void object::setShader(shader* shader)
{
	m_shader = shader;
}

void object::setModel( model* mod)
{
	m_model = mod;
}

void object::draw() const
{
	m_model->draw(m_shader);
}

glm::mat4x4 object::getMatrix()
{
	if (bUpdateMatrix)
		updateMatrix();
	return m_modelMat;
}

object::~object()
{
}

void object::updateMatrix()
{
	glm::mat4x4 scale = glm::scale(glm::mat4x4(1.0), m_scale);
	glm::mat4x4 rotX = glm::rotate(glm::mat4x4(1.0), m_rotation.x, {1, 0, 0});
	glm::mat4x4 rotY = glm::rotate(glm::mat4x4(1.0), m_rotation.y, {0, 1, 0});
	glm::mat4x4 rotZ = glm::rotate(glm::mat4x4(1.0), m_rotation.z, {0, 0, 1});

	glm::mat4x4 translate = glm::translate(glm::mat4x4(1.0), m_position);


	m_modelMat = translate * rotZ * rotY * rotX * scale * m_modelMat;
	bUpdateMatrix = false;
}
