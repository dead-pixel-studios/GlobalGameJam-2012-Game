#pragma once

#include "SpriteBase.h"

class Map : public SpriteBase{
public:
	Map() {_solid=false;}
	virtual bool IsKillZone(CorePosition pos)=0;
};