// Loads and manages all textures stored in memory

#ifndef _TEXTUREMANAGER_H
#define _TEXTUREMANAGER_H

#include <SDL.h>
#include <SDL_image.h>
#include <map>
#include "LTextureAnimation.h"

class TextureManager
{
public:
	TextureManager();
	~TextureManager();

	void loadTextures(SDL_Renderer* gRenderer, std::string filename);

	LTextureAnimation getTextureAnimation(const int &textureID) const;

private:
	std::map<int, LTextureAnimation*> m_textureMap;
};

#endif