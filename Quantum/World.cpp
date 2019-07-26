#include "stdafx.h"
#include "World.hpp"
#include "Halfspace.hpp"
#include "Contact.hpp"
#include <iostream>

namespace Quantum {

	World::World()
	{

	}

	World::~World()
	{
		for (int i = 0; i < m_bodies.size(); i++)
		{
			delete m_bodies[i];
		}

		for (int i = 0; i < m_forceRegistries.size(); i++)
		{
			delete m_forceRegistries[i];
		}
	}

	// PRIVATE

	float World::tick()
	{
		if (m_useGravity)
			applyGravity();
		
		updateForces();

		if (m_useCollision)
			narrowphase(broadphase());

		for (int i = 0; i < m_bodies.size(); i++)
		{
			m_bodies[i]->integrate((m_isDeterministe) ? DELTA : (m_time - m_ticktime));
		}

		m_ticktime += (m_isDeterministe) ? DELTA : (m_time - m_ticktime);

		return m_time - m_ticktime;
	}

	void World::update(float dt)
	{
		for (int i = 0; i < m_bodies.size(); i++)
		{
			if (m_bodies[i]->getGxUpdater() != NULL)
				m_bodies[i]->getGxUpdater()->update(m_bodies[i]->getPosition() + dt * m_bodies[i]->getVelocity());
		}
	}

	void World::updateForces()
	{
		for (int i = 0; i < m_forceRegistries.size(); i++)
		{
			m_forceRegistries[i]->m_fg->update(m_forceRegistries[i]->m_b);
		}
	}

	// PUBLIC

	void World::integrate(float t)
	{
		m_time += t;

		float dt = m_time - m_ticktime;

		if (m_isDeterministe)
		{
			while (dt >= DELTA)
			{
				dt = tick();
			}
		}
		else
		{
			dt = tick();
		}

		update(dt);
	}

	void World::addBody(Body* body)
	{
		m_bodies.push_back(body);
	}

	void World::addForceRegistry(ForceRegistry* fg)
	{
		m_forceRegistries.push_back(fg);
	}


	std::vector<Contact> World::broadphase()
	{
		std::vector<AABB> aabbs = std::vector<AABB>();
		std::vector<Contact> contacts = std::vector<Contact>();

		for (int i = 0; i < m_bodies.size(); i++)
		{
			aabbs.push_back(m_bodies[i]->getAABB());
		}

		for (int i = 0; i < m_bodies.size(); i++)
		{
			for (int j = i + 1; j < m_bodies.size(); j++)
			{
				if (aabbs[i].collideWith(aabbs[j]))
				{
					contacts.push_back(Contact(m_bodies[i], m_bodies[j]));
				}
			}
		}

		return contacts;
	}

	void World::narrowphase(std::vector<Contact> & c)
	{
		for (int i = 0; i < c.size(); i++)
		{
			c[i].m_body1->collideWithBody(this, c[i].m_body2);
		}
	}

	void World::resolve(Contact c, Particle* p1, Particle* p2)
	{
		p1->setPosition(p1->getPosition() - (c.m_normal * c.m_depth * p2->getMass() / (p1->getMass() + p2->getMass())));
		p2->setPosition(p2->getPosition() + (c.m_normal * c.m_depth * p1->getMass() / (p1->getMass() + p2->getMass())));

		p1->setVelocity(p1->getVelocity() - 2.0f * glm::dot(p1->getVelocity(), c.m_normal) * c.m_normal);
		p2->setVelocity(p2->getVelocity() + 2.0f * glm::dot(p2->getVelocity(), -c.m_normal) * c.m_normal);
	}

	void World::resolve(Contact c, Particle* p, Halfspace* h)
	{
		p->setPosition(p->getPosition() + c.m_normal * c.m_depth);

		p->setVelocity(p->getVelocity() - 2.0f * glm::dot(p->getVelocity(), c.m_normal) * c.m_normal);
	}


	void World::clearBodies()
	{
		for (int i = 0; i < m_bodies.size(); i++)
		{
			delete m_bodies[i];
		}
		m_bodies.clear();

		for (int i = 0; i < m_forceRegistries.size(); i++)
		{
			delete m_forceRegistries[i];
		}
		m_forceRegistries.clear();
	}

	void World::applyGravity()
	{
		for (int i = 0; i < m_bodies.size(); i++)
		{
			m_bodies[i]->addForce(glm::vec3(0.0f, -9.3f, 0.0f));
		}
	}

	void World::useGravity(bool useGravity)
	{
		m_useGravity = useGravity;
	}

	void World::useCollision(bool useCollision)
	{
		m_useCollision = useCollision;
	}

	void World::setDeterministe(bool isDeterministe)
	{
		m_isDeterministe = isDeterministe;
	}

	bool World::isUsingGravity()
	{
		return m_useGravity;
	}

	bool World::isUsingCollision()
	{
		return m_useCollision;
	}

	bool World::isDeterministe()
	{
		return m_isDeterministe;
	}
}