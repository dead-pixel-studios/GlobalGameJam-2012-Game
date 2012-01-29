#pragma once

#include "SpriteBase.h"
#include "Platform.h"

class Map : public SpriteBase 
{
public:
	Map() {_solid=false;}
	vector<Platform*> platforms;
	virtual bool IsKillZone(CorePosition pos)=0;
};