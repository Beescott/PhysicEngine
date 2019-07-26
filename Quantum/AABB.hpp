#pragma once
#include "glm/glm.hpp"

namespace Quantum
{

	class AABB
	{
		public:
			AABB(glm::vec3 min, glm::vec3 max);
			~AABB();

			bool collideWith(AABB const& aabb);

			glm::vec3 m_min;
			glm::vec3 m_max;
	};

}