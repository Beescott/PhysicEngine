#pragma once

#include "Body.hpp"
#include "glm/glm.hpp"

namespace Quantum
{

	class Contact
	{
		public:
			Contact(Body* body1, Body* body2, glm::vec3 point = glm::vec3(0), glm::vec3 normal = glm::vec3(0), float depth = 0.0f);
			~Contact();

			Body* m_body1;
			Body* m_body2;
			glm::vec3 m_point;
			glm::vec3 m_normal;
			float m_depth;
	};

}