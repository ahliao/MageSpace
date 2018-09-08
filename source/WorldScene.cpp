#include "WorldScene.h"

WorldScene::WorldScene() : WorldScene(640, 480)
{
	
}

WorldScene::WorldScene(int screen_width, int screen_height) : WorldScene(640, 480, NULL)
{

}

WorldScene::WorldScene(int screen_width, int screen_height, TextureManager *textureManager)
{
	m_camera = { 0, 0, screen_width, screen_height };
	m_camSpeed = 2;
	m_camScale = 1;

	m_textureManager = textureManager;
}

WorldScene::~WorldScene()
{
	// Delete all objects
	for (SpaceObject *obj : m_objects) {
		delete obj;
	}
}

void WorldScene::loadScene(SDL_Renderer* gRenderer)
{
	// Create the scene objects
	SpaceObject *m_planet = new SpaceObject;
	m_planet->setTextureAnimation(m_textureManager->getTextureAnimation(1));
	/*if( !m_planet->loadTextureFromFile( gRenderer, "resources/planet_A.png", 0xFF, 0, 0 ) )
	{
		printf( "Failed to load planet texture!\n" );
	}*/

	m_objects.push_back(m_planet);

	m_player = new Ship;
	m_player->loadShip("resources/Ship_A.txt", m_textureManager);
	//m_player->setTextureAnimation(m_textureManager->getTextureAnimation(2));
	//m_player->setSize(64, 64);
	/*if( !m_player->loadTextureFromFile( gRenderer, "resources/ship_A.png", 0xFF, 0xFF, 0xFF, 1, 2 ) )
	{
		printf( "Failed to load ship texture!\n" );
	}*/

	//m_objects.push_back(m_player);

	//sector.loadTextureFromFile(gRenderer, "resources/sectorBG_A.jpg");
	generateBackground(gRenderer);

	TTF_Font *gFont;
	gFont = TTF_OpenFont( "resources/lazy.ttf", 28 );
	if( gFont == NULL )
	{
		printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
	}
	else
	{
		//Render text
		SDL_Color textColor = { 0xFF, 0xFF, 0xFF };
		text = new LTexture();
		if( !text->loadFromRenderedText( gRenderer, gFont, "The quick brown fox jumps over the lazy dog", textColor ) )
		{
			printf( "Failed to render text texture!\n" );
		}
	}
}

void WorldScene::render(SDL_Renderer* gRenderer, SDL_Rect* clip)
{
	update();

	// Draw the background
	//sector.render(gRenderer, 0, 0);
	for (SpaceObject *obj : m_background) {
		obj->render(gRenderer, m_camera.x, m_camera.y, m_camScale);
	}

	for (SpaceObject *obj : m_objects) {
		obj->render(gRenderer, m_camera.x, m_camera.y, m_camScale);
	}

	m_player->render(gRenderer, m_camera.x, m_camera.y, m_camScale);

	SDL_Rect renderQuad = { 10, 10, text->getWidth(), text->getHeight() };
	text->render(gRenderer, renderQuad);
}

void WorldScene::update()
{
	for (SpaceObject *obj : m_background) {
		obj->update();
	}

	for (SpaceObject *obj : m_objects) {
		obj->update();
	}

	m_player->update();

	// Update the camera from it's velocity
	//m_camera.x += m_camVel.vx;
	//m_camera.y += m_camVel.vy;
	//m_camera.x = ((m_player->getPos().x + m_player->getWidth()/2) * m_camScale - m_camera.w / 2);
	//m_camera.y = ((m_player->getPos().y + m_player->getHeight()/2) * m_camScale - m_camera.h / 2);
}

void WorldScene::handleInput(SDL_Event& e)
{
	m_player->handleInput(e);

	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_w: 
            	m_camScale += 0.05;
            	break;
            case SDLK_s: 
            	m_camScale -= 0.05;
            	break;
        }
    }
}

// Draws a generated background
void WorldScene::generateBackground(SDL_Renderer* gRenderer)
{
	// TODO: different generations for different areas

	// Draw randomly 
	//LTexture *star = new LTexture();
	//star->loadFromFile(gRenderer, "resources/BG_Stars.png", 0, 0, 0);

	for (int i = 0; i < 560; ++i) {
		SpaceObject *starObj = new SpaceObject();
		starObj->setTextureAnimation(m_textureManager->getTextureAnimation(3));
		starObj->setFrameSpeed(128);
		starObj->setFrameNumScaled(rand() % (128*2));
		starObj->setSize(8, 8);
		starObj->setPos(rand() % 2560 - 1280, rand() % 2560 - 1280);

		m_background.push_back(starObj);	
	}
}