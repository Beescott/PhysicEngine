#pragma once

#include "GxObject.hpp"
#include "Body.hpp"

class GxParticleFixedPointSpring :
	public GxObject
{
	public:
		GxParticleFixedPointSpring(glm::vec3* fixedPoint, Quantum::Body* b, float radius);
		~GxParticleFixedPointSpring();

		void draw(glm::vec3 ref);

protected:
	glm::vec3* m_fixedPoint;
	Quantum::Body* m_b;
	float m_radius;
};

