#include "stdafx.h"
#include "ParticleParticleSpringForce.hpp"

namespace Quantum
{

	ParticleParticleSpringForce::ParticleParticleSpringForce(Body* otherBody, float restLength, float springConstant)
	{
		m_otherBody = otherBody;
		m_restLength = restLength;
		m_springConstant = springConstant;
	}


	ParticleParticleSpringForce::~ParticleParticleSpringForce()
	{
	}

	void ParticleParticleSpringForce::update(Body* b)
	{
		glm::vec3 d = b->getPosition() - m_otherBody->getPosition();
		float coeff = -(glm::length(d) - m_restLength) * m_springConstant;
		b->addForce(glm::normalize(d) * coeff);
	}
}