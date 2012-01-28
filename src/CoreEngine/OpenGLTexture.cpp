#include "OpenGLTexture.h"

OpenGLTexture::OpenGLTexture(string textureLocation)
{
	this->textureLocation = textureLocation;
	this->surface = NULL;
}

OpenGLTexture::OpenGLTexture(SDL_Surface * surface)
{
	this->textureLocation = "";
	this->surface = surface;
}

bool OpenGLTexture::Load()
{
	if(surface==NULL)
	{
		surface = IMG_Load(textureLocation.c_str());
		if(surface==NULL) { return false; }
	}

	texture_format = CoreFunctions::PixelFormatToTextureFormat(surface->format);

	glGenTextures( 1, &texture );
	glBindTexture( GL_TEXTURE_2D, texture );

	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );

	glTexImage2D( GL_TEXTURE_2D, 0, surface->format->BytesPerPixel, surface->w, surface->h, 0, texture_format, GL_UNSIGNED_BYTE, surface->pixels );

	return true;
}

OpenGLTexture::~OpenGLTexture()
{
	if(surface!=NULL)
	{
		SDL_FreeSurface(surface);
	}
	glDeleteTextures(1, &texture);
}

int OpenGLTexture::GetPixel(int x, int y){
	return 0;
}