#ifndef _LTEXTURE_H
#define _LTEXTURE_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>

//Texture wrapper class
class LTexture
{
	public:
		//Initializes variables
		LTexture();

		//Deallocates memory
		~LTexture();

		//Loads image at specified path
		bool loadFromFile( SDL_Renderer* gRenderer, std::string path, uint16_t alphaR, uint16_t alphaG, uint16_t alphaB );
		
		//Creates image from font string
		bool loadFromRenderedText( SDL_Renderer* gRenderer, TTF_Font *gFont, std::string textureText, SDL_Color textColor );

		//Deallocates texture
		void free();

		//Set color modulation
		void setColor( Uint8 red, Uint8 green, Uint8 blue );

		//Set blending
		void setBlendMode( SDL_BlendMode blending );

		//Set alpha modulation
		void setAlpha( Uint8 alpha );
		
		//Renders texture at given point
		void render( SDL_Renderer* gRenderer, SDL_Rect renderQuad, SDL_Rect* clip = NULL, 
			double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

		//Gets image dimensions
		int getWidth() const;
		int getHeight() const;

	private:
		//The actual hardware texture
		SDL_Texture* m_texture;

		//Image dimensions
		int m_width;
		int m_height;
};

#endif