#include "directionalLight.h"

directionalLight::directionalLight(glm::vec3 position, glm::vec3 rotation, const glm::vec3& direction)
	:light(position, rotation), m_direction(direction)
{
}

void directionalLight::setDirection(const glm::vec3& newDirection)
{
	m_direction = newDirection;
}

glm::vec3 directionalLight::getDirection() const
{
	return m_direction;
}
