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

inline CorePosition operator+(CorePosition lhs, CorePosition &rhs){
	CorePosition ret;
	ret.SetX(lhs.GetX() + rhs.GetX());
	ret.SetY(lhs.GetY() + rhs.GetY());
	return ret;
}

inline CorePosition operator-(CorePosition lhs, CorePosition &rhs){
	CorePosition ret;
	ret.SetX(lhs.GetX() - rhs.GetX());
	ret.SetY(lhs.GetY() - rhs.GetY());
	return ret;
}

extern CorePosition centerPoint;