#include "MainWindow.h"

MainWindow::MainWindow()
{
	init();
	loadMedia();
}

MainWindow::~MainWindow()
{
	
}

bool MainWindow::init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		m_window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( m_window == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			m_renderer = SDL_CreateRenderer( m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( m_renderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( m_renderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}

				 //Initialize SDL_ttf
				if( TTF_Init() == -1 )
				{
					printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

bool MainWindow::loadMedia()
{
	bool success;
	// Load the required resources
	m_textureManager = new TextureManager();
	m_textureManager->loadTextures(m_renderer, "resources/TextureMap.txt");

	m_scene = new WorldScene(640, 480, m_textureManager);
	m_scene->loadScene(m_renderer);

	return success;
}

void MainWindow::show()
{
	//Main loop flag
	bool quit = false;

	//Event handler
	SDL_Event e;

	//While application is running
	while( !quit )
	{
		//Handle events on queue
		while( SDL_PollEvent( &e ) != 0 )
		{
			//User requests quit
			if( e.type == SDL_QUIT )
			{
				quit = true;
			}

			m_scene->handleInput(e);
		}

		//Clear screen
		SDL_SetRenderDrawColor( m_renderer, 0x00, 0x00, 0x00, 0xFF );
		SDL_RenderClear( m_renderer );

		m_scene->update();

		m_scene->render(m_renderer);

		//Update current frame
		//m_planet.update();

		//Render current frame
		//m_planet.render( m_renderer, 0, 0);

		//Update screen
		SDL_RenderPresent( m_renderer );
	}
}

void MainWindow::close()
{
	//Free loaded images
	//m_planet.free();

	//Free global font
	

	//Destroy window	
	SDL_DestroyRenderer( m_renderer );
	SDL_DestroyWindow( m_window );
	m_window = NULL;
	m_renderer = NULL;

	//Quit SDL subsystems
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}