#pragma once

#include "SpriteBase.h"
#include "Powerup.h"
#include "Map.h"

class TestMap :  public Map {
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

	Powerup * _pwrUp;

	int lavaStep;
};