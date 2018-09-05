#ifndef _MAINWINDOW_H
#define _MAINWINDOW_H

//Using SDL and standard IO
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>

#include "TextureManager.h"
#include "SpaceObject.h"
#include "WorldScene.h"

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

class MainWindow
{
public:
	MainWindow();
	~MainWindow();

	bool init();
	bool loadMedia();
	void show();
	void close();

private:
	//The window we'll be rendering to
	SDL_Window* m_window;

	//The window renderer
	SDL_Renderer* m_renderer;	

	// Test
	WorldScene* m_scene;

	// Texture Manager
	TextureManager* m_textureManager;
};

#endif