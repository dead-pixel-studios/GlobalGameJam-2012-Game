#include "Universe.h"
#include "TestMap.h"
#include <iostream>

TestMap::TestMap()
{
	texture = gEngine->CreateTexture(CoreFunctions::GetAppPath() + "/data/Level1/background.png");
	texture->Load();

	backgroundMist = gEngine->CreateTexture(CoreFunctions::GetAppPath() + "/data/Level1/MistBackground.png");
	backgroundMist->Load();

	foreground = gEngine->CreateTexture(CoreFunctions::GetAppPath() + "/data/Level1/Foreground.png");
	foreground->Load();

	foregroundMist = gEngine->CreateTexture(CoreFunctions::GetAppPath() + "/data/Level1/MistForeground.png");
	foregroundMist->Load();

	collision = gEngine->CreateTexture(CoreFunctions::GetAppPath() + "/data/Level1/Collision.png");
	collision->Load();

	lava1 = gEngine->CreateTexture(CoreFunctions::GetAppPath() + "/data/Level1/Lava1.png");
	lava1->Load();

	lava2 = gEngine->CreateTexture(CoreFunctions::GetAppPath() + "/data/Level1/Lava2.png");
	lava2->Load();

	lava3 = gEngine->CreateTexture(CoreFunctions::GetAppPath() + "/data/Level1/Lava3.png");
	lava3->Load();

	killzone = gEngine->CreateTexture(CoreFunctions::GetAppPath() + "/data/Level1/KillZone.png");
	killzone->Load();

	_size=CoreSize(3072,1536);
	_pos=CorePosition(0,0);

	_backgroundmistPos=CorePosition(0,0);
	_foregroundmistPos=CorePosition(0,0);

	_pwrUp = new Powerup(CorePosition(800,1080), PowerupType::Freeze);
	Universe::Instance()->AddSprite(_pwrUp);

	this->_icePlatform = new Platform(CorePosition(700, 1000));
	Universe::Instance()->AddSprite(_icePlatform);
	this->platforms.push_back(_icePlatform);
	
	_visible=true;
	lastMistScroll = 0.0F;
	lastLavaChange = 0.0F;
	lavaStep = 0;
}

void TestMap::Update(float fTime)
{
	/*if(fTime-lastMistScroll > 10) {
		lastMistScroll = fTime;
		if(_pos.GetY()>0-768) {
			_pos.SetY(_pos.GetY()-1);
		}
		_backgroundmistPos.SetX(_backgroundmistPos.GetX() - 1);
		_foregroundmistPos.SetX(_foregroundmistPos.GetX() - 2);
	}*/

	if(fTime-lastLavaChange > 100) {
		lastLavaChange = fTime;
		lavaStep++;
		if(lavaStep>2) { lavaStep = 0; }
	}
}

void TestMap::Draw()
{
	if(_visible) {
		CorePosition ofs=Universe::Instance()->_worldOffset;
		CorePosition adjpos=_pos-ofs;
		this->gEngine->DrawTexture(texture,&adjpos,&centerPoint,&_size,_angle);
		this->gEngine->DrawTexture(backgroundMist,&_backgroundmistPos,&centerPoint,&_size,_angle);
		this->gEngine->DrawTexture(foreground,&adjpos,&centerPoint,&_size,_angle);

		switch(lavaStep) {
		case 0:
			this->gEngine->DrawTexture(lava1,&adjpos,&centerPoint,&_size,_angle);
			break;
		case 1:
			this->gEngine->DrawTexture(lava2,&adjpos,&centerPoint,&_size,_angle);
			break;
		case 2:
			this->gEngine->DrawTexture(lava3,&adjpos,&centerPoint,&_size,_angle);
			break;
		}
		this->gEngine->DrawTexture(foregroundMist,&_foregroundmistPos,&centerPoint,&_size,_angle);

		CorePosition * textPos = new CorePosition(10,10);
		SDL_Color color;
		color.r = 255;
		color.g = 0;
		color.b = 0;
		this->gEngine->DrawString(CoreFunctions::addIntToString("PosY: ", _pos.GetY()),textPos,color);

		//_pwrUp->Draw();
	}
}

CoreColor TestMap::GetPixel(CorePosition pos){
		return gEngine->getPixelColor(collision->GetSurface(), pos.GetX(), pos.GetY());
}

bool TestMap::IsKillZone(CorePosition pos){

	bool ret=gEngine->getPixelColor(killzone->GetSurface(), pos.GetX(), pos.GetY()).rgba() == 0xff0000ff;

	// if there are any visible platforms first, then the player is safe and stood on a platform (ish)
	for(int i = 0; i < (int) platforms.size(); i++) {
		Platform * ref = platforms.at(i);

		if(ref->GetPixel(pos).rgba() == 0xff0000ff) {
			if(ref->IsVisible() == true) {
				ret=false;
			}
		}
	}
	return ret;
}