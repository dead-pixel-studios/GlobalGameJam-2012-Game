#pragma once

#include "SpriteBase.h"

class Map : public SpriteBase{
public:
	virtual bool IsKillZone(CorePosition pos)=0;
}