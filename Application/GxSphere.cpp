#include "stdafx.h"
#include "GxSphere.hpp"

#include <GL/glut.h>
#include <GL/gl.h>

GxSphere::GxSphere(float radius, glm::vec3 color) :
	m_radius(radius), m_color(color)
{
}

GxSphere::GxSphere(float radius) :
	GxSphere(radius, glm::vec3((float)(rand() % 100) / 100.0f, (float)(rand() % 100) / 100.0f, (float)(rand() % 100) / 100.0f))
{
}

GxSphere::GxSphere() :
	GxSphere(1.0f, glm::vec3((float)(rand() % 100) / 100.0f, (float)(rand() % 100) / 100.0f, (float)(rand() % 100) / 100.0f))
{
}

GxSphere::~GxSphere()
{
}

void GxSphere::draw(glm::vec3 ref)
{
	if (m_position.y > -20.0f)
	{
		glPushMatrix();
			glTranslatef((m_position.x - ref.x), (m_position.y - ref.y), (m_position.z - ref.z));
			glColor3d(m_color.x, m_color.y, m_color.z);
			glutSolidSphere(m_radius, 15, 15);
		glPopMatrix();
	}
}

void GxSphere::setColor(float r, float g, float b)
{
	m_color.x = r;
	m_color.y = g;
	m_color.z = b;
}

void GxSphere::setColor(glm::vec3 color)
{
	m_color = color;
}