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
	this_powerup_type = type;
}

void Powerup::Update(float)
{
	SpriteSet cols=CollisionDetect();
	Player *player=dynamic_cast<Player*>(Universe::Instance()->_focus);
	if(cols.count(player)){
		//todo: player now has a powerup in his inventory
		player->powerups.push_back(this_powerup_type);

		//for now, just show and enable the ice bridge
		//Universe::Instance()->_currentMap->platforms.at(0)->SetEnabled(true);
		//Universe::Instance()->_currentMap->platforms.at(0)->SetVisible(true);
		Universe::Instance()->RemoveAndDeleteSprite(this);
	}
}