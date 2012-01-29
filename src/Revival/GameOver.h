#pragma once
#include "../CoreEngine/CoreGraphics.h"
#include "../CoreEngine/CoreController.h"

class GameOver {
public:
	static GameOver* Instance();
	void Update(float fTime);
	void Draw();

	void GameIsOver();
	bool IsGameOver() { return this->gameOver; }
protected:
	GameOver(void) {};
	GameOver(const GameOver&);
	GameOver& operator=(const GameOver&);
private:
	static GameOver* pinstance;
	void Init();
	
	CoreGraphics * gEngine;
	OpenGLTexture * texture;
	CorePosition * pos;
	CoreSize * size;

	float fadeaccumulator;

	CoreController * player1;
	bool gameOver;
	float fade;
};