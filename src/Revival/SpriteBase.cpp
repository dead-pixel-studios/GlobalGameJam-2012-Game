#include "SpriteBase.h"
#include "Universe.h"

SpriteBase::SpriteBase(){
	_angle=0;
	this->gEngine = CoreGraphics::Instance();
}

void SpriteBase::DefaultDraw(){
	this->gEngine->DrawTexture(texture,&_pos,&_size,_angle);
}

bool SpriteBase::IsKeyDown(SDLKey key){
	return Universe::Instance()->IsKeyDown(key);
}