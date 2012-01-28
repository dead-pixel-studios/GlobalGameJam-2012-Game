#pragma once

#include "../CoreEngine/CoreGraphics.h"
#include "SpriteBase.h"
#include <set>

class CoreGraphics;

class Universe {
public:
	static Universe* Instance();
	void Update(float fTime);
	void Draw();

	void AddSprite(SpriteBase *sprite);

	void KeyDown(SDLKey key);
	void KeyUp(SDLKey key);
	
	bool IsKeyDown(SDLKey key);

	SpriteBase *_currentMap;
protected:
	Universe(void) {};
	Universe(const Universe&);
	Universe& operator=(const Universe&);
private:
	typedef std::set<SpriteBase*> SpriteSet;
	typedef SpriteSet::iterator SpriteItr;
	typedef std::set<SDLKey> KeySet;

	static Universe* pinstance;
	void Init();
	float rotation;

	SpriteSet _sprites;
	KeySet _keys;
};