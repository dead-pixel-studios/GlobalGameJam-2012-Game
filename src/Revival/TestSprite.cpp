#include "TestSprite.h"
#include "Universe.h"

TestSprite::TestSprite(){
	this->rotation = 0.0F;

	texture = gEngine->CreateTexture(CoreFunctions::GetAppPath() + "/data/bloogy.bmp");
	texture->Load();

	_size=CoreSize(64,64);
	_pos=CorePosition(100,100);
}

void TestSprite::Update(float){
	switch(Universe::Instance()->currentKeyStatus) {
	case SDLK_KP_PLUS:
	case SDLK_RIGHT:
		rotateP();
		break;
	case SDLK_KP_MINUS:
	case SDLK_LEFT:
		rotateM();
		break;
	}
}

void TestSprite::rotateP()
{
	_angle += 1.0F;
}
void TestSprite::rotateM()
{
	_angle -= 1.0F;
	if(_angle<=0) _angle+=360.0F;
}