#include "Universe.h"
#include "Player.h"
#include "Intro.h"
#include "TestMap.h"
#include "Map.h"

#include <iostream>
#include <cmath>

CoreSize sz33(3,3);

Player::Player()
{

	this->maxpixels_persecond_speed = 0.8F;

	this->movingforward_sprites_texture = gEngine->CreateTexture(CoreFunctions::GetAppPath() + "/data/Walking/WalkRight.png");
	this->movingforward_sprites_texture->Load();
	this->movingbackwards_sprites_texture = gEngine->CreateTexture(CoreFunctions::GetAppPath() + "/data/Walking/WalkLeft.png");
	this->movingbackwards_sprites_texture->Load();
	this->staticiso_sprite_texture = gEngine->CreateTexture(CoreFunctions::GetAppPath() + "/data/Static/StaticIsoRight.png");
	this->staticiso_sprite_texture->Load();

	this->jumpleft_texture = gEngine->CreateTexture(CoreFunctions::GetAppPath() + "/data/Jump/JumpLeft.png");
	this->jumpleft_texture->Load();
	this->jumpright_texture = gEngine->CreateTexture(CoreFunctions::GetAppPath() + "/data/Jump/JumpRight.png");
	this->jumpright_texture->Load();

	this->texture = staticiso_sprite_texture;
	
	this->_size=CoreSize(145,500);
	this->_pos=CorePosition(0,0);

	this->_point1=CorePosition(50, 500);
	this->_point2=CorePosition(100,500);
	this->_origin=_point1;

	this->jump_time_length_secs = 7.0F; // how long it takes to jump
	this->jump_current_velocity_pixels_sec = 1.0F; // current jump velocity (pixels per second) (for acceleration)
	this->jump_elapsed = 0.0F; // current jump
	this->jumping = false;

	this->Gravity = 2.5;
	this->Velocity= 0;
	_health=100;
	_doomed=false;

	_visible=true;

	this->currentframe = 0;
	//this->framesize = CoreSize(_size.GetWidth(), _size.GetHeight());

	frame_accumulator = 0;
	lastupdatepos = _pos;
	_time_elapsed=0;

	this->player1 = new CoreController(1);
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

	if(player1->IsConnected()) {
		/*if(player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) {
			move = maxpixels_persecond_speed * delta * MOVEMENT_FORWARD;
			currentDirection = MOVEMENT_FORWARD;
			RecordEvent(EventType::Left);
		}
		else if(player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) {
			move = maxpixels_persecond_speed * delta * MOVEMENT_BACKWARD;
			currentDirection =MOVEMENT_BACKWARD;
			RecordEvent(EventType::Right);
		}
		else if(player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) {
			RecordEvent(EventType::Jump);
			if (jumping != true) {
				Velocity = -30.0F;
				jumping = true;
			}
		}
		*/

		thumblx = player1->GetState().Gamepad.sThumbLX;
		thumbly = player1->GetState().Gamepad.sThumbLY;

		if(thumblx>4000) {
			move = maxpixels_persecond_speed * delta * MOVEMENT_FORWARD;
			currentDirection = MOVEMENT_FORWARD;
			RecordEvent(EventType::Left);
		}
		else if(thumblx<-10000) {
			move = maxpixels_persecond_speed * delta * MOVEMENT_BACKWARD;
			currentDirection =MOVEMENT_BACKWARD;
			RecordEvent(EventType::Right);
		}

		if(player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_A) {
			RecordEvent(EventType::Jump);
			if (jumping != true) {
				Velocity = -30.0F;
				jumping = true;
			}
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
	if(_doomed){
		RecordEvent(EventType::Hurt);
		_health-=10;
	}
	
	if(_health<=0){
		RecordEvent(EventType::Die);
		//fade out
		//_visible=false;
		_pos=CorePosition(0,0);
		_health=100;
		_doomed=false;
		std::cout << "DIED!" << std::endl;

		DeadPlayer *dp=new DeadPlayer(_recorded_events);
		Universe::Instance()->AddSprite(dp);
		dp->Start();
	}
	if(_pos.GetX() != lastupdatepos.GetX() || _pos.GetY() != lastupdatepos.GetY()){
		RecordEvent(EventType::PosChange);
	}
}

void Player::Draw(){



	CorePosition cpoint1=_lpoint1-Universe::Instance()->_worldOffset;
	CorePosition cpoint2=_lpoint1-Universe::Instance()->_worldOffset;

	SDL_Rect * bacon = new SDL_Rect();
	bacon->h = (Uint16) 0.1;
	bacon->w = (Uint16) 0.1;
	bacon->x = (Uint16) 0.1;
	bacon->y = (Uint16) 0.1;

	//SDL_SetClipRect(this->texture->GetSurface(), bacon);
	int frames;
	if (currentDirection > 0) { 
		// moving right
		if(jumping) {
			this->texture = jumpright_texture;
		}
		else {
			this->texture = movingforward_sprites_texture;
		}
		frames = 8;
	} else if (currentDirection < 0) {
		// moving left
		if(jumping) {
			this->texture = jumpleft_texture;
		}
		else {
			this->texture = movingbackwards_sprites_texture;
		}
		frames = 8;
	} else {
		// stationary
		if(jumping) {
			this->texture = jumpright_texture;
			frames = 8;
		}
		else {
			this->texture = staticiso_sprite_texture;
			frames =1;
			currentframe = 0;
		}
	}

	// Draw the sprite
	if(_visible){
		CorePosition drawPosition=_pos;
		drawPosition.SetX(drawPosition.GetX()-Universe::Instance()->_worldOffset.GetX());
		drawPosition.SetY(drawPosition.GetY()-Universe::Instance()->_worldOffset.GetY());
		this->gEngine->DrawTextureFrame(texture,&drawPosition,&_origin,&_size,_angle,frames,currentframe);
	}

	// Draw the two ray-tracing dots (over the sprite)
	gEngine->DrawRectangle(&cpoint1, &sz33 ,0xff,0,0,0xff);
	gEngine->DrawRectangle(&cpoint2, &sz33 ,0xff,0,0,0xff);

	lastupdatepos.SetX(_pos.GetX());
	lastupdatepos.SetY(_pos.GetY());

	CorePosition * textPos = new CorePosition(10,50);
	SDL_Color color;
	color.r = 255;
	color.g = 0;
	color.b = 0;
	gEngine->DrawString(CoreFunctions::addIntToString("X: ",thumblx),textPos,color);
	textPos->SetY(60);
	gEngine->DrawString(CoreFunctions::addIntToString("Y: ",thumbly),textPos,color);
	free(textPos);
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

	// ray trace down from point
	// using the map, find the hit layer and return the top pixel in y-axis as a coreposition
	// check any visible platforms first and return them if valid

	bool hit=false;

	CorePosition startPoint=point;
	startPoint.SetY(0);
	startPoint.SetX(_pos.GetX()+point.GetX());
	while(!hit){
		startPoint.SetY(startPoint.GetY()+1);
		if(startPoint.GetY()>6000) break; // don't go on forever, give up after 6000 down

		int count = (int) Universe::Instance()->_currentMap->platforms.size();
		for(int i = 0; i < count; i++) {

			//if (startPoint.GetY() > 300 && startPoint.GetX() < 200) {
			//	hit = true;
			//}

			Platform * element = Universe::Instance()->_currentMap->platforms.at(i);
			if(element->collision_enabled) {
				CoreColor temp = element->GetPixel(startPoint);
				Uint32 tempcol = temp.rgba();
				hit=(tempcol==0x000000ff);
			}
		}

		CoreColor pxl=Universe::Instance()->_currentMap->GetPixel(startPoint);
		Uint32 col=pxl.rgba();
		if (!hit) {
			hit=(col==0x000000ff);
		}
	}
	return startPoint;
}

void Player::RecordEvent(EventType::Enum type){
	PlayerEvent evt;
	evt.time=_time_elapsed;
	evt.type=type;
	evt.pos=_pos;
	_recorded_events.push_back(evt);
}