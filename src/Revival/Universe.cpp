#include "Universe.h"
#include "TestSprite.h"
#include "TestMap.h"
#include "Player.h"

Universe* Universe::pinstance = 0;
Universe* Universe::Instance () {
	if(pinstance == 0) { pinstance = new Universe; pinstance->Init(); }
	return pinstance;
}

void Universe::Init() {
	//AddSprite(new TestSprite());
	_currentMap=new TestMap();
	AddSprite(_currentMap);
	AddSprite(new Player());
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

void Universe::KeyDown(SDLKey key){
	_keys.insert(key);
}

void Universe::KeyUp(SDLKey key){
	_keys.erase(key);
}

bool Universe::IsKeyDown(SDLKey key){
	return _keys.count(key);
}