#include "SpriteBase.h"

SpriteBase::SpriteBase(){
	_angle=0;
	this->gEngine = CoreGraphics::Instance();
}

void SpriteBase::DefaultDraw(){
	this->gEngine->DrawTexture(texture,&_pos,&_size,_angle);
}
