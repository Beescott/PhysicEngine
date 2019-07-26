#pragma once

#include "ForceGenerator.hpp"
#include "Body.hpp"

namespace Quantum
{

	class MagnetismForce :
		public ForceGenerator
	{
		public:
			MagnetismForce(Body* otherBody, float k);
			~MagnetismForce();

			void update(Body* b);

			Body* m_otherBody;
			float m_k;
	};

}