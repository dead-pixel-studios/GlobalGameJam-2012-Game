#include "Universe.h"
#include "Powerup.h"
#include "Player.h"

Powerup::Powerup(CorePosition pos, PowerupType::Enum type)
{
	texture = gEngine->CreateTexture(CoreFunctions::GetAppPath() + "/data/power-ups/icon-freeze.png");
	texture->Load();
	_size=CoreSize(60,60);
	_pos=pos;
	_visible = true;
}

void Powerup::Update(float)
{
	SpriteSet cols=CollisionDetect();
	Player *player=dynamic_cast<Player*>(Universe::Instance()->_focus);
	if(cols.count(player)){
		Universe::Instance()->RemoveAndDeleteSprite(this);
	}
}