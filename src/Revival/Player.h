#pragma once

#include "SpriteBase.h"

class Player : public SpriteBase{
private:
	bool _hitFloor;

	CorePosition _point1, _point2;
	CorePosition _lpoint1, _lpoint2;

	static const int MOVEMENT_FORWARD = 1;
	static const int MOVEMENT_BACKWARD = -1;

	float maxpixels_persecond_speed;
	float currentspeed;

	float jump_time_length;
	float jump_current_velocity_pixels_sec;
	float jump_elapsed;

	bool WorldCollisionCheck();
	CorePosition LandPoint(CorePosition point);
public:
	Player();
	void Update(float dT);
	void Draw();
};