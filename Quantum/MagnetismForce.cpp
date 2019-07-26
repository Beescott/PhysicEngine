#include "stdafx.h"
#include "MagnetismForce.hpp"


namespace Quantum
{

	MagnetismForce::MagnetismForce(Body* otherBody, float k)
	{
		m_otherBody = otherBody;
		m_k = k;
	}


	MagnetismForce::~MagnetismForce()
	{
	}

	void MagnetismForce::update(Body* b)
	{
		glm::vec3 d = b->getPosition() - m_otherBody->getPosition();
		float coeff = m_k * (b->getCharge() * m_otherBody->getCharge());
		float l = glm::length(d) * glm::length(d);
		if (glm::length(d) > 0.5f)
			b->addForce((glm::normalize(d) * coeff) / l);
	}
}