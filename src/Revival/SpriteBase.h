#pragma once

#include "../CoreEngine/CoreGraphics.h"

class CoreGraphics;

class SpriteBase{
protected:
	CorePosition _pos;
	CorePosition _origin;
	CoreSize _size;
	float _angle;
	CorePosition _deltaPos;
	int _deltaAngle;

	bool _visible;

	CoreGraphics *gEngine;
	OpenGLTexture *texture;

	friend class SpriteZCompare;
	
	void DefaultDraw();
	
	bool IsKeyDown(SDLKey key);
public:
	SpriteBase();

	virtual void Update(float deltaTime)=0;
	virtual void Draw() {DefaultDraw();}

	CoreColor GetPixel(CorePosition pos);
};