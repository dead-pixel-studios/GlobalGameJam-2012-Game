#pragma once

#include "SpriteBase.h"

class TestMap : public SpriteBase {
public:
	TestMap();
	void Update(float);
	void Draw();

	CoreColor GetPixel(CorePosition pos);
private:
	float lastMistScroll;
	float lastLavaChange;
	CorePosition _backgroundmistPos;
	CorePosition _foregroundmistPos;

	OpenGLTexture * backgroundMist;
	OpenGLTexture * foreground;
	OpenGLTexture * foregroundMist;
	OpenGLTexture * collision;

	OpenGLTexture * lava1;
	OpenGLTexture * lava2;
	OpenGLTexture * lava3;

	int lavaStep;
};