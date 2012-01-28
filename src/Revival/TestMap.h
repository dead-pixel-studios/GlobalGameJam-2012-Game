#pragma once

#include "SpriteBase.h"

class TestMap : public SpriteBase {
public:
	TestMap();
	void Update(float);
	void Draw();
private:
	float lastUpdate;
	CorePosition _backgroundmistPos;
	CorePosition _foregroundmistPos;

	OpenGLTexture * backgroundMist;
	OpenGLTexture * foreground;
	OpenGLTexture * foregroundMist;
	OpenGLTexture * collision;

	OpenGLTexture * lava1;
	OpenGLTexture * lava2;
	OpenGLTexture * lava3;
};