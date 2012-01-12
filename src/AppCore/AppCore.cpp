#include "AppCore.h"

AppCore* AppCore::pinstance = 0;
AppCore* AppCore::Instance () {
	if(pinstance == 0) { pinstance = new AppCore; pinstance->Init(); }
	return pinstance;
}

void AppCore::Init() {
	quit = false;
	this->GraphicsCore = CoreGraphics::Instance();
	OpenGLTexture * texture1 = GraphicsCore->CreateTexture(CoreFunctions::GetAppPath() + "/data/image.bmp");
	texture1->Load();

	frameCount = 0;
	appStartFrame = -1;
}

void AppCore::Start() {
}

void AppCore::Update(float fTime)
{
	if(appStartFrame==-1) { appStartFrame = SDL_GetTicks(); }
	float frameRate = (float)((float)frameCount / (float)((SDL_GetTicks() - appStartFrame) / 1000.f));

	this->GraphicsCore->StartFrame();

	SDL_framerateDelay(this->GraphicsCore->getFPSManager());
	CorePosition * cPos = new CorePosition(10,10);
	CoreSize * cSize = new CoreSize(64,64);
	//this->GraphicsCore->DrawTexture(texture1,cPos,cSize);
	delete cPos;
	delete cSize;
	cPos = new CorePosition(100,100);
	cSize = new CoreSize(128,128);
	//this->GraphicsCore->DrawTexture(texture2,cPos,cSize);
	delete cPos;
	//delete cSize;
	SDL_Color color;
	color.r = 255;
	color.g = 0;
	color.b = 0;
	cPos = new CorePosition(5,5);
	this->GraphicsCore->DrawString(CoreFunctions::addIntToString("FPS: ", (int)frameRate), cPos, color);
	delete cPos;
	this->GraphicsCore->EndFrame();

	frameCount++;
}

void AppCore::HandleKeyDown(SDL_Event keyDownEvent)
{
}
