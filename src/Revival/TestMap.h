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
	
	bool winnable();
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
	OpenGLTexture * lava4;
	OpenGLTexture * lava5;
	OpenGLTexture * lava6;
	OpenGLTexture * lava7;
	OpenGLTexture * lava8;
	OpenGLTexture * lava9;
	OpenGLTexture * lava10;
	OpenGLTexture * lava11;
	OpenGLTexture * lava12;


	OpenGLTexture * killzone;

	Powerup * _pwrUp;
	Platform * _icePlatform;

	int lavaStep;
};