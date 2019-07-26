#pragma once

#include "GxObject.hpp"
#include "Body.hpp"

class GxParticleParticleSpring :
	public GxObject
{
	public:
		GxParticleParticleSpring(Quantum::Body* b1, Quantum::Body* b2, float radius);
		~GxParticleParticleSpring();

		void draw(glm::vec3 ref);

	protected:
		Quantum::Body* m_b1;
		Quantum::Body* m_b2;
		float m_radius;
};

