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
	_currentMap=new TestMap();
	AddSprite(_currentMap);
	_focus=new Player();
	AddSprite(_focus);
}

void Universe::AddSprite(SpriteBase *sprite){
	_sprites.insert(sprite);
}

void Universe::Update(float fTime)
{
	CorePosition focusPos=_focus->GetPosition();
	focusPos.SetX(focusPos.GetX()-512);
	focusPos.SetY(focusPos.GetY()-384);
	focusPos.SetX(focusPos.GetX()+_focus->GetSize().GetWidth()/2);
	focusPos.SetY(focusPos.GetY()+_focus->GetSize().GetHeight()/2);
	_worldOffset=focusPos;
	if(_worldOffset.GetX()<0) _worldOffset.SetX(0);
	if(_worldOffset.GetY()<0) _worldOffset.SetY(0);
	if(_worldOffset.GetX()+1024>_currentMap->GetSize().GetWidth()) _worldOffset.SetX(_currentMap->GetSize().GetWidth()-1024);
	if(_worldOffset.GetY()+768>_currentMap->GetSize().GetHeight()) _worldOffset.SetY(_currentMap->GetSize().GetHeight()-768);

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