#include "Universe.h"
#include "Platform.h"
#include "Player.h"

Platform::Platform(CorePosition pos)
{
	this->_size.SetHeight(1536);
	this->_size.SetWidth(3072);
	this->_pos.SetX(0);
	this->_pos.SetY(0);
	this->texture = gEngine->CreateTexture(CoreFunctions::GetAppPath() + "/data/Level1/Level1_Ice.png");
	this->texture->Load();
	this->collision_texture = gEngine->CreateTexture(CoreFunctions::GetAppPath() + "/data/Level1/Level1_Ice_Collision.png");
	this->collision_texture->Load();
	this->_visible = false;
	this->collision_enabled = false;
	this->collision_texture_visible = true;
}

void Platform::Update(float delta)
{
	SpriteSet cols=CollisionDetect();
	Player *player=dynamic_cast<Player*>(Universe::Instance()->_focus);
}

 CoreColor Platform::GetPixel(CorePosition pos){
	 return CoreGraphics::Instance()->getPixelColor(collision_texture->GetSurface(), pos.GetX(), pos.GetY());
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

void Platform::SetEnabled(bool Enabled) {
	this->collision_enabled = Enabled;
}

void Platform::SetVisible(bool value) {
	this->_visible = value;
}