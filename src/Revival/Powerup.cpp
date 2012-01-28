#include "Universe.h"
#include "Powerup.h"

Powerup::Powerup()
{
	texture = gEngine->CreateTexture(CoreFunctions::GetAppPath() + "/data/power-ups/icon-freeze.png");
	texture->Load();
	_size=CoreSize(60,60);
	_pos=CorePosition(720,1080);
	_visible = true;
}

void Powerup::Update(float)
{
}