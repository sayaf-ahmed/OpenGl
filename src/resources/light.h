#pragma once
#include "../core/vec.h"
#include "../core/mat.h"
class light
{
private:
	bool m_updateMat = false;
protected:
	glm::vec3 m_position, m_rotation, m_scale;
	glm::vec3 m_ambient= {0.2, 0.2, 0.2}, m_diffuse = {0.5, 0.5, 0.5}, m_specular = {1.0, 1.0, 1.0};
	glm::vec3 m_color = { 1.0, 1.0, 1.0 };
	glm::mat4x4 m_modelMat = glm::mat4x4(1.0);

public:

	light(glm::vec3 position = { 0, 0, 0 }, glm::vec3 rotation = { 0, 0, 0 }, glm::vec3 scale = {1, 1, 1});

	void setPosition(const glm::vec3& newPosition);
	void setRotation(const glm::vec3& newRotation);
	void setScale(const glm::vec3& newScale);

	void setColor(const glm::vec3& color);

	glm::vec3 getPosition() const;
	glm::vec3 getRotation() const;
	glm::vec3 getColor() const;


	glm::vec3 getAmbient() const;
	glm::vec3 getDiffuse() const;
	glm::vec3 getSpecular() const;

	glm::mat4x4 getMatrix();

private:
	void updateMatrix();




};

