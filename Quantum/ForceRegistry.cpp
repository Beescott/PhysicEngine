#include "stdafx.h"
#include "ForceRegistry.hpp"

namespace Quantum
{

	ForceRegistry::ForceRegistry(Body* b, ForceGenerator* fg)
	{
		m_b = b;
		m_fg = fg;
	}


	ForceRegistry::~ForceRegistry()
	{
		delete m_fg;
	}

}