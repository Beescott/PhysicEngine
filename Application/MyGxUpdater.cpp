#include "stdafx.h"
#include "MyGxUpdater.hpp"
#include "GxObject.hpp"


MyGxUpdater::MyGxUpdater(void* gxObject) : GxUpdater(gxObject)
{
}


MyGxUpdater::~MyGxUpdater()
{
}

void MyGxUpdater::update(glm::vec3 pos)
{
	((GxObject*)m_gxObject)->setPosition(pos);
}
