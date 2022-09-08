#pragma once
#include "core/vec.h"
#include "core/mat.h"
#include "resources/shader.h"
#include "resources/model.h"
class object
{
private:
	glm::vec3 m_position = glm::vec3(0, 0 , 0);
	glm::vec3 m_scale = glm::vec3(1, 1, 1);
	glm::vec3 m_rotation = glm::vec3(0, 0, 0);

	glm::mat4x4 m_modelMat = glm::mat4x4(1.0);

	shader* m_shader;
	model* m_model;
	bool bUpdateMatrix = true;

public:
	object(const glm::vec3& pos = { 0, 0, 0 }, const glm::vec3& scale = { 1, 1, 1 }, const glm::vec3& rot = { 0, 0, 0 });

	glm::vec3 getPosition()const;
	glm::vec3 getScale()const;
	glm::vec3 getRotation()const;

	void setPosition(const glm::vec3& newPos);
	void setScale(const glm::vec3& newScale);
	void setRotation(const glm::vec3& newRotation);

	void setShader(shader* shader);
	void setModel(model* mod);

	void draw() const;

	glm::mat4x4 getMatrix();

	virtual ~object();
private:
	void updateMatrix();

};

