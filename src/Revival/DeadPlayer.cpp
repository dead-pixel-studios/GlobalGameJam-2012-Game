#include "DeadPlayer.h"

#include <iostream>

DeadPlayer::DeadPlayer(EventList events)
{

	_master_events=events;
	_started=false;
	_visible=false;
	_solid=false;
}

void DeadPlayer::Start(){
	_events=_master_events;
	_started=true;
	_visible=true;
	_solid=true;
	_time_elapsed=0.0;
}

void DeadPlayer::Update(float delta){
	if(!_started) return;

	_time_elapsed+=delta;

	PlayerEvent currentEvent;

	if(!_events.empty() && _time_elapsed>_events.front().time){
		currentEvent=_events.front();
		_events.pop_front();
	}else{
		currentEvent.type=EventType::None;
		return;
	}

	float move = 0.0F;
	if(currentEvent.type==EventType::Left){
		_pos=currentEvent.pos;
		move = maxpixels_persecond_speed * delta * MOVEMENT_FORWARD;
		currentDirection = MOVEMENT_FORWARD;
	} else if (currentEvent.type==EventType::Right){
		_pos=currentEvent.pos;
		move = maxpixels_persecond_speed * delta * MOVEMENT_BACKWARD;
		currentDirection =MOVEMENT_BACKWARD;
	} else {
		currentDirection = 0; // stationary
	}

	if(currentEvent.type==EventType::Jump) {
		_pos=currentEvent.pos;
		RecordEvent(EventType::Jump);
		if (jumping != true) {
			Velocity = -30.0F;
			jumping = true;
		}
	}

	// move Y (up down)
	CorePosition lpoint1 = LandPoint(_point1);
	CorePosition lpoint2 = LandPoint(_point2);

	jump_elapsed += delta / 100;
	//if(jump_elapsed >= jump_time_length_secs) {
		//jumping = false;
		//jump_elapsed = 0.0F;
	//}

	Velocity += Gravity;

	_pos.SetX(lpoint1.GetX()-50);
	_pos.SetY((int) (_pos.GetY() + Velocity));

	if(_pos.GetY() > lpoint1.GetY()-_size.GetHeight()) {
		Velocity = 0;
		_pos.SetY(lpoint1.GetY()-_size.GetHeight());
		jumping = false;
	}

	// move X (left right)
	float wantedx = _pos.GetX() + move;
	float min_x = 0.0F;
	float max_x = (float) Universe::Instance()->_currentMap->GetSize().GetWidth() - this->_size.GetWidth();
	if(wantedx >= min_x && wantedx <= max_x) {
		_pos.SetX((int) wantedx);
	}

	// rotation using ray-tracing
	double angle=atan2((double)lpoint2.GetY() - lpoint1.GetY(), (double)lpoint2.GetX() - lpoint1.GetX()) * 180 / 3.14159;
	if(angle>60.0) angle=60.0;
	if(angle<-60.0) angle=-60.0;
	if(angle<=0) angle+=360.0;
	_angle=(float) angle;


	frame_accumulator += delta ;
	while (frame_accumulator >= (800.00/8)) {
		frame_accumulator -= (800.0F/8);
		if(this->_pos.GetX() != this->lastupdatepos.GetX() || this->_pos.GetY() != this->lastupdatepos.GetY()) {
			currentframe++;
			currentframe = currentframe % 8;
		} else {
			currentframe = 0;
		}
	}


	if(Universe::Instance()->_currentMap->IsKillZone(_pos+_point1)) _doomed=true;
	if(_doomed) _health-=10;
	
	if(currentEvent.type==EventType::Die){
		_pos=currentEvent.pos;
		//fade out
		//_visible=false;
		_pos=CorePosition(0,0);
		_health=100;
		_doomed=false;
		Start();

		std::cout << "DeadPlayer DIED!" << std::endl;
	}

	
}