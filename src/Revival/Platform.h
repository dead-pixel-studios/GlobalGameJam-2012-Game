#pragma once

#include "SpriteBase.h"

class Platform : public SpriteBase
{
private:

public:
	Platform(CorePosition pos);
	void Update(float fTime);
	bool PlayerWithinBounds();
	OpenGLTexture * collision_texture;
	bool collision_enabled;
	bool collision_texture_visible;
	CoreColor GetPixel(CorePosition pos);
	void SetEnabled(bool Enabled);
	void SetVisible(bool value);
};