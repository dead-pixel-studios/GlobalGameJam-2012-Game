#pragma once

class CorePosition
{
public:
	CorePosition();
	CorePosition(int x, int y);
	int GetX() { return x; }
	int GetY() { return y; }
	void SetX(int newX) { this->x = newX; }
	void SetY(int newY) { this->y = newY; }
	~CorePosition();
private:
	int x;
	int y;
};

extern CorePosition centerPoint;