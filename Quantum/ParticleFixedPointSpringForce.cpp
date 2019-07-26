#include "stdafx.h"
#include "ParticleFixedPointSpringForce.hpp"

namespace Quantum
{

	ParticleFixedPointSpringForce::ParticleFixedPointSpringForce(glm::vec3* fixedPoint, float restLength, float springConstant)
	{
		m_fixedPoint = fixedPoint;
		m_restLength = restLength;
		m_springConstant = springConstant;
	}


	ParticleFixedPointSpringForce::~ParticleFixedPointSpringForce()
	{
	}

	void ParticleFixedPointSpringForce::update(Body* b)
	{
		glm::vec3 d = b->getPosition() - (*m_fixedPoint);
		float coeff = -(glm::length(d) - m_restLength) * m_springConstant;
		b->addForce(glm::normalize(d) * coeff);
	}

}