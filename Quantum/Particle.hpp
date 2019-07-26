#pragma once

#include "Body.hpp"
#include "glm/glm.hpp"

namespace Quantum {

	class Particle : public Body
	{
		public:
			Particle(glm::vec3 position = glm::vec3(0), float mass = 1.0f, glm::vec3 velocity = glm::vec3(0), glm::vec3 acceleration = glm::vec3(0), float damping = 0.99f, float charge = 1.0f, float radius = 0.3f);
			~Particle();

			void integrate(float t);
			void addForce(glm::vec3 f);
			void print();
			void clear();
			AABB getAABB();

			void collideWithBody(World* w, Body* b) override;
			void collideWithParticle(World* w, Body* p) override;
			void collideWithHalfspace(World* w, Body* h) override;

			void setPosition(glm::vec3 position);
			void setMass(float mass);
			void setVelocity(glm::vec3 velocity);
			void setAcceleration(glm::vec3 acceleration);
			void setGxUpdater(GxUpdater* gxUpdater);
			void setCharge(float charge);
			void setRadius(float radius);
			
			glm::vec3 getPosition();
			float getMass();
			glm::vec3 getVelocity();
			glm::vec3 getAcceleration();
			GxUpdater* getGxUpdater();
			float getCharge();
			float getRadius();

		protected:
			glm::vec3 m_position;
			glm::vec3 m_velocity;
			glm::vec3 m_acceleration;
			glm::vec3 m_forceAccumulator;
			float m_damping;
			float m_mass;
			float m_invMass;
			float m_charge;
			float m_radius;
			
			GxUpdater* m_gxUpdater = NULL;
	};

}