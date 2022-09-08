#pragma once
#include "../core/mat.h"
class cam3d
{
private:
	glm::vec3 m_position;
	glm::vec3 m_target;

	bool m_updateMat = false;
	glm::mat4x4 m_viewMat;

public:

	cam3d(const glm::vec3& pos = { 0, 0, 0 }, const glm::vec3& target = { 0, 0, -1 });


	void setTarget(const glm::vec3& target);
	void setPosition(const glm::vec3& pos);

	glm::mat4x4 getView();

	glm::vec3 getPos() const;
	void setViewMat(const glm::mat4x4& newMat); 
	glm::vec3 getTarget() const;

private:
	void updateMat();

};

