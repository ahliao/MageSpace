// class holding objects in the loaded system
#ifndef _WORLDSCENE_H
#define _WORLDSCENE_H

#include <vector>
#include <SDL.h>
#include <SDL_image.h>

#include "TextureManager.h"
#include "SpaceObject.h"
#include "Ship.h"

class WorldScene
{
public:
	WorldScene();
	WorldScene(int screen_width, int screen_height);
	WorldScene(int screen_width, int screen_height, TextureManager *textureManager);
	~WorldScene();

	void loadScene(SDL_Renderer* gRenderer);
	void render(SDL_Renderer* gRenderer, SDL_Rect* clip = NULL);
	void update();
	void handleInput(SDL_Event& e);

	// Helper functions
	void generateBackground(SDL_Renderer* gRender);

private:
	std::vector<SpaceObject*> m_background;
	std::vector<SpaceObject*> m_objects;
	SDL_Rect m_camera;
	Vector2D m_camVel;

	int m_camSpeed;
	double m_camScale;

	Ship *m_player;

	// Sector

	LTexture *text;
	TextureManager *m_textureManager;
};

#endif