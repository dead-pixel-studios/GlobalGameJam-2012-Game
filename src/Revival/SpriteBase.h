#pragma once

#include "../CoreEngine/CoreGraphics.h"

class CoreGraphics;

class SpriteBase{
protected:
	CorePosition _pos;
	CorePosition _origin;
	int _angle;
	CorePosition _deltaPos;
	int _deltaAngle;

	friend class SpriteZCompare;
public:
	virtual void Update()=0;
	virtual void Draw()=0;
};