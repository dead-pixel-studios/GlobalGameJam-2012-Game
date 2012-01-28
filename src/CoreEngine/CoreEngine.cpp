#include "CoreEngine.h"

CoreEngine* CoreEngine::pinstance = 0;
CoreEngine* CoreEngine::Instance () {
	if(pinstance == 0) { pinstance = new CoreEngine; pinstance->Init(); }
	return pinstance;
}

void CoreEngine::Init() {
	CoreFunctions::ClearLog();
	this->GraphicsEngine = CoreGraphics::Instance();
	this->CoreApp = AppCore::Instance();
}

void CoreEngine::Start()
{
	this->CoreApp->Start();
	if(!CoreApp->DoQuit())
	{
		this->AppLoop();
	}
}

void CoreEngine::AppLoop()
{
	bool quit = false;
	while(!quit)
	{
		float timeNow = (float)SDL_GetTicks(); // Returns the number of milliseconds since SDL library initialization
		float deltaTime = (timeNow - lastUpdate) / 1000.0F; // delta in ms / 1000
		CoreApp->Update(deltaTime);
		quit = CheckEvents();
		if(!quit) { quit = CoreApp->DoQuit(); }
		lastUpdate = timeNow;
	}
}

bool CoreEngine::CheckEvents() {
	while(SDL_PollEvent(&event)) {
		switch(event.type) {
		case SDL_QUIT:
			return true;
			break;
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE) { return true; }
			CoreApp->HandleKeyDown(event);
			break;
		case SDL_KEYUP:
			CoreApp->HandleKeyUp(event);
		}
		RaiseEvent(event);
	}
	return false;
}

void CoreEngine::HandleKeyDown(SDL_Event keyDownEvent) {
	CoreApp->HandleKeyDown(keyDownEvent);
}

void CoreEngine::HandleKeyUp(SDL_Event keyUpEvent) {
}

void CoreEngine::RaiseEvent(SDL_Event eventRaised) {
	switch(eventRaised.type) {
	case SDL_KEYDOWN:
		HandleKeyDown(eventRaised);
		break;
	case SDL_KEYUP:
		HandleKeyUp(eventRaised);
		break;
	}
}
