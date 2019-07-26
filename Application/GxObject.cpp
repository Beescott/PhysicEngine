#include "stdafx.h"
#include "GxObject.hpp"


GxObject::GxObject()
{
}


GxObject::~GxObject()
{
}

void GxObject::setPosition(glm::vec3 pos)
{
	m_position = pos;
}