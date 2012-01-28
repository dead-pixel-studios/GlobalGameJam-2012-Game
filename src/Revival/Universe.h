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

	void rotateP();
	void rotateM();

	void AddSprite(SpriteBase *sprite);

protected:
	Universe(void) {};
	Universe(const Universe&);
	Universe& operator=(const Universe&);
private:
	typedef std::set<SpriteBase*> SpriteSet;
	typedef SpriteSet::iterator SpriteItr;

	static Universe* pinstance;
	void Init();
	float rotation;

	CoreGraphics * gEngine;
	OpenGLTexture * texture1;

	SpriteSet _sprites;
};