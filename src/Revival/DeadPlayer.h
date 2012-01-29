#pragma once

#include "Player.h"

class DeadPlayer : public Player{
	EventList _events;
public:
	DeadPlayer(EventList events);
	void Start();
	void Update();
}