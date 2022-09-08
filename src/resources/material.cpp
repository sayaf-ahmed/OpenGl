#include "material.h"

material::material(texture* diffuse, texture* specular, texture* emission, float shininess)
	:m_diffuse(diffuse), m_specular(specular), m_emission(emission), m_shininess(shininess)
{
}

void material::setDiffuse(texture* tex)
{
	m_diffuse = tex;
}

void material::setSpecular(texture* tex)
{
	m_specular = tex;
}

void material::setEmission(texture* tex)
{
	m_emission = tex;
}

void material::setShininess(float shininess)
{
	m_shininess = shininess;
}

float material::getShininess() const
{
	return m_shininess;
}

void material::use()
{
	if (m_diffuse != nullptr)
		m_diffuse->use(0);

	if (m_specular != nullptr)
		m_specular->use(1);

	if (m_emission != nullptr)
		m_emission->use(2);
}
