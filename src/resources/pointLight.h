#pragma once
#include "light.h"
class pointLight : public light
{
private:
	float m_constant, m_linear, m_quadratic;

public:
	pointLight(glm::vec3 position = { 0, 0, 0 }, glm::vec3 rotation = { 0, 0, 0 }, float constant = 1, float linear = 0.09f, float quad = 0.032f);

	void setConstant (float value);
	void setLinear   (float value);
	void setQuadratic(float value);




	float getConstant()const;
	float getLinear()const;
	float getQuadratic()const;

};

