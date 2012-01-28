#include "PlayerSprite.h"
#include "Universe.h"
#include <sstream>

PlayerSprite::PlayerSprite() {

	this->MaximumVelocityX = 1.0F;
	this->MaximumVelocityY = 1.0F;

	this->rotation = 0.0F;
	texture = gEngine->CreateTexture(CoreFunctions::GetAppPath() + "/data/playerplaceholder.bmp");
	texture->Load();
	
	//Player start position (using floats)
	CurrentPosX = 100.0F;
	CurrentPosY = 100.0F;

	_size=CoreSize(64,64);

	VelocityX = 0.0F;
	VelocityY = 0.5F;

	background = gEngine->CreateTexture(CoreFunctions::GetAppPath() + "/data/flat.png");
	background->Load();
}

bool PlayerSprite::RectangleCollisionDetect(SDL_Rect  A, SDL_Rect  B) {
	// http://lazyfoo.net/SDL_tutorials/lesson17/index.php
	
	//The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = A.x;
    rightA = A.x + A.w;
    topA = A.y;
    bottomA = A.y + A.h;
        
    //Calculate the sides of rect B
    leftB = B.x;
    rightB = B.x + B.w;
    topB = B.y;
    bottomB = B.y + B.h;

//If any of the sides from A are outside of B
    if( bottomA <= topB )
    {
        return false;
    }
    
    if( topA >= bottomB )
    {
        return false;
    }
    
    if( rightA <= leftB )
    {
        return false;
    }
    
    if( leftA >= rightB )
    {
        return false;
    }
    
    //If none of the sides from A are outside B
    return true;
}

void PlayerSprite::Update(float value) {
	this->CurrentPosX = this->CurrentPosX + VelocityX;
	this->CurrentPosY = this->CurrentPosY + VelocityY;
	
	CurrentRectangle.x = (int) this->CurrentPosX;
	CurrentRectangle.y = (int) this->CurrentPosY;
	CurrentRectangle.h = this->_size.GetHeight();
	CurrentRectangle.w = this->_size.GetWidth();

	collisionboxrect.x = 200;
	collisionboxrect.y = 200;
	collisionboxrect.h = 200;
	collisionboxrect.w = 200;
	colliding = RectangleCollisionDetect(CurrentRectangle,collisionboxrect);
	
	collisionboxloc.str("");
	collisionboxloc << "Collision Box: x:" << collisionboxrect.x;
	collisionboxloc << "y: " << collisionboxrect.y << " h: " << collisionboxrect.h << " w: " << collisionboxrect.w;

	currentloc.str("");
	currentloc << "Current Box: x:" << (int) this->CurrentPosX;
	currentloc << "y: " << (int) this->CurrentPosY << " h: " << this->_size.GetHeight() << " w: " << this->_size.GetWidth(); 
	if(colliding == true) {
		currentloc << " Colliding: true";
	} else {
		currentloc << " Colliding: false";
	}
	
	this->_pos.SetX((int) this->CurrentPosX);
	this->_pos.SetY((int) this->CurrentPosY);

	
}

void PlayerSprite::Draw() {
	SDL_Color yellow;
	yellow.g = 255;
	yellow.b = 255;
	yellow.r = 0;
	this->gEngine->DrawRectangle(new CorePosition(collisionboxrect.x, collisionboxrect.y), new CoreSize(collisionboxrect.w, collisionboxrect.h), 255,0,0,255);
	this->gEngine->DrawString(collisionboxloc.str(), new CorePosition(10,10), yellow);
	this->gEngine->DrawString(currentloc.str(), new CorePosition((int) (this->_pos.GetX() + 110), (int) (this->_pos.GetY())), yellow);
	
	
	this->DefaultDraw();
}