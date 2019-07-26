#pragma once
#include "Body.hpp"
#include "glm/glm.hpp"

namespace Quantum
{

	class Halfspace :
		public Body
	{
		public:
			Halfspace(glm::vec3 normal, float offset);
			~Halfspace();

			void integrate(float t) override;
			void addForce(glm::vec3 f) override;
			AABB getAABB() override;
			
			void collideWithBody(World* w, Body* b) override;
			void collideWithParticle(World* w, Body* p) override;
			void collideWithHalfspace(World* w, Body* h) override;

			glm::vec3 getPosition() override;
			glm::vec3 getVelocity() override;
			GxUpdater* getGxUpdater() override;
			float getCharge() override;

			glm::vec3 m_normal;
			float m_offset;
	};

}