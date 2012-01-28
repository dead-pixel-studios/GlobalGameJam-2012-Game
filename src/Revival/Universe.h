#pragma once

#include "../CoreEngine/CoreGraphics.h"
#include "SpriteBase.h"
#include "Map.h"
#include <set>

class CoreGraphics;

class Universe {
public:
	static Universe* Instance();
	void Update(float fTime);
	void Draw();

	void AddSprite(SpriteBase *sprite);
	void RemoveAndDeleteSprite(SpriteBase *sprite);
	void RemoveAllSprites(bool preserverPlayer=false);
	SpriteSet CollisionDetect(CorePosition pos, CoreSize box, SpriteBase *ignore=NULL);

	void KeyDown(SDLKey key);
	void KeyUp(SDLKey key);
	
	bool IsKeyDown(SDLKey key);

	Map *_currentMap;
	SpriteBase *_focus;

	CorePosition _worldOffset;
protected:
	Universe(void) {};
	Universe(const Universe&);
	Universe& operator=(const Universe&);
private:
	static Universe* pinstance;
	void Init();
	float rotation;

	SpriteSet _sprites;
	SpriteSet _deletes;
	KeySet _keys;
};