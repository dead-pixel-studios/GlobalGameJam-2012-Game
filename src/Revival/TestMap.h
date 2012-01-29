#pragma once

#include "Map.h"
#include "Powerup.h"
#include "Platform.h"
#include "SpriteBase.h"
#include <vector>

class TestMap :  public Map {
public:
	TestMap();
	void Update(float);
	void Draw();
	CoreColor GetPixel(CorePosition pos);
	bool IsKillZone(CorePosition pos);
private:
	float mistaccumulator;
	float lavaaccumulator;

	CorePosition _backgroundmistPos;
	CorePosition _foregroundmistPos;

	OpenGLTexture * backgroundMist;
	OpenGLTexture * foreground;
	OpenGLTexture * foregroundMist;
	OpenGLTexture * collision;

	OpenGLTexture * lava1;
	OpenGLTexture * lava2;
	OpenGLTexture * lava3;

	OpenGLTexture * killzone;

	Powerup * _pwrUp;
	Platform * _icePlatform;

	int lavaStep;
};