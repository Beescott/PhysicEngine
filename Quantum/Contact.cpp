#include "stdafx.h"
#include "Contact.hpp"

namespace Quantum
{

	Contact::Contact(Body* body1, Body* body2, glm::vec3 point, glm::vec3 normal, float depth) :
		m_body1(body1), m_body2(body2), m_point(point), m_normal(normal), m_depth(depth)
	{
	}


	Contact::~Contact()
	{
	}

}