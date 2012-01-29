#pragma once

#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_framerate.h>
#include "OpenGLTexture.h"
#include "CoreFunctions.h"
#include "CoreSize.h"
#include "CorePosition.h"

#include <string>

using namespace std;

class CoreColor;
class Player;

class CoreGraphics
{
public:
	static CoreGraphics* Instance();
	void StartFrame();
	void EndFrame();
	OpenGLTexture * CreateTexture(string textureLocation);
	void DrawTexture(OpenGLTexture * texture, CorePosition * position, CorePosition * origin, CoreSize * size, float rotation = -1, float red = 1.0F, float green = 1.0F, float blue = 1.0F, float alpha = 1.0F);
	void DrawTextureFrame(OpenGLTexture * texture, CorePosition * position, CorePosition * origin, CoreSize * size, float rotation = -1, int totalframes = 1, int currentframe = 1, float red = 1.0F, float green = 1.0F, float blue = 1.0F, float alpha = 1.0F);
	void DrawString(string str, CorePosition * position, SDL_Color color);
	void DrawRectangle(CorePosition * position, CoreSize * size, int r, int g, int b, int a);

	void ScaleWorld(float x, float y, float z);
	CoreColor getPixelColor(SDL_Surface * surface, int x, int y);
	CoreSize * GetScreenSize() { return ScreenSize; }
	FPSmanager * getFPSManager() { return fManager; }

	void glEnable2D();
	void glDisable2D();
protected:
	CoreGraphics(void) {};
	CoreGraphics(const CoreGraphics&);
	CoreGraphics& operator=(const CoreGraphics&);
private:
	static CoreGraphics* pinstance;
	FPSmanager * fManager;
	TTF_Font * defaultFont;
	SDL_Surface * screen;
	CoreSize * ScreenSize;
	void Init();

	SDL_Surface * GetPow2Surface(SDL_Surface * surface);
	Uint32 getPixel(SDL_Surface * surface, int x, int y);

	float xScale;
	float yScale;
	float zScale;
};

#include "CoreColor.h"