#pragma once

#include "ForceGenerator.hpp"

namespace Quantum
{

	class DragForce :
		public ForceGenerator
	{
		public:
			DragForce(float k1, float k2);
			~DragForce();

			void update(Body* b);

			float m_k1;
			float m_k2;
	};

}