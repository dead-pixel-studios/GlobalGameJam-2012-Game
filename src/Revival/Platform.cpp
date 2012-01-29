#include "Universe.h"
#include "Platform.h"
#include "Player.h"

Platform::Platform(CorePosition pos)
{
	this->_size.SetHeight(10);
	this->_size.SetWidth(400);
	this->_pos.SetX(pos.GetX());
	this->_pos.SetY(pos.GetY());
	texture = gEngine->CreateTexture(CoreFunctions::GetAppPath() + "/data/Lvl1Ice.png");
	texture->Load();
	this->_visible = true;
}

void Platform::Update(float delta)
{
	SpriteSet cols=CollisionDetect();
	Player *player=dynamic_cast<Player*>(Universe::Instance()->_focus);
}

bool Platform::PlayerWithinBounds()
{
	SpriteSet cols=CollisionDetect();
	Player *player=dynamic_cast<Player*>(Universe::Instance()->_focus);
	if(cols.count(player)){
		return true;
	} else { 
		return false;
	}
}