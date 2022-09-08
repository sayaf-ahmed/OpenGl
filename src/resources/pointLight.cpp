#include "pointLight.h"

pointLight::pointLight(glm::vec3 position, glm::vec3 rotation, float constant, float linear, float quad)
	:light(position, m_rotation), m_constant(constant), m_linear(linear), m_quadratic(quad)
{
}

void pointLight::setConstant(float value) 
{
	m_constant = value;
}

void pointLight::setLinear(float value) 
{
	m_linear = value;
}

void pointLight::setQuadratic(float value) 
{
	m_quadratic = value;
}

float pointLight::getConstant() const
{
	return m_constant;
}

float pointLight::getLinear() const
{
	return m_linear;
}

float pointLight::getQuadratic() const
{
	return m_quadratic;
}
