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
	this->lavadeath_left = gEngine->CreateTexture(CoreFunctions::GetAppPath() + "/data/Deaths/Lava/Left.png");
	this->lavadeath_left->Load();
	this->lavadeath_right = gEngine->CreateTexture(CoreFunctions::GetAppPath() + "/data/Deaths/Lava/Right.png");
	this->lavadeath_right->Load();

	this->ghost_movingforward_sprites_texture = gEngine->CreateTexture(CoreFunctions::GetAppPath() + "/data/Ghost/Walking/WalkRight.png");
	this->ghost_movingforward_sprites_texture->Load();
	this->ghost_movingbackwards_sprites_texture = gEngine->CreateTexture(CoreFunctions::GetAppPath() + "/data/Ghost/Walking/WalkLeft.png");
	this->ghost_movingbackwards_sprites_texture->Load();
	this->ghost_staticiso_sprite_texture = gEngine->CreateTexture(CoreFunctions::GetAppPath() + "/data/Ghost/Static/StaticIsoRight.png");
	this->ghost_staticiso_sprite_texture->Load();
	this->ghost_jumpleft_texture = gEngine->CreateTexture(CoreFunctions::GetAppPath() + "/data/Ghost/Jump/JumpLeft.png");
	this->ghost_jumpleft_texture->Load();
	this->ghost_jumpright_texture = gEngine->CreateTexture(CoreFunctions::GetAppPath() + "/data/Ghost/Jump/JumpRight.png");
	this->ghost_jumpright_texture->Load();

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
	dead = false;

	_visible=true;

	this->currentframe = 0;
	//this->framesize = CoreSize(_size.GetWidth(), _size.GetHeight());

	frame_accumulator = 0;
	lastupdatepos = _pos;
	_time_elapsed=0;
	death_accumulator = 0;
	death_fade = 1.0F;
	zooming = false;
	zoom_accumulator = 0;
	zoom = 1.0F;

	this->player1 = new CoreController(1);
}

