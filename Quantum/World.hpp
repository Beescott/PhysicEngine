#pragma once

#include <vector>
#include "ForceRegistry.hpp"
#include "Body.hpp"

#define DELTA 0.01f

namespace Quantum {

	class Particle;
	class Halfspace;
	class Contact;

	class World
	{
		public:
			World();
			~World();

			void integrate(float t);
			void addForceRegistry(ForceRegistry* fg);
			void addBody(Body* b);

			std::vector<Contact> broadphase();
			void narrowphase(std::vector<Contact> & c);
			void resolve(Contact c, Particle* p1, Particle* p2);
			void resolve(Contact c, Particle* p, Halfspace* h);

			void clearBodies();
			void applyGravity();
			void useGravity(bool useGravity);
			void useCollision(bool useCollision);
			void setDeterministe(bool isDeterministe);

			bool isUsingGravity();
			bool isUsingCollision();
			bool isDeterministe();

		private:
			float tick();
			void update(float dt);
			void updateForces();

		protected:
			std::vector<Body*> m_bodies;
			std::vector<ForceRegistry*> m_forceRegistries;
			float m_time = 0.0f;
			float m_ticktime = 0.0f;
			bool m_useGravity = true;
			bool m_useCollision = true;
			bool m_isDeterministe = true;
	};

}