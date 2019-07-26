#pragma once

#include "Quantum.h"
#include "glm/glm.hpp"


class MyGxUpdater : public Quantum::GxUpdater
{
	public:
		MyGxUpdater(void* gxObject = NULL);
		virtual ~MyGxUpdater();

		void update(glm::vec3 pos);
};

