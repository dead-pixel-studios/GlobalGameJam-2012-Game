#include "Player.h"
#include "Universe.h"

#include <iostream>
#include <cmath>

CoreSize sz33(3,3);

Player::Player(){
	texture = gEngine->CreateTexture(CoreFunctions::GetAppPath() + "/data/character.png");
	texture->Load();
	_size=CoreSize(145,250);
	_pos=CorePosition(0,0);

	_point1=CorePosition(50, 250);
	_point2=CorePosition(100,250);
	_origin=_point1;

	_hitFloor=false;
	_visible=false;
}

void Player::Update(float){
	if(IsKeyDown(SDLK_RIGHT)){
		_visible=false;
		_hitFloor=false;
		_pos.SetX(_pos.GetX()+1);
		_pos.SetY(0);
	}
	if(IsKeyDown(SDLK_LEFT)){
		_visible=false;
		_hitFloor=false;
		_pos.SetX(_pos.GetX()-1);
		_pos.SetY(0);
	}
	CorePosition lpoint1=LandPoint(_point1);
	CorePosition lpoint2=LandPoint(_point2);
	_lpoint1=lpoint1;
	_lpoint2=lpoint2;

	_pos=CorePosition(lpoint1.GetX()-50, lpoint1.GetY()-_size.GetHeight());
	_visible=true;

	double angle=atan2((double)lpoint2.GetY() - lpoint1.GetY(), (double)lpoint2.GetX() - lpoint1.GetX()) * 180 / 3.14159;
	std::cout << angle << std::endl;
	if(angle<=0)angle+=360.0;
	_angle=angle;
}

void Player::Draw(){
	gEngine->DrawRectangle(&_lpoint1, &sz33 ,0xff,0,0,0xff);
	gEngine->DrawRectangle(&_lpoint2, &sz33 ,0xff,0,0,0xff);
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
		if(startPoint.GetY()>1024) break;

		CoreColor pxl=Universe::Instance()->_currentMap->GetPixel(startPoint);
		Uint32 col=pxl.rgba();

		hit=(col==0x000000ff);
	}
	return startPoint;
}