void Player::Update(float delta)
{
	_time_elapsed+=delta;

	float move = 0.0F;
	if((IsKeyDown(SDLK_RIGHT) || IsKeyDown(SDLK_d)) && (IsKeyDown(SDLK_LEFT) || IsKeyDown(SDLK_a))){
		currentDirection=0;
	}else if(IsKeyDown(SDLK_RIGHT) || IsKeyDown(SDLK_d)){
		move = maxpixels_persecond_speed * delta * MOVEMENT_FORWARD;
		currentDirection = MOVEMENT_FORWARD;
		RecordEvent(EventType::Left);
	}else if (IsKeyDown(SDLK_LEFT) || IsKeyDown(SDLK_a)){
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

	if(IsKeyDown(SDLK_RSHIFT)) {
		zooming = true;
	}

	//if(IsKeyDown(SDLK_LALT)) {
	//	Universe * uni = Universe::Instance();
	//	uni->seq->flEffectSends[0]=1.0;
	//}

	if(IsKeyDown(SDLK_LSHIFT)) {
		if(powerups.size()>0) {
			Powerup * pwrup = powerups.at(0);
			pwrup->Use();
			powerups.erase(powerups.begin());
		}
	}

	if(player1->IsConnected()) {
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

	if(dead) {
		death_accumulator = death_accumulator + delta;
		if(death_accumulator > 100) {
			death_accumulator = delta-death_accumulator;
		//	death_fade -= 0.05F;

			if(death_fade <= 0.0F) {
				GameOver::Instance()->GameIsOver();
			}
		}
	}

	if(zooming) {
		zoom_accumulator = zoom_accumulator + delta;
		if(zoom_accumulator > 10) {
			zoom_accumulator = delta - zoom_accumulator;

			zoom += 0.5F;
			gEngine->ScaleWorld(zoom,zoom,zoom);
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
	
	if(_health<=0) {
		RecordEvent(EventType::Die);
		//fade out
		//_visible=false;
		_pos=CorePosition(0,0);
		_health=100;
		_doomed=false;

		if(!dead){
			DeadPlayer *dp=new DeadPlayer(_recorded_events);
			Universe::Instance()->AddSprite(dp);
			dp->Start();
		}

		dead = true;
		std::cout << "DIED!" << std::endl;
	}
}

void Player::Draw()
{
	CorePosition cpoint1=_lpoint1-Universe::Instance()->_worldOffset;
	CorePosition cpoint2=_lpoint1-Universe::Instance()->_worldOffset;

	SDL_Rect * bacon = new SDL_Rect();
	bacon->h = (Uint16) 0.1;
	bacon->w = (Uint16) 0.1;
	bacon->x = (Uint16) 0.1;
	bacon->y = (Uint16) 0.1;

	//SDL_SetClipRect(this->texture->GetSurface(), bacon);
	//int frames;
	if (currentDirection > 0) { 
		// moving right
		if(jumping) {
				frames = 8;
			this->texture = jumpright_texture;
			if(_doomed) {
				this->texture = lavadeath_right;
				frames = 6;
			}
			if(dead) {
				this->texture = ghost_jumpright_texture;
			}
		}
		else {
			frames = 8;
			this->texture = movingforward_sprites_texture;
			if(_doomed) {
				this->texture = lavadeath_right;
				frames = 6;
			}
			if(dead) {
				this->texture = ghost_movingforward_sprites_texture;
			}
		}
	} else if (currentDirection < 0) {
		frames = 8;
		// moving left
		if(jumping) {
			this->texture = jumpleft_texture;
			if(_doomed) {
				this->texture = lavadeath_right;
				frames = 6;
			}
			if(dead) {
				this->texture = ghost_jumpleft_texture;
			}
		}
		else {
			this->texture = movingbackwards_sprites_texture;
			if(_doomed) {
				frames = 6;
				this->texture = lavadeath_left;
			}
			if(dead) {
				this->texture = ghost_movingbackwards_sprites_texture;
			}
		}
	} else {
		// stationary
		if(jumping) {
			this->texture = jumpright_texture;
			frames = 8;
			if(_doomed) {
				frames = 6;
				this->texture = lavadeath_left;
			}
			if(dead) {
				this->texture = ghost_jumpright_texture;
			}
		}
		else {
			this->texture = staticiso_sprite_texture;
			frames =1;
			currentframe = 0;
			if(_doomed) {
				frames = 6;
				this->texture = lavadeath_left;
			}
			if(dead) {
				this->texture = ghost_staticiso_sprite_texture;
			}
		}
	}

	// Draw the sprite
		CorePosition drawPosition=_pos;
	if(_visible){

		drawPosition.SetX(drawPosition.GetX()-Universe::Instance()->_worldOffset.GetX());
		drawPosition.SetY(drawPosition.GetY()-Universe::Instance()->_worldOffset.GetY());

		if(dead) {
				this->gEngine->DrawTextureFrame(texture,&drawPosition,&_origin,&_size,_angle,frames,currentframe,1.0F,1.0F,1.0F,death_fade);
		}
		else {
			this->gEngine->DrawTextureFrame(texture,&drawPosition,&_origin,&_size,_angle,frames,currentframe,1.0F,1.0F,1.0F);
		}
	}

	if(dead) {
		CorePosition * pwrup1pos = new CorePosition(drawPosition.GetX(),drawPosition.GetY()+_size.GetHeight());
		CorePosition * pwrup2pos = new CorePosition(drawPosition.GetX()+40,drawPosition.GetY()+_size.GetHeight());
		CorePosition * pwrup3pos = new CorePosition(drawPosition.GetX()+80,drawPosition.GetY()+_size.GetHeight());
		CoreSize * pwrupsize = new CoreSize(48,48);
		int count = 0;
		for(vector<Powerup*>::iterator pwrUpIter = powerups.begin(); pwrUpIter != powerups.end(); pwrUpIter++) {
			Powerup * pwrup = *pwrUpIter;
			switch(count) {
			case 0:
				this->gEngine->DrawTexture(pwrup->GetTexture(),pwrup1pos,&centerPoint,pwrupsize,-1,1.0,1.0,1.0,0.5);
			break;
			case 1:
				this->gEngine->DrawTexture(pwrup->GetTexture(),pwrup2pos,&centerPoint,pwrupsize,-1,1.0,1.0,1.0,0.5);
				break;
			case 2:
				this->gEngine->DrawTexture(pwrup->GetTexture(),pwrup3pos,&centerPoint,pwrupsize,-1,1.0,1.0,1.0,0.5);
				break;
			}
		}
		free(pwrup1pos);
		free(pwrupsize);
	}


	// Draw the two ray-tracing dots (over the sprite)
	gEngine->DrawRectangle(&cpoint1, &sz33 ,0xff,0,0,0xff);
	gEngine->DrawRectangle(&cpoint2, &sz33 ,0xff,0,0,0xff);

	if(_pos.GetX() != lastupdatepos.GetX() || _pos.GetY() != lastupdatepos.GetY()){
		RecordEvent(EventType::PosChange);
	}

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

bool IsHit(CorePosition startPoint){
	bool hit=false;
	int count = (int) Universe::Instance()->_currentMap->platforms.size();
	for(int i = 0; i < count; i++) {

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
	return hit;
}

CorePosition Player::LandPoint(CorePosition point){

	// ray trace down from point
	// using the map, find the hit layer and return the top pixel in y-axis as a coreposition
	// check any visible platforms first and return them if valid

	bool found=false;

	CorePosition startPoint=point;
	startPoint.SetY(0);
	startPoint.SetX(_pos.GetX()+point.GetX());
	int mapHeight=Universe::Instance()->_currentMap->GetSize().GetHeight();
	for(int cy=0; cy<mapHeight; cy+=10){
		startPoint.SetY(cy);
		bool hit=IsHit(startPoint);
		if(hit){
			while(IsHit(CorePosition(startPoint.GetX(), startPoint.GetY()-1))){
				startPoint.SetY(startPoint.GetY()-1);
			}
			break;
		}
	}
	return startPoint;
}

void Player::RecordEvent(EventType::Enum type){
	PlayerEvent evt;
	evt.time=_time_elapsed;
	evt.type=type;
	evt.pos=_pos;
	evt.tex=texture;
	evt.currentframe=currentframe;
	evt.frames=frames;
	_recorded_events.push_back(evt);
}