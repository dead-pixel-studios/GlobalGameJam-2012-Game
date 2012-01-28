#pragma once

#include "SpriteBase.h"

class Player : public SpriteBase{
private:
	bool _hitFloor;

	CorePosition _collisionPoint;

	bool WorldCollisionCheck();
public:
	Player();
	void Update(float dT);
};