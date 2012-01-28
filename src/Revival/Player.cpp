#include "Universe.h"
#include "Player.h"
#include "Intro.h"

#include <iostream>
#include <cmath>

CoreSize sz33(3,3);

Player::Player(){

	this->tits = 0;
	this->maxpixels_persecond_speed = 0.8F;

	this->texture = gEngine->CreateTexture(CoreFunctions::GetAppPath() + "/data/Walking/FinalWalkRight.bmp");
	this->texture->Load();
	
	this->_size=CoreSize(145,250);
	this->_pos=CorePosition(0,0);

	this->_point1=CorePosition(50, 250);
	this->_point2=CorePosition(100,250);
	this->_origin=_point1;

	this->jump_time_length_secs = 5.0F; // how long it takes to jump
	this->jump_current_velocity_pixels_sec = 1.0F; // current jump velocity (pixels per second) (for acceleration)
	this->jump_elapsed = 0.0F; // current jump
	this->jumping = false;

	this->_visible=true;

	this->Gravity = 2.5;
	this->Velocity= 0;

	this->currentspeed = 0;
	this->currentframe = 0;
	this->framesize = CoreSize(_size.GetWidth(), _size.GetHeight());
}

void Player::Update(float delta){


	float move = 0.0F;
	if(IsKeyDown(SDLK_RIGHT)){
		move = maxpixels_persecond_speed * delta * MOVEMENT_FORWARD;
	}
	if(IsKeyDown(SDLK_LEFT)){
		move = maxpixels_persecond_speed * delta * MOVEMENT_BACKWARD;
	}
	//if((jump_elapsed >= jump_time_length_secs) || (Intro::Instance()->finishedIntro() == true && IsKeyDown(SDLK_LCTRL))) {
	//	jumping = true;
	//}
	if(IsKeyDown(SDLK_LCTRL)) {
		Velocity = -24.0F;
	}

	// move Y (up down)
	CorePosition lpoint1 = LandPoint(_point1);
	CorePosition lpoint2 = LandPoint(_point2);

	int jump_move_y_by = 0;

	//// jumping
	//if(jumping) {
	//	  if (jump_elapsed < (jump_time_length_secs)) {
	//		// starting to jump
	//		// first third of jump animation
	//		jump_move_y_by = delta * 1;
	//		lpoint1.SetY(lpoint1.GetY() - jump_move_y_by);
	//		lpoint2.SetY(lpoint2.GetY() - jump_move_y_by);
	//	}
	//	jump_elapsed += delta / 1000;
	//}

	//if(jumping) {
	//	Velocity = -14.0F;
	//}


	Velocity += Gravity;

	if(jump_elapsed >= jump_time_length_secs) {
		jumping = false;
		jump_elapsed = 0.0F;
	}

	//_lpoint1=lpoint1; // left collision detect point 
	//_lpoint2=lpoint2; // right collision detect point

	_pos.SetX(lpoint1.GetX()-50);
	_pos.SetY(_pos.GetY() + Velocity);

	if(_pos.GetY() > lpoint1.GetY()-_size.GetHeight()) {
		Velocity = 0;
		_pos.SetY(lpoint1.GetY()-_size.GetHeight());
	}
	//_pos.SetY(lpoint1.GetY()-_size.GetHeight());

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

	SDL_Rect * bacon = new SDL_Rect();
	bacon->h = 0.1;
	bacon->w = 0.1;
	bacon->x = 0.1;
	bacon->y = 0.1;

	//SDL_SetClipRect(this->texture->GetSurface(), bacon);

	// Draw the sprite
	if(_visible){
		CorePosition drawPosition=_pos;
		drawPosition.SetX(drawPosition.GetX()-Universe::Instance()->_worldOffset.GetX());
		drawPosition.SetY(drawPosition.GetY()-Universe::Instance()->_worldOffset.GetY());
		this->gEngine->DrawTextureFrame(texture,&drawPosition,&_origin,&_size,_angle,8,tits++%8);
	}

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