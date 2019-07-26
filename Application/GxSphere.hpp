#pragma once
#include "GxObject.hpp"

class GxSphere : public GxObject
{
	public:
		GxSphere(float radius, glm::vec3 color);
		GxSphere(float radius);
		GxSphere();
		virtual ~GxSphere();

		void draw(glm::vec3 ref);
		void setColor(float r, float g, float b);
		void setColor(glm::vec3 color);
	
	protected:
		float m_radius;
		glm::vec3 m_color;
};

