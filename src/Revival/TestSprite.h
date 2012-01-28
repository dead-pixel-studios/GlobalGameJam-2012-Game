#include "SpriteBase.h"

class TestSprite : public SpriteBase{
private:
	void rotateP();
	void rotateM();

	float rotation;
public:
	TestSprite();
	void Draw();
	void Update();
};