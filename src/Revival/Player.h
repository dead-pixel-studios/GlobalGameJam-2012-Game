#pragma once

#include "SpriteBase.h"
#include <vector>
#include <list>
#include "Powerup.h"
#include "../CoreEngine/CoreController.h"
#include "GameOver.h"

class DeadPlayer;

namespace EventType{
	enum Enum{
		None,
		Left,
		Right,
		Jump,
		Die,
		Hurt,
		PosChange
	};
}

struct PlayerEvent{
	double time;
	EventType::Enum type;
	CorePosition pos;
	OpenGLTexture *tex;
	int frames, currentframe;
};

typedef std::list<PlayerEvent> EventList;

class Player : public SpriteBase{
private:
	CoreController * player1;
protected:
	bool _hitFloor;
	
	int currentDirection;

	OpenGLTexture *movingforward_sprites_texture;
	OpenGLTexture *movingbackwards_sprites_texture;
	OpenGLTexture *staticiso_sprite_texture;
	OpenGLTexture *jumpleft_texture;
	OpenGLTexture *jumpright_texture;

	OpenGLTexture *lavadeath_left;
	OpenGLTexture *lavadeath_right;

	OpenGLTexture *ghost_movingforward_sprites_texture;
	OpenGLTexture *ghost_movingbackwards_sprites_texture;
	OpenGLTexture *ghost_staticiso_sprite_texture;
	OpenGLTexture *ghost_jumpleft_texture;
	OpenGLTexture *ghost_jumpright_texture;

	CorePosition _point1, _point2;
	CorePosition _lpoint1, _lpoint2;

	static const int MOVEMENT_FORWARD = 1;
	static const int MOVEMENT_BACKWARD = -1;

	float Gravity;
	float Velocity;

	float maxpixels_persecond_speed;
	CorePosition lastupdatepos;

	int frames, currentframe;
	float frame_accumulator;

	float jump_time_length_secs;
	float jump_current_velocity_pixels_sec;
	float jump_elapsed;

	float death_accumulator;
	float death_fade;
	bool jumping;
	bool _doomed;
	bool dead;

	int _health;
	double _time_elapsed;

	int thumblx;
	int thumbly;

	EventList _recorded_events;

	bool WorldCollisionCheck();
	void RecordEvent(EventType::Enum event);
	CorePosition LandPoint(CorePosition point);

public:
	vector<Powerup*> powerups;
	Player();
	virtual void Update(float dT);
	virtual void Draw();
};

#include "DeadPlayer.h"