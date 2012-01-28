#include "TestMap.h"

TestMap::TestMap(){
	texture = gEngine->CreateTexture(CoreFunctions::GetAppPath() + "/data/testmap.png");
	texture->Load();

	_size=CoreSize(1024,768);
	_pos=CorePosition(0,0);

	_visible=true;
}

void TestMap::Update(float){
}