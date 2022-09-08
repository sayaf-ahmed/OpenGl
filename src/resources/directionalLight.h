#pragma once
#include "light.h"
class directionalLight: public light
{
private:
	glm::vec3 m_direction;

public:
	directionalLight(glm::vec3 position = { 0, 0, 0 }, glm::vec3 rotation = { 0, 0, 0 }, const glm::vec3& direction = {0, -1, 0});
	void setDirection(const glm::vec3& newDirection);
	glm::vec3 getDirection()const;
};

