#pragma once

#include "glm/glm.hpp"

class GxObject
{
	public:
		GxObject();
		virtual ~GxObject();

		void setPosition(glm::vec3 pos);
		virtual void draw(glm::vec3 ref) = 0;

	protected:
		glm::vec3 m_position;
};

