#pragma once

#include "SpriteBase.h"

class Platform : public SpriteBase
{
public:
	Platform(CorePosition pos);
	void Update(float fTime);
	bool PlayerWithinBounds();
};