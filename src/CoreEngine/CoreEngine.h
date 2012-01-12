#pragma once

#include "CoreGraphics.h"
#include "../AppCore/AppCore.h"
class CoreGraphics;
class AppCore;

class CoreEngine
{
public:
	static CoreEngine* Instance();
	void Start();
protected:
	CoreEngine(void) {};
	CoreEngine(const CoreEngine&);
	CoreEngine& operator=(const CoreEngine&);
private:
	static CoreEngine* pinstance;

	CoreGraphics * GraphicsEngine;
	AppCore * CoreApp;
	void Init();
	void AppLoop();
	bool CheckEvents();
	void RaiseEvent(SDL_Event eventRaised);
	void HandleKeyUp(SDL_Event keyUpEvent);
	void HandleKeyDown(SDL_Event keyDownEvent);

	SDL_Event event;
	float lastUpdate;
};