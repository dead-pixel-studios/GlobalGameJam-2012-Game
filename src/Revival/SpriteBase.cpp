#include "SpriteBase.h"
#include "Universe.h"

SpriteBase::SpriteBase(){
	_angle=0;
	_visible=false;
	_origin=CorePosition(-1,-1);
	this->gEngine = CoreGraphics::Instance();
}

void SpriteBase::DefaultDraw(){
	if(_visible) this->gEngine->DrawTexture(texture,&_pos,&_origin,&_size,_angle);
}

bool SpriteBase::IsKeyDown(SDLKey key){
	return Universe::Instance()->IsKeyDown(key);
}

CoreColor SpriteBase::GetPixel(CorePosition pos){
	return gEngine->getPixelColor(texture->GetSurface(), pos.GetX(), pos.GetY());
}