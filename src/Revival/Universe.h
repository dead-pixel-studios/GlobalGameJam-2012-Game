#pragma once

#include "../CoreEngine/CoreGraphics.h"

class CoreGraphics;

class Universe {
public:
	static Universe* Instance();
	void Update(float fTime);
	void Draw();
protected:
	Universe(void) {};
	Universe(const Universe&);
	Universe& operator=(const Universe&);
private:
	static Universe* pinstance;
	void Init();

	CoreGraphics * gEngine;
	OpenGLTexture * texture1;
};