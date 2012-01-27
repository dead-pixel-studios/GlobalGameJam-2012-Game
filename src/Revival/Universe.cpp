#include "Universe.h"

Universe* Universe::pinstance = 0;
Universe* Universe::Instance () {
	if(pinstance == 0) { pinstance = new Universe; pinstance->Init(); }
	return pinstance;
}

void Universe::Init() {
	this->gEngine = CoreGraphics::Instance();
	this->rotation = 0.0F;

	texture1 = gEngine->CreateTexture(CoreFunctions::GetAppPath() + "/data/bloogy.bmp");
	texture1->Load();
}

void Universe::Update(float fTime)
{

}

void Universe::Draw()
{
	CorePosition * cPos = new CorePosition(100,100);
	CoreSize * cSize = new CoreSize(64,64);
	this->gEngine->DrawTexture(texture1,cPos,cSize, this->rotation);
	delete cPos;
	delete cSize;
}

void Universe::rotateP()
{
	this->rotation += 1.0F;
}
void Universe::rotateM()
{
	this->rotation -= 1.0F;
}