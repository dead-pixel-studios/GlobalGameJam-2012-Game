#include "TestSprite.h"
#include "Universe.h"

TestSprite::TestSprite(){
	this->rotation = 0.0F;

	texture = gEngine->CreateTexture(CoreFunctions::GetAppPath() + "/data/bloogy.bmp");
	texture->Load();
}

void TestSprite::Update(){

	switch(Universe::Instance()->currentKeyStatus) {
	case SDLK_KP_PLUS:
	case SDLK_LEFT:
		rotateP();
		break;
	case SDLK_KP_MINUS:
	case SDLK_RIGHT:
		rotateM();
		break;
	}
}

void TestSprite::Draw(){
	CorePosition * cPos = new CorePosition(100,100);
	CoreSize * cSize = new CoreSize(64,64);
	this->gEngine->DrawTexture(texture,cPos,cSize, this->rotation);
	delete cPos;
	delete cSize;
}

void TestSprite::rotateP()
{
	this->rotation += 1.0F;
}
void TestSprite::rotateM()
{
	this->rotation -= 1.0F;
}