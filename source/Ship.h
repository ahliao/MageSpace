#ifndef _SHIP_H
#define _SHIP_H

#include <vector>
#include "ShipTile.h"
#include "TextureManager.h"

class Ship
{
public:
	Ship();
	~Ship();

	void loadShip(const std::string &shipFilename, const TextureManager* const textureManager);

	void handleInput(SDL_Event& e);

	//Renders texture at given point
	void render( SDL_Renderer* gRenderer, int camX, int camY, double camScale = 1, SDL_Rect* clip = NULL );

	// Updates the position of the object
	void update();

private:
	// Ship tile frame points
	std::vector<Point2D> m_framePoints;

	// Ship tile info
	std::vector<ShipTile> m_tiles;

	int m_subspaceSpeed;
	Vector2D m_rotationSpeed;

	// Engine Activation
	bool m_forwardEngineOn;
};

#endif