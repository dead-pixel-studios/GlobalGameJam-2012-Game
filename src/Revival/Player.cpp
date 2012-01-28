#include "Player.h"
#include "Universe.h"

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
	float wantedx = _pos.GetX() + move;
	float min_x = 0.0F;
	float max_x = Universe::Instance()->_currentMap->GetSize().GetWidth();
	if(wantedx >= min_x && wantedx <= max_x) {
		_pos.SetX(wantedx);
	}

	CorePosition lpoint1=LandPoint(_point1);
	CorePosition lpoint2=LandPoint(_point2);
	_lpoint1=lpoint1;
	_lpoint2=lpoint2;

	_pos=CorePosition(lpoint1.GetX()-50, lpoint1.GetY()-_size.GetHeight());

	double angle=atan2((double)lpoint2.GetY() - lpoint1.GetY(), (double)lpoint2.GetX() - lpoint1.GetX()) * 180 / 3.14159;
	if(angle>60.0) angle=60.0;
	if(angle<-60.0) angle=-60.0;
	if(angle<=0) angle+=360.0;
	_angle=angle;
}

void Player::Draw(){
	CorePosition cpoint1=_lpoint1-Universe::Instance()->_worldOffset;
	CorePosition cpoint2=_lpoint1-Universe::Instance()->_worldOffset;
	gEngine->DrawRectangle(&cpoint1, &sz33 ,0xff,0,0,0xff);
	gEngine->DrawRectangle(&cpoint2, &sz33 ,0xff,0,0,0xff);
	DefaultDraw();
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