#pragma once

#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <SDL/SDL_image.h>
#include <string>

using namespace std;

class OpenGLTexture
{
public:
	OpenGLTexture(string textureLocation);
	OpenGLTexture(SDL_Surface * surface);
	bool Load();
	GLuint Texture() { return texture; }
	~OpenGLTexture();
private:
	string textureLocation;
	GLenum texture_format;
	GLuint texture;
	SDL_Surface * surface;
};

#include "CoreFunctions.h"