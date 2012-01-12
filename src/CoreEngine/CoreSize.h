#pragma once

class CoreSize
{
public:
	CoreSize();
	CoreSize(int width, int height);
	bool PowerOf2();
	int GetWidth() { return width; }
	int GetHeight() { return height; }
	void SetWidth(int newWidth) { this->width = newWidth; }
	void SetHeight(int newHeight) { this->height = newHeight; }
	~CoreSize();
private:
	int width;
	int height;
};
