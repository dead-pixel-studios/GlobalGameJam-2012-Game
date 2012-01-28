#pragma once

#include "SpriteBase.h"

namespace PowerupType{
	enum Enum{
		Freeze
	};
}

class Powerup : public SpriteBase
{
public:
	Powerup(CorePosition pos, PowerupType::Enum type);
	void Update(float fTime);
};