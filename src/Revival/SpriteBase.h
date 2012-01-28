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

	CoreGraphics *gEngine;
	OpenGLTexture *texture;

	friend class SpriteZCompare;
public:
	SpriteBase();

	virtual void Update()=0;
	virtual void Draw()=0;
};