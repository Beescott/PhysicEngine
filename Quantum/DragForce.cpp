#include "stdafx.h"
#include "DragForce.hpp"
#include "body.hpp"

namespace Quantum
{

	DragForce::DragForce(float k1, float k2)
	{
		m_k1 = k1;
		m_k2 = k2;
	}


	DragForce::~DragForce()
	{
	}

	void DragForce::update(Body* b)
	{
		float coeff = - (m_k1 * glm::length(b->getVelocity()) + m_k2 * pow(glm::length(b->getVelocity()), 2.0f));
		b->addForce(glm::normalize(b->getVelocity()) * coeff);
	}
}