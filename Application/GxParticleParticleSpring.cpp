#include "stdafx.h"
#include "GxParticleParticleSpring.hpp"

#include <GL/glut.h>
#include <GL/gl.h>

GxParticleParticleSpring::GxParticleParticleSpring(Quantum::Body* b1, Quantum::Body* b2, float radius) :
	m_b1(b1), m_b2(b2), m_radius(radius)
{
}


GxParticleParticleSpring::~GxParticleParticleSpring()
{
}

void GxParticleParticleSpring::draw(glm::vec3 ref)
{
	glPushMatrix();
		glLineWidth(m_radius);
		glColor3f(1.0f, 1.0f, 1.0f);
		glBegin(GL_LINES);
			glVertex3f((m_b1->getPosition().x - ref.x), (m_b1->getPosition().y - ref.y), (m_b1->getPosition().z - ref.z));
			glVertex3f((m_b2->getPosition().x - ref.x), (m_b2->getPosition().y - ref.y), (m_b2->getPosition().z - ref.z));
		glEnd();
	glPopMatrix();
}