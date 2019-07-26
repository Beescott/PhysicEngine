#pragma once

#include "Quantum.h"

namespace Quantum
{

	class ParticleFixedPointSpringForce :
		public ForceGenerator
	{
		public:
			ParticleFixedPointSpringForce(glm::vec3* fixedPoint, float restLength, float springConstant);
			~ParticleFixedPointSpringForce();

			void update(Body* b);

			glm::vec3* m_fixedPoint;
			float m_restLength;
			float m_springConstant;
	};

}