#pragma once
#include "../CoreEngine/CoreGraphics.h"
#include "../CoreEngine/CoreController.h"

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
	float accumulator;
	CoreGraphics * gEngine;
	OpenGLTexture * texture;
	OpenGLTexture * snake;
	CorePosition * pos;
	CoreSize * size;
	CorePosition * snakepos;
	CoreSize * snakesize;
	CoreController * player1;

	float openedFor;
	float lastUpdate;
	float rotation;
	bool haveFinishedIntro;
	bool fadeIn;
float fade;
};