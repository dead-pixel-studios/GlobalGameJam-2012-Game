#include "Intro.h"
#include "Universe.h"

CorePosition center(-1,-1);

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

	this->loadico = gEngine->CreateTexture(CoreFunctions::GetAppPath() + "\\data\\loading.png");
	this->loadico->Load();

	this->pos = new CorePosition(0,0);
	this->size = new CoreSize(1024,768);

	this->snakepos = new CorePosition(914,658);
	this->snakesize = new CoreSize(100,100);

	this->loadpos = new CorePosition(753,727);
	this->loadsize = new CoreSize(151,31);

	this->openedFor = 0;
	this->lastUpdate = 0;
	this->rotation = 0;
	this->haveFinishedIntro = false;
	this->fadeIn = true;
	this->fade = 0.0F;

	this->player1 = new CoreController(1);

	this->accumulator = 0;
	loadaccu = 0;

	this->loading = true;
}

void Intro::Update(float fTime)
{
	accumulator = accumulator + fTime;
	loadaccu = loadaccu + fTime;

	if(loadaccu > 5) {
		loadaccu = fTime-loadaccu;
		if(this->loading) {
			if(fadeIn) {
				this->fade += 0.05F;
				if(this->fade >= 1.0F) {
					fadeIn = false;
				}
			}
			else {
				fade -= 0.05F;
				if(this->fade <= 0.0F) {
					this->loading = false;
					fadeIn = true;
				}
			}
		}
	}
	if(accumulator >= 10) {
		accumulator = fTime - accumulator;

		if(!this->loading) {
			if(this->fadeIn) {
				this->fade +=  0.05F;
				if(this->fade >= 1.0F) {
					this->fadeIn = false;
				}
			}
			else {
				this->rotation -= 1.5F;
				if(this->rotation <= 0) {
					this->rotation = 360;
				}
			}
		}
	}

	if(!this->loading) {
			if(!fadeIn) {
				if(Universe::Instance()->IsKeyDown(SDLK_SPACE)) {
					this->haveFinishedIntro = true;
				}
				if(player1->IsConnected()) {
					if(player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_START) {
						this->haveFinishedIntro = true;
					}
				}
			}
	}
}

void Intro::Draw()
{
	if(loading) {
		float r, g, b, a;
		r = CoreFunctions::GenerateRandomNumberBetween(0.0F,1.0F);
		g = CoreFunctions::GenerateRandomNumberBetween(0.0F,1.0F);
		b = CoreFunctions::GenerateRandomNumberBetween(0.0F,1.0F);
		a = 1.0F;
		this->gEngine->DrawTexture(snake,snakepos,&centerPoint, snakesize ,rotation,r,g,b,a);
		this->gEngine->DrawTexture(loadico,loadpos,&centerPoint,loadsize, -1, fade,fade,fade);
	}
	else {
		this->gEngine->DrawTexture(texture,pos,&centerPoint, size,-1,this->fade,this->fade,this->fade);
	}
}

bool Intro::finishedIntro()
{
	return haveFinishedIntro;
}