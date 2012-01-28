#include "TestSprite.h"
#include "Universe.h"

TestSprite::TestSprite(){
	this->gEngine = CoreGraphics::Instance();
	this->rotation = 0.0F;

	texture1 = gEngine->CreateTexture(CoreFunctions::GetAppPath() + "/data/bloogy.bmp");
	texture1->Load();
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
	this->gEngine->DrawTexture(texture1,cPos,cSize, this->rotation);
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