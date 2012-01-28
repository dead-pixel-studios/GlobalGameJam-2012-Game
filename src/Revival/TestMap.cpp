#include "TestMap.h"

TestMap::TestMap(){
	texture = gEngine->CreateTexture(CoreFunctions::GetAppPath() + "/data/testmap.png");
	texture->Load();

	_size=CoreSize(3072,1536);
	_pos=CorePosition(0,0);

	_visible=true;
}

void TestMap::Update(float){
}

void TestMap::Draw(){
	gEngine->DrawRectangle(&_pos,&_size,0xff,0xff,0xff,0xff);
	DefaultDraw();
}