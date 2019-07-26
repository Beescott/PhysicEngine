#pragma once

#include "ForceGenerator.hpp"
#include "Body.hpp"

namespace Quantum
{

	class ForceRegistry
	{
		public:
			ForceRegistry(Body* b = NULL, ForceGenerator* fg = NULL);
			~ForceRegistry();

			Body* m_b;
			ForceGenerator* m_fg;
	};

}