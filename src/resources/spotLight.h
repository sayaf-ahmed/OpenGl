#pragma once
#include "pointLight.h"

class spotLight : public pointLight 
{
private:
	glm::vec3 m_direction;
	float m_innerCutOff, m_outerCutOff;


public:
	spotLight(glm::vec3 position = { 0, 0, 0 }, glm::vec3 rotation = { 0, 0, 0 }, const glm::vec3& direction = { 0, 0, -1 },
		float innerAngle = 12.5f, float outerAngle = 17.5f);

	void setInnerAngle(float angle);
	void setOuterAngle(float angle);
	void  setDirection(const glm::vec3& newDirection);

	glm::vec3 getDirection() const;
	float getInnerAngle() const;
	float getOuterAngle() const;

	float getInnerCutOff() const;
	float getOuterCutOff() const;



};

