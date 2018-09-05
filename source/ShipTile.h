// Defines a single tile of a ship
// These are only the ship's hull, not the parts

#ifndef _SHIPTILE_H
#define _SHIPTILE_H

#include "SpaceObject.h"

class ShipTile : public SpaceObject
{
public:
	ShipTile();
	~ShipTile();

	virtual void setTextureAnimation(const LTextureAnimation& textureAnim) override;

private:
	std::string m_desc;
};

#endif