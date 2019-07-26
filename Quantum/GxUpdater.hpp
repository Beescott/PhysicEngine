#pragma once

#include "glm/glm.hpp"

namespace Quantum {

	class GxUpdater
	{
		public:
			GxUpdater(void* gxObject = NULL);
			virtual ~GxUpdater();

			virtual void update(glm::vec3 pos) = 0;

		protected:
			void* m_gxObject;
	};

}