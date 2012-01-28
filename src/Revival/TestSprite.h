#include "SpriteBase.h"

class TestSprite : public SpriteBase{
private:
	CoreGraphics * gEngine;
	OpenGLTexture * texture1;
	void rotateP();
	void rotateM();

	float rotation;
public:
	TestSprite();
	void Draw();
	void Update();
};