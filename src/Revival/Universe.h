#pragma once

#include "../CoreEngine/CoreGraphics.h"
#include "SpriteBase.h"
#include <set>

class CoreGraphics;

typedef std::set<SpriteBase*> SpriteSet;
typedef SpriteSet::iterator SpriteItr;
typedef std::set<SDLKey> KeySet;

class Universe {
public:
	static Universe* Instance();
	void Update(float fTime);
	void Draw();

	void AddSprite(SpriteBase *sprite);
	void RemoveAndDeleteSprite(SpriteBase *sprite);
	void RemoveAllSprites(bool preserverPlayer=false);
	SpriteSet Universe::CollisionDetect(CorePosition pos, CoreSize box, SpriteBase *ignore=NULL);

	void KeyDown(SDLKey key);
	void KeyUp(SDLKey key);
	
	bool IsKeyDown(SDLKey key);

	SpriteBase *_currentMap;
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
	KeySet _keys;
};