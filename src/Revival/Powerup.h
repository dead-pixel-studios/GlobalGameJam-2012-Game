#pragma once

#include "SpriteBase.h"

namespace PowerupType{
	enum Enum {
		Freeze
	};
}

class Powerup : public SpriteBase
{
public:
	Powerup(CorePosition pos, PowerupType::Enum type);
	OpenGLTexture * GetTexture();
	void Update(float fTime);
	PowerupType::Enum this_powerup_type;
	void Use();
};