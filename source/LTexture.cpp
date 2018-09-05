#include "LTexture.h"

LTexture::LTexture()
{
	//Initialize
	m_texture = NULL;
	m_width = 0;
	m_height = 0;
}

LTexture::~LTexture()
{
	//Deallocate
	free();
}

bool LTexture::loadFromFile( SDL_Renderer* gRenderer, std::string path, uint16_t alphaR, uint16_t alphaG, uint16_t alphaB )
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Color key image
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, alphaR, alphaG, alphaB ) );

		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			m_width = loadedSurface->w;
			m_height = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	//Return success
	m_texture = newTexture;
	return m_texture != NULL;
}

bool LTexture::loadFromRenderedText( SDL_Renderer* gRenderer, TTF_Font *gFont, std::string textureText, SDL_Color textColor )
{
	//Get rid of preexisting texture
	free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
	if( textSurface != NULL )
	{
		//Create texture from surface pixels
        m_texture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
		if( m_texture == NULL )
		{
			printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			m_width = textSurface->w;
			m_height = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface( textSurface );
	}
	else
	{
		printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
	}

	
	//Return success
	return m_texture != NULL;
}

void LTexture::free()
{
	//Free texture if it exists
	if( m_texture != NULL )
	{
		SDL_DestroyTexture( m_texture );
		m_texture = NULL;
		m_width = 0;
		m_height = 0;
	}
}

void LTexture::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
	//Modulate texture rgb
	SDL_SetTextureColorMod( m_texture, red, green, blue );
}

void LTexture::setBlendMode( SDL_BlendMode blending )
{
	//Set blending function
	SDL_SetTextureBlendMode( m_texture, blending );
}
		
void LTexture::setAlpha( Uint8 alpha )
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod( m_texture, alpha );
}

void LTexture::render( SDL_Renderer* gRenderer, SDL_Rect renderQuad, SDL_Rect* clip, 
	double angle, SDL_Point* center, SDL_RendererFlip flip )
{
	//Render to screen
	SDL_RenderCopyEx( gRenderer, m_texture, clip, &renderQuad, angle, center, flip );
}

int LTexture::getWidth() const
{
	return m_width;
}

int LTexture::getHeight() const
{
	return m_height;
}