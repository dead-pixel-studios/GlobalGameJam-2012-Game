#pragma once

#include "SpriteBase.h"

class Player : public SpriteBase{
private:
	bool _hitFloor;

	CorePosition _point1, _point2;
	CorePosition _lpoint1, _lpoint2;

	static const int MOVEMENT_FORWARD = 1;
	static const int MOVEMENT_BACKWARD = -1;

	float Gravity;
	float Velocity;

	float maxpixels_persecond_speed;
	float currentspeed;

	float currentframe;
	CoreSize framesize;
	int lastframems;

	float jump_time_length_secs;
	float jump_current_velocity_pixels_sec;
	float jump_elapsed;
	bool jumping;

	bool WorldCollisionCheck();
	CorePosition LandPoint(CorePosition point);
	int tits;

	int _health;
public:
	Player();
	void Update(float dT);
	void Draw();
};