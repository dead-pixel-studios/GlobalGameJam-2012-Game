#include "GameOver.h"
#include "Universe.h"

GameOver* GameOver::pinstance = 0;
GameOver* GameOver::Instance () {
	if(pinstance == 0) { pinstance = new GameOver; pinstance->Init(); }
	return pinstance;
}

void GameOver::Init() {
	this->gEngine = CoreGraphics::Instance();

	this->texture = gEngine->CreateTexture(CoreFunctions::GetAppPath() + "\\data\\game-over.png");
	this->texture->Load();

	this->pos = new CorePosition(0,0);
	this->size = new CoreSize(1024,768);

	this->player1 = new CoreController(1);

	this->gameOver = false;
	this->fade = 0.0F;
	fadeaccumulator = 0;
}

void GameOver::Update(float fTime)
{
	fadeaccumulator = fadeaccumulator + fTime;
	if(fadeaccumulator > 10) {
		fadeaccumulator = fTime-fadeaccumulator;
		fade += 0.05F;
	}
}

void GameOver::Draw()
{
	this->gEngine->DrawTexture(texture,pos,&centerPoint, size,-1,this->fade,this->fade,this->fade);
}

void GameOver::GameIsOver()
{
	this->gameOver = true;
}