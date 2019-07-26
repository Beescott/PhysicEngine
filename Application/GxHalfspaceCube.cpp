#include "stdafx.h"
#include "GxHalfspaceCube.hpp"
#include "Quantum.h"

#include <GL/glut.h>
#include <GL/gl.h>
#include <iostream>

GxHalfspaceCube::GxHalfspaceCube(float radius, glm::vec3 center, glm::vec3 rotation)
{
	m_radius = radius;
	m_center = center;
	m_rotation = rotation;

	m_vertexs.push_back(glm::vec3(-radius, -radius, -radius));
	m_vertexs.push_back(glm::vec3(radius, -radius, -radius));
	m_vertexs.push_back(glm::vec3(radius, radius, -radius));
	m_vertexs.push_back(glm::vec3(-radius, radius, -radius));
	m_vertexs.push_back(glm::vec3(-radius, -radius, radius));
	m_vertexs.push_back(glm::vec3(radius, -radius, radius));
	m_vertexs.push_back(glm::vec3(radius, radius, radius));
	m_vertexs.push_back(glm::vec3(-radius, radius, radius));
}


GxHalfspaceCube::~GxHalfspaceCube()
{
}

void GxHalfspaceCube::setRotation(glm::vec3 rotation)
{
	m_rotation = rotation;
}

void GxHalfspaceCube::draw(glm::vec3 ref)
{
	glPushMatrix();
		glTranslatef((m_center.x - ref.x), (m_center.y - ref.y), (m_center.z - ref.z));
		//glRotatef(m_rotation.z, 0, 0, 1);
		//glRotatef(m_rotation.y, 0, 1, 0);
		//glRotatef(m_rotation.x, 1, 0, 0);
		glColor3d(1.0f, 0.0f, 0.0f);
		glBegin(GL_LINES);
			glVertex3f(m_vertexs[0].x, m_vertexs[0].y, m_vertexs[0].z);
			glVertex3f(m_vertexs[1].x, m_vertexs[1].y, m_vertexs[1].z);

			glVertex3f(m_vertexs[1].x, m_vertexs[1].y, m_vertexs[1].z);
			glVertex3f(m_vertexs[2].x, m_vertexs[2].y, m_vertexs[2].z);

			glVertex3f(m_vertexs[2].x, m_vertexs[2].y, m_vertexs[2].z);
			glVertex3f(m_vertexs[3].x, m_vertexs[3].y, m_vertexs[3].z);

			glVertex3f(m_vertexs[3].x, m_vertexs[3].y, m_vertexs[3].z);
			glVertex3f(m_vertexs[0].x, m_vertexs[0].y, m_vertexs[0].z);

			glVertex3f(m_vertexs[4].x, m_vertexs[4].y, m_vertexs[4].z);
			glVertex3f(m_vertexs[5].x, m_vertexs[5].y, m_vertexs[5].z);

			glVertex3f(m_vertexs[5].x, m_vertexs[5].y, m_vertexs[5].z);
			glVertex3f(m_vertexs[6].x, m_vertexs[6].y, m_vertexs[6].z);

			glVertex3f(m_vertexs[6].x, m_vertexs[6].y, m_vertexs[6].z);
			glVertex3f(m_vertexs[7].x, m_vertexs[7].y, m_vertexs[7].z);

			glVertex3f(m_vertexs[7].x, m_vertexs[7].y, m_vertexs[7].z);
			glVertex3f(m_vertexs[4].x, m_vertexs[4].y, m_vertexs[4].z);

			glVertex3f(m_vertexs[0].x, m_vertexs[0].y, m_vertexs[0].z);
			glVertex3f(m_vertexs[4].x, m_vertexs[4].y, m_vertexs[4].z);

			glVertex3f(m_vertexs[1].x, m_vertexs[1].y, m_vertexs[1].z);
			glVertex3f(m_vertexs[5].x, m_vertexs[5].y, m_vertexs[5].z);

			glVertex3f(m_vertexs[2].x, m_vertexs[2].y, m_vertexs[2].z);
			glVertex3f(m_vertexs[6].x, m_vertexs[6].y, m_vertexs[6].z);

			glVertex3f(m_vertexs[3].x, m_vertexs[3].y, m_vertexs[3].z);
			glVertex3f(m_vertexs[7].x, m_vertexs[7].y, m_vertexs[7].z);

		glEnd();
	glPopMatrix();
}

void GxHalfspaceCube::rotateZXY(float angleZ, float angleX, float angleY)
{
	for(int i = 0; i < m_vertexs.size(); i++)
	{
		glm::vec3 res = m_vertexs[i];
		float theta = angleZ * PI / 180.0f;
		//rot Z
		res.x = m_vertexs[i].x * cos(theta) - m_vertexs[i].y * sin(theta);
		res.y = m_vertexs[i].x * sin(theta) + m_vertexs[i].y * cos(theta);

		glm::vec3 ress = res;
		theta = angleX * PI / 180.0f;
		//rot X
		ress.y = res.y * cos(theta) - res.z * sin(theta);
		ress.z = res.y * sin(theta) + res.z * cos(theta);

		glm::vec3 resss = ress;
		theta = angleY * PI / 180.0f;
		//rot Y
		resss.x = ress.x * cos(theta) + ress.z * sin(theta);
		resss.z = -ress.x * sin(theta) + ress.z * cos(theta);

		m_vertexs[i] = resss;
	}
}