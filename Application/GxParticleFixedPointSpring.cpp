#include "stdafx.h"
#include "GxParticleFixedPointSpring.hpp"

#include <GL/glut.h>
#include <GL/gl.h>

GxParticleFixedPointSpring::GxParticleFixedPointSpring(glm::vec3* fixedPoint, Quantum::Body* b, float radius) :
	m_fixedPoint(fixedPoint), m_b(b), m_radius(radius)
{
}


GxParticleFixedPointSpring::~GxParticleFixedPointSpring()
{
}

void GxParticleFixedPointSpring::draw(glm::vec3 ref)
{
	glPushMatrix();
		glLineWidth(m_radius);
		glColor3f(1.0f, 0.6f, 0.6f);
		glBegin(GL_LINES);
			glVertex3f((m_fixedPoint->x - ref.x), (m_fixedPoint->y - ref.y), (m_fixedPoint->z - ref.z));
			glVertex3f((m_b->getPosition().x - ref.x), (m_b->getPosition().y - ref.y), (m_b->getPosition().z - ref.z));
		glEnd();
	glPopMatrix();
}
