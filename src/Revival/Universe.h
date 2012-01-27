#pragma once

#include "../CoreEngine/CoreGraphics.h"

class CoreGraphics;

class Universe {
public:
	static Universe* Instance();
	void Update(float fTime);
	void Draw();

	void rotateP();
	void rotateM();
protected:
	Universe(void) {};
	Universe(const Universe&);
	Universe& operator=(const Universe&);
private:
	static Universe* pinstance;
	void Init();
	float rotation;

	CoreGraphics * gEngine;
	OpenGLTexture * texture1;
};