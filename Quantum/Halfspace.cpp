#include "stdafx.h"
#include "Halfspace.hpp"
#include "World.hpp"
#include "Particle.hpp"
#include "Halfspace.hpp"
#include "Contact.hpp"

namespace Quantum
{

	Halfspace::Halfspace(glm::vec3 normal, float offset) :
		m_normal(normal), m_offset(offset)
	{
	}


	Halfspace::~Halfspace()
	{
	}

	void Halfspace::integrate(float t)
	{}
	void Halfspace::addForce(glm::vec3 f)
	{}
	AABB Halfspace::getAABB()
	{
		return AABB(glm::vec3(0)-INFINITY, glm::vec3(0)+INFINITY);
	}

	void Halfspace::collideWithBody(World* w, Body* b)
	{
		b->collideWithHalfspace(w, this);
	}

	void Halfspace::collideWithParticle(World* w, Body* p)
	{
		float d = glm::dot(p->getPosition(), m_normal) - m_offset - ((Particle*)p)->getRadius();
		if (d < 0.0f)
			w->resolve(Contact(p, this, glm::vec3(0), m_normal, -d), (Particle*)p, this);
	}

	void Halfspace::collideWithHalfspace(World* w, Body* h)
	{
		// Do nothing
	}

	glm::vec3 Halfspace::getPosition()
	{
		return glm::vec3(0);
	}
	glm::vec3 Halfspace::getVelocity()
	{
		return glm::vec3(0);
	}
	GxUpdater* Halfspace::getGxUpdater()
	{
		return NULL;
	}
	float Halfspace::getCharge()
	{
		return 0.0f;
	}
}