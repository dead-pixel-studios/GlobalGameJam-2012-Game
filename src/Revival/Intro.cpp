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
	this->fadeIn = true;
	this->fade = 0.0F;

	this->player1 = new CoreController(1);
}

void Intro::Update(float fTime)
{
	float tslu = fTime-lastUpdate;
	this->openedFor += tslu;

	if(tslu >= 10) {
		this->lastUpdate = fTime;

		if(this->fadeIn) {
			this->fade += 0.005F;
			if(this->fade >= 1.0F) {
				this->fadeIn = false;
			}
		}
		else {
			this->rotation += 1.0F;
			if(this->rotation >= 360) {
				this->rotation = 0;
			}
		}
	}

	if(Universe::Instance()->IsKeyDown(SDLK_SPACE)) {
		this->haveFinishedIntro = true;
	}

	if(player1->IsConnected()) {
		if(player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_START) {
			this->haveFinishedIntro = true;
		}
	}
}

void Intro::Draw()
{
	this->gEngine->DrawTexture(texture,pos,size,-1,this->fade,this->fade,this->fade);
	float r, g, b, a;
	r = CoreFunctions::GenerateRandomNumberBetween(0.0F,1.0F);
	g = CoreFunctions::GenerateRandomNumberBetween(0.0F,1.0F);
	b = CoreFunctions::GenerateRandomNumberBetween(0.0F,1.0F);
	a = 1.0F;
	this->gEngine->DrawTexture(snake,snakepos,snakesize,rotation,r,g,b,a);
}

bool Intro::finishedIntro()
{
	return haveFinishedIntro;
}