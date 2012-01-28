#include "Player.h"
#include "Universe.h"

#include <iostream>

Player::Player(){
	texture = gEngine->CreateTexture(CoreFunctions::GetAppPath() + "/data/character.png");
	texture->Load();
	_size=CoreSize(145,250);
	_pos=CorePosition(0,0);

	_collisionPoint=CorePosition(73, 250);

	_hitFloor=false;
	_visible=true;
}

void Player::Update(float){
	if(!_hitFloor){
		_pos.SetY(_pos.GetY()+1);
		_hitFloor=WorldCollisionCheck();
	}
}

bool Player::WorldCollisionCheck(){
	static Uint32 lastCol=0;

	CorePosition posToCheck=_collisionPoint;
	posToCheck.SetX(posToCheck.GetX()+_pos.GetX());
	posToCheck.SetY(posToCheck.GetY()+_pos.GetY());

	CoreColor pxl=Universe::Instance()->_currentMap->GetPixel(posToCheck);
	Uint32 col=pxl.rgba();

	if(col!=lastCol){
		std::cout << 0xff000000 << ':' << col << std::endl;
		lastCol=col;
	}
	return (col==0xff000000);
}