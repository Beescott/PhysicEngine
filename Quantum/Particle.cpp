#include "stdafx.h"
#include <iostream>
#include "Particle.hpp"
#include "World.hpp"
#include "Halfspace.hpp"
#include "GxUpdater.hpp"
#include "AABB.hpp"
#include "Contact.hpp"

namespace Quantum {

	Particle::Particle(glm::vec3 position, float mass, glm::vec3 velocity, glm::vec3 acceleration, float damping, float charge, float radius)
	{
		m_position = position;
		m_mass = mass;
		if (mass > 0.0f)
			m_invMass = 1.0f / mass;
		m_velocity = velocity;
		m_acceleration = acceleration;
		m_damping = damping;
		m_charge = charge;
		m_radius = radius;
	}


	Particle::~Particle()
	{
		delete m_gxUpdater;
	}

	void Particle::integrate(float t)
	{
		m_velocity *= m_damping;
		m_acceleration += m_forceAccumulator * m_invMass;
		m_velocity += m_acceleration * t;
		m_position += m_velocity * t;

		if (m_gxUpdater != NULL) m_gxUpdater->update(m_position);
		clear();
	}

	void Particle::addForce(glm::vec3 f)
	{
		m_forceAccumulator += f;
	}

	void Particle::print()
	{
		std::cout << "Particle : pos (" << m_position.x << "," << m_position.y << "," << m_position.z << ")" << std::endl;
	}

	void Particle::clear()
	{
		m_acceleration = glm::vec3(0);
		m_forceAccumulator = glm::vec3(0);
	}

	AABB Particle::getAABB()
	{
		return AABB(m_position - m_radius, m_position + m_radius);
	}

	void Particle::collideWithBody(World* w, Body* b)
	{
		b->collideWithParticle(w, this);
	}

	void Particle::collideWithParticle(World* w, Body* p)
	{
		if (glm::distance(getPosition(), p->getPosition()) <= (m_radius + ((Particle*)p)->m_radius))
			w->resolve(Contact(this, p, (getPosition() + p->getPosition()) / 2.0f, glm::normalize(p->getPosition() - getPosition()), (m_radius + ((Particle*)p)->m_radius) - glm::distance(getPosition(), p->getPosition())), this, ((Particle*)p));
	}

	void Particle::collideWithHalfspace(World* w, Body* h)
	{
		float d = glm::dot(getPosition(), ((Halfspace*)h)->m_normal) - ((Halfspace*)h)->m_offset - m_radius;
		if (d < 0.0f)
			w->resolve(Contact(this, h, glm::vec3(0), ((Halfspace*)h)->m_normal, -d), this, ((Halfspace*)h));
	}

	void Particle::setPosition(glm::vec3 position)
	{
		m_position = position;
	}

	void Particle::setMass(float mass)
	{
		m_mass = mass;
		if (mass > 0.0f)
			m_invMass = 1.0f / mass;
	}

	void Particle::setVelocity(glm::vec3 velocity)
	{
		m_velocity = velocity;
	}

	void Particle::setAcceleration(glm::vec3 acceleration)
	{
		m_acceleration = acceleration;
	}

	void Particle::setGxUpdater(GxUpdater* gxUpdater)
	{
		m_gxUpdater = gxUpdater;
	}

	void Particle::setCharge(float charge)
	{
		m_charge = charge;
	}

	void Particle::setRadius(float radius)
	{
		m_radius = radius;
	}


	glm::vec3 Particle::getPosition()
	{
		return m_position;
	}
	
	float Particle::getMass()
	{
		return m_mass;
	}

	glm::vec3 Particle::getVelocity()
	{
		return m_velocity;
	}

	glm::vec3 Particle::getAcceleration()
	{
		return m_acceleration;
	}

	GxUpdater* Particle::getGxUpdater()
	{
		return m_gxUpdater;
	}

	float Particle::getCharge()
	{
		return m_charge;
	}

	float Particle::getRadius()
	{
		return m_radius;
	}
}