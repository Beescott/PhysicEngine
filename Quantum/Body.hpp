#pragma once

#include "glm/glm.hpp"
#include "AABB.hpp"
#include "GxUpdater.hpp"



namespace Quantum
{
	class World;

	class Body
	{
		public:
			Body();
			~Body();

			virtual void integrate(float t) = 0;
			virtual void addForce(glm::vec3 f) = 0;
			virtual AABB getAABB() = 0;

			virtual void collideWithBody(World* w, Body* b) = 0;
			virtual void collideWithParticle(World* w, Body* p) = 0;
			virtual void collideWithHalfspace(World* w, Body* h) = 0;

			virtual glm::vec3 getPosition() = 0;
			virtual glm::vec3 getVelocity() = 0;
			virtual GxUpdater* getGxUpdater() = 0;
			virtual float getCharge() = 0;

			float m_restitution;
	};

}