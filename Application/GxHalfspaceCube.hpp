#pragma once
#include "GxObject.hpp"
#include <vector>

class GxHalfspaceCube :
	public GxObject
{
	public:
		GxHalfspaceCube(float radius, glm::vec3 center, glm::vec3 rotation);
		~GxHalfspaceCube();

		void setRotation(glm::vec3 rotation);

		void draw(glm::vec3 ref);

		void rotateZXY(float angleZ, float angleX, float angleY);

	protected:
		float m_radius;
		glm::vec3 m_center;
		glm::vec3 m_rotation;
		std::vector<glm::vec3> m_vertexs;
};

