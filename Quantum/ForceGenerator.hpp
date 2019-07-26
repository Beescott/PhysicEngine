#pragma once
#include "Particle.hpp"

class Body;

namespace Quantum
{

	class ForceGenerator
	{
		public:
			ForceGenerator();
			~ForceGenerator();

			virtual void update(Body* b) = 0;
	};

}