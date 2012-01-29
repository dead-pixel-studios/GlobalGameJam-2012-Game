#pragma once

#include "SpriteBase.h"
#include "Player.h"

class DeadPlayer : public Player{
	EventList _events;
	EventList _master_events;
	bool _started;
public:
	DeadPlayer(EventList events);
	void Start();
	void Update(float);
	void Draw();
};