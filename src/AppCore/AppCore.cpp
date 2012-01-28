#include "AppCore.h"

AppCore* AppCore::pinstance = 0;
AppCore* AppCore::Instance () {
	if(pinstance == 0) { pinstance = new AppCore; pinstance->Init(); }
	return pinstance;
}

void AppCore::Init() {
	quit = false;
	this->GraphicsCore = CoreGraphics::Instance();

	this->universe = Universe::Instance();
	this->intro = Intro::Instance();
	frameCount = 0;
	appStartFrame = -1;
}

void AppCore::Start() {
}

void AppCore::Update(float fTime)
{
	if(appStartFrame==-1) { appStartFrame = SDL_GetTicks(); }
	float frameRate = (float)((float)frameCount / (float)((SDL_GetTicks() - appStartFrame) / 1000.f));

	//SDL_framerateDelay(this->GraphicsCore->getFPSManager());

	if(this->intro->finishedIntro()) {
		this->universe->Update(fTime);
	}
	else {
		this->intro->Update(fTime);
	}
	this->GraphicsCore->StartFrame();

	if(this->intro->finishedIntro()) {
		this->universe->Draw();
	}
	else {
		this->intro->Draw();
	}

	CorePosition * cPos = new CorePosition(5,5);
	SDL_Color color;
	color.r = 255;
	color.g = 0;
	color.b = 0;
	this->GraphicsCore->DrawString(CoreFunctions::addIntToString("FPS: ", (int)frameRate), cPos, color);
	
	delete cPos;
	this->GraphicsCore->EndFrame();

	frameCount++;
}

void AppCore::HandleKeyDown(SDL_Event keyDownEvent)
{
	universe->KeyDown(keyDownEvent.key.keysym.sym);
}

void AppCore::HandleKeyUp(SDL_Event keyUpEvent){
	universe->KeyUp(keyUpEvent.key.keysym.sym);
}