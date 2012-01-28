#include "CoreGraphics.h"

CoreGraphics* CoreGraphics::pinstance = 0;
CoreGraphics* CoreGraphics::Instance () {
	if(pinstance == 0) { pinstance = new CoreGraphics; pinstance->Init(); }
	return pinstance;
}

void CoreGraphics::Init() {
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		printf("Unable to initialize SDL: %s/n", SDL_GetError());
		return;
	}

	this->ScreenSize = new CoreSize(1024,768);

	SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY ,SDL_DEFAULT_REPEAT_INTERVAL);
	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1);

	screen = SDL_SetVideoMode(ScreenSize->GetWidth(), ScreenSize->GetHeight(), 32, SDL_OPENGL );
	SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 8 );
	SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 8 );
	SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 8 );
	SDL_GL_SetAttribute( SDL_GL_ALPHA_SIZE, 8 );

	glEnable( GL_TEXTURE_2D );

	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
	glViewport( 0, 0, 1024, 768 );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	TTF_Init();
	atexit(TTF_Quit);

	std::string strPath = CoreFunctions::GetAppPath();
	strPath += "/data/slkscr.ttf";
	defaultFont = TTF_OpenFont(strPath.c_str(), 8);

	fManager = new FPSmanager();
	SDL_initFramerate(fManager);
	SDL_setFramerate(fManager, 31);
}

OpenGLTexture * CoreGraphics::CreateTexture(string textureLocation)
{
	return new OpenGLTexture(textureLocation);
}

void CoreGraphics::DrawRectangle(CorePosition * position, CoreSize * size, int r, int g, int b, int a)
{
	glEnable2D();

	//glColor4i(r,g,b,a);
	float rFloat, gFloat, bFloat, aFloat;

	rFloat = (float)r / 255.0F;
	gFloat = (float)g / 255.0F;
	bFloat = (float)b / 255.0F;
	aFloat = (float)a / 255.0F;
	glColor4f(rFloat, gFloat, bFloat, aFloat);
	glBegin(GL_QUADS);
		glTexCoord2i( 0, 1 );
		glVertex2i(position->GetX(),position->GetY()+size->GetHeight());

		glTexCoord2i( 1, 1 );
		glVertex2i(position->GetX()+size->GetWidth(),position->GetY()+size->GetHeight());

		glTexCoord2i( 1, 0 );
		glVertex2d(position->GetX()+size->GetWidth(),position->GetY());

		glTexCoord2i( 0, 0 );
		glVertex2d(position->GetX(),position->GetY());
	glEnd();

	glDisable2D();
}

void CoreGraphics::DrawTexture(OpenGLTexture * texture, CorePosition * position, CoreSize * size, float rotation, float red, float green, float blue, float alpha)
{
	glEnable2D();

	glBindTexture( GL_TEXTURE_2D, texture->Texture());

	glColor4f(red,green,blue,alpha);

	if(rotation > -1) {
		GLfloat center_x = position->GetX()+(GLfloat)(size->GetWidth()*0.5);
		GLfloat center_y = position->GetY()+(GLfloat)(size->GetHeight()*0.5);

		glTranslatef( center_x, center_y, 0 );
		glRotatef( rotation, 0, 0, 1 );
		glTranslatef( -center_x, -center_y, 0 );
	}

	glBegin(GL_QUADS);
		glTexCoord2i( 0, 1 );
		glVertex2i(position->GetX(),position->GetY()+size->GetHeight());

		glTexCoord2i( 1, 1 );
		glVertex2i(position->GetX()+size->GetWidth(),position->GetY()+size->GetHeight());

		glTexCoord2i( 1, 0 );
		glVertex2d(position->GetX()+size->GetWidth(),position->GetY());

		glTexCoord2i( 0, 0 );
		glVertex2d(position->GetX(),position->GetY());
	glEnd();

	glDisable2D();
}

void CoreGraphics::DrawString(string str, CorePosition * position, SDL_Color color)
{
	SDL_Surface * textSurface = TTF_RenderText_Solid(defaultFont, str.c_str(), color);
	textSurface = GetPow2Surface(textSurface);

	OpenGLTexture * oglTex = new OpenGLTexture(textSurface);
	oglTex->Load();

	CoreSize * cSize = new CoreSize(textSurface->w,textSurface->h);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	glEnable2D();

	glBindTexture( GL_TEXTURE_2D, oglTex->Texture());

	glColor4f(1.0f,1.0f,1.0f,1.0f);
	glBegin(GL_QUADS);
		glTexCoord2i( 0, 1 );
		glVertex2i(position->GetX(),position->GetY()+cSize->GetHeight());

		glTexCoord2i( 1, 1 );
		glVertex2i(position->GetX()+cSize->GetWidth(),position->GetY()+cSize->GetHeight());

		glTexCoord2i( 1, 0 );
		glVertex2d(position->GetX()+cSize->GetWidth(),position->GetY());

		glTexCoord2i( 0, 0 );
		glVertex2d(position->GetX(),position->GetY());
	glEnd();

	glDisable2D();

	delete cSize;

	delete oglTex;
}

SDL_Surface * CoreGraphics::GetPow2Surface(SDL_Surface * surface)
{
	int Pow2W = CoreFunctions::NextPowerOf2(surface->w);
	int Pow2H = CoreFunctions::NextPowerOf2(surface->h);
	SDL_Surface * tempSurface = SDL_CreateRGBSurface(0, Pow2W, Pow2H, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
	SDL_SetAlpha(surface,0,0);
	SDL_BlitSurface(surface, 0, tempSurface, 0);
	SDL_FreeSurface(surface);
	SDL_Surface * dispFormat = SDL_DisplayFormatAlpha(tempSurface);
	SDL_FreeSurface(tempSurface);
	return dispFormat;
}

void CoreGraphics::glEnable2D()
{
	int vPort[4];

	glGetIntegerv(GL_VIEWPORT, vPort);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	glOrtho(vPort[0], vPort[0]+vPort[2], vPort[1]+vPort[3], vPort[1], -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(0.375, 0.375, 0.);

	glPushAttrib(GL_DEPTH_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
}

void CoreGraphics::glDisable2D()
{
	glPopAttrib();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

void CoreGraphics::StartFrame()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
}

void CoreGraphics::EndFrame()
{
	SDL_GL_SwapBuffers();
}

CoreColor * CoreGraphics::getPixelColor(SDL_Surface * surface, int x, int y) {
	Uint8 r,g,b,a;
	SDL_LockSurface(surface);
	Uint32 pixelPointer = getPixel(surface,x,y);
	SDL_GetRGBA(pixelPointer, surface->format, &r,&g,&b,&a);
	SDL_UnlockSurface(surface);
	CoreColor * newColor = new CoreColor();
	newColor->r = r;
	newColor->g = g;
	newColor->b = b;
	newColor->a = a;
	return newColor;
}

Uint32 CoreGraphics::getPixel(SDL_Surface * surface, int x, int y) {
	int bpp = surface->format->BytesPerPixel;
	/* Here p is the address to the pixel we want to retrieve */
	Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
	switch(bpp) {
	case 1:
		return *p;
	case 2:
		return *(Uint16 *)p;
	case 3:
		if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
			return p[0] << 16 | p[1] << 8 | p[2];
		else
			return p[0] | p[1] << 8 | p[2] << 16;
	case 4:
		return *(Uint32 *)p;
	default:
		return 0;       /* shouldn't happen, but avoids warnings */
	}
}