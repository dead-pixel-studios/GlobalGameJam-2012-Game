#pragma once

#include "SpriteBase.h"

class Powerup : public SpriteBase
{
public:
	Powerup(CorePosition pos);
	void Update(float fTime);
};