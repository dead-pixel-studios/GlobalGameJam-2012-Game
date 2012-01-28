#pragma once

#include "SpriteBase.h"

class Player : public SpriteBase {
private:
	bool _hitFloor;

	CorePosition _point1, _point2;
	CorePosition _lpoint1, _lpoint2;

	bool WorldCollisionCheck();
	CorePosition LandPoint(CorePosition point);
public:
	Player();
	void Update(float dT);
	void Draw();
};