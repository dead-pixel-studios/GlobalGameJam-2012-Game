#pragma once

#include "../CoreEngine/CoreGraphics.h"
#include <set>

class CoreGraphics;
class SpriteBase;

typedef std::set<SpriteBase*> SpriteSet;
typedef SpriteSet::iterator SpriteItr;
typedef std::set<SDLKey> KeySet;

class SpriteBase{
protected:
	CorePosition _pos;
	CorePosition _origin;
	CoreSize _size;
	float _angle;
	CorePosition _deltaPos;
	int _deltaAngle;

	bool _visible;
	bool _solid;

	CoreGraphics *gEngine;
	OpenGLTexture *texture;

	friend class SpriteZCompare;
	
	void DefaultDraw();
	
	bool IsKeyDown(SDLKey key);
	SpriteSet CollisionDetect();
public:
	SpriteBase();

	virtual void Update(float deltaTime)=0;
	virtual void Draw() {DefaultDraw();}

	virtual CoreColor GetPixel(CorePosition pos);

	CorePosition GetPosition() {return _pos;}
	CoreSize GetSize() {return _size;}
	bool IsVisible();
	bool IsSolid();
};

#include "Universe.h"