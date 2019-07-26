#pragma once

#include "Quantum.h"

namespace Quantum
{

	class ParticleParticleSpringForce :
		public ForceGenerator
	{
		public:
			ParticleParticleSpringForce(Body* otherBody, float restLength, float springConstant);
			~ParticleParticleSpringForce();

			void update(Body* b);

			Body* m_otherBody;
			float m_restLength;
			float m_springConstant;
	};

}