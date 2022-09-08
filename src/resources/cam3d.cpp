#include "cam3d.h"
#include <glm/gtc/matrix_transform.hpp>

cam3d::cam3d(const glm::vec3& pos, const glm::vec3& target)
	:m_position(pos), m_target(target)
{
	m_updateMat = true;
}

void cam3d::setTarget(const glm::vec3& target)
{
	m_target = target;
	m_updateMat = true;
}


void cam3d::setPosition(const glm::vec3& pos)
{
	m_position = pos;
	m_updateMat = true;

}

glm::mat4x4 cam3d::getView()
{
	if (m_updateMat)
		updateMat();
	return m_viewMat;
}

glm::vec3 cam3d::getPos() const
{
	return m_position;
}

void cam3d::setViewMat(const glm::mat4x4& newMat)
{
	m_viewMat = newMat;
}

glm::vec3 cam3d::getTarget() const
{
	return m_target;
}

void cam3d::updateMat()
{
	m_viewMat = glm::lookAt(m_position, m_target, glm::vec3(0, 1, 0));
}
