#pragma once
#include "texture.h"

class material
{
private:
	texture* m_diffuse, *m_specular, *m_emission;
	float m_shininess;

public:
	material(texture* diffuse = nullptr, texture* specular = nullptr, texture* emission = nullptr, float shininess = 0);

	void setDiffuse (texture* tex);
	void setSpecular(texture* tex);
	void setEmission(texture* tex);


	void setShininess(float shininess);

	float getShininess()const;

	void use();



};

