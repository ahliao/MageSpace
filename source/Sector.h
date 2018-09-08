#ifndef _SECTOR_H
#define _SECTOR_H

#include <SDL.h>
#include <SDL_image.h>

// A sector is an area of space that can hold features like planets
// The world scene will manage what sector is loaded to minimize memory use
class Sector
{
public:
	Sector();
	~Sector();

	//Loads image at specified path
	void generateSector();

	//Renders texture at given point
	void render( SDL_Renderer* gRenderer, int camX, int camY, SDL_Rect* clip = NULL );

	// Updates the position of the object
	void update();

private:
	
};

#endif