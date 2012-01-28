#include "SpriteBase.h"
#include <sstream>

class PlayerSprite : public SpriteBase{
private:
	float MaximumVelocityX;
	float MaximumVelocityY;
	float rotation;
	float VelocityX;
	float VelocityY;
	float AccelerationX;
	float AccelerationY;
	float CurrentPosX;
	float CurrentPosY;
	bool RectangleCollisionDetect(SDL_Rect, SDL_Rect);
	SDL_Rect CurrentRectangle;
	stringstream collisionboxloc;
	stringstream currentloc;
	SDL_Rect collisionboxrect;
	bool colliding;
	OpenGLTexture * background;
public:
	PlayerSprite();
	void Draw();
	void Update(float);
	bool Colliding();
};