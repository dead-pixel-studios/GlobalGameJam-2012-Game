#include "Universe.h"
#include "TestSprite.h"

Universe* Universe::pinstance = 0;
Universe* Universe::Instance () {
	if(pinstance == 0) { pinstance = new Universe; pinstance->Init(); }
	return pinstance;
}

void Universe::Init() {
	currentKeyStatus=SDLK_UNKNOWN;
	AddSprite(new TestSprite());
}

void Universe::AddSprite(SpriteBase *sprite){
	_sprites.insert(sprite);
}

void Universe::Update(float fTime)
{
	for(SpriteItr i=_sprites.begin(); i!=_sprites.end(); ++i){
		SpriteBase *ptr = *i;
		ptr->Update(fTime);
	}
}

void Universe::Draw()
{
	for(SpriteItr i=_sprites.begin(); i!=_sprites.end(); ++i){
		SpriteBase *ptr = *i;
		ptr->Draw();
	}
}