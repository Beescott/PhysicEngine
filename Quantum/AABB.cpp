#include "stdafx.h"
#include "AABB.hpp"

namespace Quantum
{

	AABB::AABB(glm::vec3 min, glm::vec3 max) :
		m_min(min), m_max(max)
	{
	}

	AABB::~AABB()
	{
	}

	bool AABB::collideWith(AABB const& aabb)
	{
		return (!((m_min.x >= aabb.m_max.x)
			|| (m_max.x <= aabb.m_min.x)
			|| (m_min.y >= aabb.m_max.y)
			|| (m_max.y <= aabb.m_min.y)
			|| (m_min.z >= aabb.m_max.z)
			|| (m_max.z <= aabb.m_min.z)));
	}

}