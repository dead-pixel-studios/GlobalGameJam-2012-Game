#pragma once

#include "../CoreEngine/CoreGraphics.h"
#include "../CoreEngine/CoreFunctions.h"
#include "../Revival/Universe.h"

class CoreGraphics;

class AppCore
{
public:
	static AppCore* Instance();
	void Start();
	void HandleKeyDown(SDL_Event keyDownEvent);
	void HandleKeyUp(SDL_Event keyUpEvent);
	void Update(float Time);
	bool DoQuit() { return quit; }
protected:
	AppCore(void) {};
	AppCore(const AppCore&);
	AppCore& operator=(const AppCore&);
private:
	static AppCore* pinstance;
	CoreGraphics * GraphicsCore;
	int frameCount;
	int appStartFrame;
	bool quit;

	Universe * universe;
	void Init();
};
