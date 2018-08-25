//Using SDL and standard IO
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>

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
};