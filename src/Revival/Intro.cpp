#include "Intro.h"
#include "Universe.h"

Intro* Intro::pinstance = 0;
Intro* Intro::Instance () {
	if(pinstance == 0) { pinstance = new Intro; pinstance->Init(); }
	return pinstance;
}

void Intro::Init() {
	this->gEngine = CoreGraphics::Instance();
	this->texture = gEngine->CreateTexture(CoreFunctions::GetAppPath() + "\\data\\intro.png");
	this->texture->Load();

	this->snake = gEngine->CreateTexture(CoreFunctions::GetAppPath() + "\\data\\aaahsnake.png");
	this->snake->Load();

	this->pos = new CorePosition(0,0);
	this->size = new CoreSize(1024,768);

	this->snakepos = new CorePosition(914,658);
	this->snakesize = new CoreSize(100,100);

	this->openedFor = 0;
	this->lastUpdate = 0;
	this->rotation = 0;
	this->haveFinishedIntro = false;
}

void Intro::Update(float fTime)
{
	float tslu = fTime-lastUpdate;
	this->openedFor += tslu;

	if(tslu >= 10) {
		this->lastUpdate = fTime;
		this->rotation += 1.0F;
		if(this->rotation >= 360) {
			this->rotation = 0;
		}
	}

	if(Universe::Instance()->IsKeyDown(SDLK_SPACE)) {
		this->haveFinishedIntro = true;
	}
}

void Intro::Draw()
{
	this->gEngine->DrawTexture(texture,pos,size);
	this->gEngine->DrawTexture(snake,snakepos,snakesize,rotation);
}

bool Intro::finishedIntro()
{
	return haveFinishedIntro;
}