#include "Universe.h"
#include "Player.h"
#include "Intro.h"

#include <iostream>
#include <cmath>

CoreSize sz33(3,3);

Player::Player(){
	maxpixels_persecond_speed = 0.8F;

	texture = gEngine->CreateTexture(CoreFunctions::GetAppPath() + "/data/character.png");
	texture->Load();
	_size=CoreSize(145,250);
	_pos=CorePosition(0,0);

	_point1=CorePosition(50, 250);
	_point2=CorePosition(100,250);
	_origin=_point1;

	this->jump_time_length_secs = 5.0F; // how long it takes to jump
	this->jump_current_velocity_pixels_sec = 1.0F; // current jump velocity (pixels per second) (for acceleration)
	this->jump_elapsed = 0.0F; // current jump
	this->jumping = false;

	_visible=true;

	this->currentspeed = 0;
}

void Player::Update(float delta){

	float move = 0.0F;
	if(IsKeyDown(SDLK_RIGHT)){
		move = maxpixels_persecond_speed * delta * MOVEMENT_FORWARD;
	}
	if(IsKeyDown(SDLK_LEFT)){
		move = maxpixels_persecond_speed * delta * MOVEMENT_BACKWARD;
	}
	if((jump_elapsed >= jump_time_length_secs) || (Intro::Instance()->finishedIntro() == true && IsKeyDown(SDLK_LCTRL))) {
		jumping = true;
	}

	// move Y (up down)
	CorePosition lpoint1=LandPoint(_point1);
	CorePosition lpoint2=LandPoint(_point2);

	int jump_move_y_by = 0;

	// jumping
	if(jumping) {
		  if (jump_elapsed < (jump_time_length_secs)) {
			// starting to jump
			// first third of jump animation
			jump_move_y_by = delta / 1;
			lpoint1.SetY(lpoint1.GetY() - jump_move_y_by);
			lpoint2.SetY(lpoint2.GetY() - jump_move_y_by);
		}
		jump_elapsed += delta;
	}

	if(jump_elapsed >= jump_time_length_secs) {
		jumping = false;
		jump_elapsed = 0.0F;
	}

	_lpoint1=lpoint1;
	_lpoint2=lpoint2;
	CorePosition * position_includinglowestpoints = new CorePosition(lpoint1.GetX()-50, lpoint1.GetY()-_size.GetHeight());
	_pos.SetX(position_includinglowestpoints->GetX());
	_pos.SetY(position_includinglowestpoints->GetY());

	// move X (left right)
	float wantedx = _pos.GetX() + move;
	float min_x = 0.0F;
	float max_x = Universe::Instance()->_currentMap->GetSize().GetWidth() - this->_size.GetWidth();
	if(wantedx >= min_x && wantedx <= max_x) {
		_pos.SetX(wantedx);
	}
	// rotation using ray-tracing
	double angle=atan2((double)lpoint2.GetY() - lpoint1.GetY(), (double)lpoint2.GetX() - lpoint1.GetX()) * 180 / 3.14159;
	if(angle>60.0) angle=60.0;
	if(angle<-60.0) angle=-60.0;
	if(angle<=0) angle+=360.0;
	_angle=angle;
}

void Player::Draw(){
	CorePosition cpoint1=_lpoint1-Universe::Instance()->_worldOffset;
	CorePosition cpoint2=_lpoint1-Universe::Instance()->_worldOffset;

	// Draw the sprite
	DefaultDraw();

	// Draw the two ray-tracing dots (over the sprite)
	gEngine->DrawRectangle(&cpoint1, &sz33 ,0xff,0,0,0xff);
	gEngine->DrawRectangle(&cpoint2, &sz33 ,0xff,0,0,0xff);
}

bool Player::WorldCollisionCheck(){
	static Uint32 lastCol=0;

	CorePosition posToCheck=_point1;
	posToCheck.SetX(posToCheck.GetX()+_pos.GetX());
	posToCheck.SetY(posToCheck.GetY()+_pos.GetY());

	CoreColor pxl=Universe::Instance()->_currentMap->GetPixel(posToCheck);
	Uint32 col=pxl.rgba();

	return (col==0x000000ff);
}

CorePosition Player::LandPoint(CorePosition point){
	bool hit=false;

	CorePosition startPoint=point;
	startPoint.SetY(0);
	startPoint.SetX(_pos.GetX()+point.GetX());
	while(!hit){
		startPoint.SetY(startPoint.GetY()+1);
		if(startPoint.GetY()>6000) break; // don't go on forever, give up after 6000 down

		CoreColor pxl=Universe::Instance()->_currentMap->GetPixel(startPoint);
		Uint32 col=pxl.rgba();

		hit=(col==0x000000ff);
	}
	return startPoint;
}