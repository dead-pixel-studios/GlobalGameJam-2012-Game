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
	if(IsKeyDown(SDLK_KP_PLUS) || IsKeyDown(SDLK_RIGHT)) rotateP();
	if(IsKeyDown(SDLK_KP_MINUS) || IsKeyDown(SDLK_LEFT)) rotateM();
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