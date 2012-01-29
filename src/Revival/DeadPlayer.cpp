#include "DeadPlayer.h"

DeadPlayer::DeadPlayer(EventList events){
	_events=events;
}

void Player::Update(float delta){
	_time_elapsed+=delta;

	float move = 0.0F;
	if(IsKeyDown(SDLK_RIGHT) || IsKeyDown(SDLK_d)){
		move = maxpixels_persecond_speed * delta * MOVEMENT_FORWARD;
		currentDirection = MOVEMENT_FORWARD;
		RecordEvent(EventType::Left);
	} else if (IsKeyDown(SDLK_LEFT) || IsKeyDown(SDLK_a)){
		move = maxpixels_persecond_speed * delta * MOVEMENT_BACKWARD;
		currentDirection =MOVEMENT_BACKWARD;
		RecordEvent(EventType::Right);
	} else {
		currentDirection = 0; // stationary
	}

	if(IsKeyDown(SDLK_LCTRL) || IsKeyDown(SDLK_w) || IsKeyDown(SDLK_UP)) {
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
	if(jump_elapsed >= jump_time_length_secs) {
		jumping = false;
		jump_elapsed = 0.0F;
	}

	Velocity += Gravity;

	_pos.SetX(lpoint1.GetX()-50);
	_pos.SetY((int) (_pos.GetY() + Velocity));

	if(_pos.GetY() > lpoint1.GetY()-_size.GetHeight()) {
		Velocity = 0;
		_pos.SetY(lpoint1.GetY()-_size.GetHeight());
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
	
	if(_health<=0){
		//fade out
		//_visible=false;
		_pos=CorePosition(0,0);
		_health=100;
		_doomed=false;
		std::cout << "DIED!" << std::endl;
		RecordEvent(EventType::Die);
	}	
}