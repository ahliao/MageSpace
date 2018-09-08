#include <cmath>

#include <fstream>
#include "Ship.h"

Ship::Ship()
{
	m_subspaceSpeed = 4;
	m_rotation = 0;
	m_rotationSpeed.vx = 2;	// Counter-clockwise rotation
    m_rotationSpeed.vy = 2;	// Clockwise rotation
    m_rotationVel = 0;
    m_pos.x = 0;
    m_pos.y = 0;
    m_vel.vx = 0;
    m_vel.vy = 0;
    m_width = 256;
    m_height = 192;

	m_forwardEngineOn = false;
}

Ship::~Ship()
{

}

void Ship::loadShip(const std::string &shipFilename, const TextureManager* const textureManager)
{
    std::ifstream shipFile;
    shipFile.open(shipFilename);
    if (!shipFile) {
        printf("Error opening ship file.");
    } else {
        std::string line;
        char delim = '\t';
        while (getline(shipFile, line)) {
            // First character should always be <
            int xmlIndex = line.find('>');
            std::string xmltag = line.substr(1, xmlIndex-1);
            std::string xmlval = line.substr(xmlIndex+1, line.rfind('<') - xmlIndex - 1);
            if (!xmltag.compare("SHIPNAME")) {
                
            } else if (!xmltag.compare("FRAMEPOINT")) {
                Point2D pnt;
                int commaIndex = xmlval.find(',');
                std::string frameX = xmlval.substr(0, commaIndex);
                std::string frameY = xmlval.substr(commaIndex + 1, std::string::npos);
                pnt.x = stoi(frameX);
                pnt.y = stoi(frameY);
                m_framePoints.push_back(pnt);
            } else if (!xmltag.compare("TILE")) {
                int commaIndex1 = xmlval.find(',');
                int commaIndex2 = xmlval.find(',', commaIndex1+1);
                int commaIndex3 = xmlval.find(',', commaIndex2+1);
                int commaIndex4 = xmlval.find(',', commaIndex3+1);
                std::string frameX = xmlval.substr(0, commaIndex1);
                std::string frameY = xmlval.substr(commaIndex1 + 1, commaIndex2-commaIndex1);
                std::string textureID = xmlval.substr(commaIndex2 + 1, commaIndex3-commaIndex2);
                std::string clipNum = xmlval.substr(commaIndex3 + 1, commaIndex4-commaIndex3);
                std::string rotationAngle = xmlval.substr(commaIndex4 + 1, xmlval.length()-commaIndex4);

                ShipTile tile;
                tile.setTextureAnimation(textureManager->getTextureAnimation(stoi(textureID)));
                tile.setFrameNum(stoi(clipNum));
                tile.setPos(stoi(frameX) * tile.getWidth(), stoi(frameY) * tile.getHeight());
                tile.setRotation(stod(rotationAngle));
                m_tiles.push_back(tile);
            }
        }
    }
}

void Ship::handleInput(SDL_Event& e)
{
	//If a key was pressed
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: 
            	m_forwardEngineOn = true;
            	break;
            case SDLK_DOWN: 
            	break;
            case SDLK_LEFT: m_rotationVel -= m_rotationSpeed.vx; break;
            case SDLK_RIGHT: m_rotationVel += m_rotationSpeed.vy; break;
        }
    }

    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: 
            	m_forwardEngineOn = false;
            	m_vel.vy = 0; 
            	m_vel.vx = 0; 
            	break;
            case SDLK_DOWN: 
            	m_vel.vy = 0; 
            	m_vel.vx = 0; 
            	break;
            case SDLK_LEFT: m_rotationVel += m_rotationSpeed.vx; break;
            case SDLK_RIGHT: m_rotationVel -= m_rotationSpeed.vy; break;
        }
    }
}

//Renders texture at given point
void Ship::render( SDL_Renderer* gRenderer, int camX, int camY, double camScale, SDL_Rect* clip )
{
    SDL_Texture* image_sum = SDL_CreateTexture(gRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, m_width, m_height);
    SDL_SetRenderTarget(gRenderer, image_sum);
    SDL_SetTextureBlendMode(image_sum, SDL_BLENDMODE_BLEND);
	//SpaceObject::render(gRenderer, camX, camY, camScale, clip);
    //test.render(gRenderer, camX, camY, camScale, clip);
    for (ShipTile tile : m_tiles) {
        tile.render(gRenderer, camX, camY, 1, clip);
    }
    SDL_SetRenderTarget(gRenderer, NULL);
    SDL_Rect image_sum_rect;
    image_sum_rect.x=m_pos.x * camScale - camX;
    image_sum_rect.y=m_pos.y * camScale - camY;
    image_sum_rect.w=m_width * camScale;
    image_sum_rect.h=m_height * camScale;
    //SDL_Point center = { image_sum_rect.x + image_sum_rect.w/2, image_sum_rect.y + image_sum_rect.h/2 };

    SDL_RenderCopyEx(gRenderer, image_sum, NULL, &image_sum_rect, m_rotation, NULL, SDL_FLIP_NONE);
    //SDL_RenderPresent(gRenderer);
}

// Updates the position of the object
void Ship::update()
{
	// Update velocity
	if (m_forwardEngineOn) {
    	double rotInRad = m_rotation * M_PI / 180.0;
		m_vel.vy = -m_subspaceSpeed * cos(rotInRad); 
    	m_vel.vx = m_subspaceSpeed * sin(rotInRad); 
	} else {
        m_vel.vy = 0; 
        m_vel.vx = 0; 
    }

	// Update rotation
    m_pos.x += m_vel.vx;
    m_pos.y += m_vel.vy;
    m_rotation += m_rotationVel;

    for (ShipTile &tile : m_tiles) {
        //tile.setRotationVel(m_rotationVel);
        //tile.setVel(m_vel);
        //tile.update();
    }
    /*m_tiles[0].setRotationVel(m_rotationVel);
    m_tiles[0].setVel(m_vel);
    m_tiles[0].update();*/
	//SpaceObject::update();

}
