#pragma once

#include "SpriteBase.h"

class Platform;

class Map : public SpriteBase 
{
public:
	Map() {_solid=false;}
	vector<Platform*> platforms;
	virtual bool IsKillZone(CorePosition pos)=0;
};

#include "Platform.h"