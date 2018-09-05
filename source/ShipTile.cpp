#include "ShipTile.h"

ShipTile::ShipTile()
{
	m_desc = "Standard hull piece";
}

ShipTile::~ShipTile()
{

}

void ShipTile::setTextureAnimation(const LTextureAnimation& textureAnim)
{
	SpaceObject::setTextureAnimation(textureAnim);
	m_textureAnim.stop();	// No animations for ship tiles
}