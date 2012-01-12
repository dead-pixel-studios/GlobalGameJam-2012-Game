#include "CoreSize.h"

CoreSize::CoreSize()
{
}

CoreSize::CoreSize(int width, int height)
{
	this->width = width;
	this->height = height;
}

CoreSize::~CoreSize()
{
}

bool CoreSize::PowerOf2()
{
	if ((this->width & (this->width - 1)) != 0)
	{
		return false;
	}

	if ((this->height & (this->height - 1)) != 0)
	{
		return false;
	}

	return true;
}