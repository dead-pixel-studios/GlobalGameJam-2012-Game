#include "Universe.h"
#include "TestSprite.h"
#include "TestMap.h"
#include "Player.h"
#include <iostream>

SDL_bool SDL_HasIntersection(const SDL_Rect * A, const SDL_Rect * B)
{
    int Amin, Amax, Bmin, Bmax;

    /* Horizontal intersection */
    Amin = A->x;
    Amax = Amin + A->w;
    Bmin = B->x;
    Bmax = Bmin + B->w;
    if (Bmin > Amin)
        Amin = Bmin;
    if (Bmax < Amax)
        Amax = Bmax;
    if (Amax <= Amin)
        return SDL_FALSE;

    /* Vertical intersection */
    Amin = A->y;
    Amax = Amin + A->h;
    Bmin = B->y;
    Bmax = Bmin + B->h;
    if (Bmin > Amin)
        Amin = Bmin;
    if (Bmax < Amax)
        Amax = Bmax;
    if (Amax <= Amin)
        return SDL_FALSE;

    return SDL_TRUE;
}

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

	for(SpriteItr i=_deletes.begin(); i!=_deletes.end(); ++i){
		_sprites.erase(*i);
		delete *i;
	}
	_deletes.clear();
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
	return (bool) _keys.count(key);
}

SpriteSet Universe::CollisionDetect(CorePosition pos, CoreSize size, SpriteBase *ignore){
	SpriteSet ret;
	SDL_Rect priRect;
	priRect.x=pos.GetX();
	priRect.y=pos.GetY();
	priRect.w=size.GetWidth();
	priRect.h=size.GetHeight();
	for(SpriteItr i=_sprites.begin();i!=_sprites.end();++i){
		if(*i!=ignore){
			SpriteBase *sprite=*i;
			if(sprite->IsVisible() && sprite->IsSolid()){
				SDL_Rect secRect;
				secRect.x=sprite->GetPosition().GetX();
				secRect.y=sprite->GetPosition().GetY();
				secRect.w=sprite->GetSize().GetWidth();
				secRect.h=sprite->GetSize().GetHeight();
				if(SDL_HasIntersection(&priRect, &secRect)){
					ret.insert(sprite);
				}
			}
		}
	}
	return ret;
}

void Universe::RemoveAndDeleteSprite(SpriteBase *sprite){
	_deletes.insert(sprite);
}