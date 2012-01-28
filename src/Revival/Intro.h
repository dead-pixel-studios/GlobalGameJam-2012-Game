#pragma once
#include "../CoreEngine/CoreGraphics.h"

class Intro {
public:
	static Intro* Instance();
	void Update(float fTime);
	void Draw();

	bool finishedIntro();
protected:
	Intro(void) {};
	Intro(const Intro&);
	Intro& operator=(const Intro&);
private:
	static Intro* pinstance;
	void Init();

	CoreGraphics * gEngine;
	OpenGLTexture * texture;
	OpenGLTexture * snake;
	CorePosition * pos;
	CoreSize * size;
	CorePosition * snakepos;
	CoreSize * snakesize;

	float openedFor;
	float lastUpdate;
	float rotation;
	bool haveFinishedIntro;
	bool fadeIn;
float fade;
};