#include "spotLight.h"
#include "glm/glm.hpp"

spotLight::spotLight(glm::vec3 position, glm::vec3 rotation, const glm::vec3& direction, float innerAngle, float outerAngle)
	:pointLight(position, rotation), m_direction(direction)
{
	m_innerCutOff = glm::cos(glm::radians(innerAngle));
	m_outerCutOff = glm::cos(glm::radians(outerAngle));
}

void spotLight::setInnerAngle(float angle)
{
	m_innerCutOff = glm::cos(glm::radians(angle));
}

void spotLight::setOuterAngle(float angle)
{
	m_outerCutOff = glm::cos(glm::radians(angle));
}

void spotLight::setDirection(const glm::vec3& newDirection)
{
	m_direction = newDirection;
}

glm::vec3 spotLight::getDirection() const
{
	return m_direction;
}

float spotLight::getInnerAngle() const
{
	return glm::degrees(glm::acos(m_innerCutOff));
}

float spotLight::getOuterAngle() const
{
	return glm::degrees(glm::acos(m_outerCutOff));
}

float spotLight::getInnerCutOff() const
{
	return m_innerCutOff;
}

float spotLight::getOuterCutOff() const
{
	return m_outerCutOff;
}
