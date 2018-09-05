#include <fstream>
#include <string>
#include <vector>

#include "TextureManager.h"

TextureManager::TextureManager()
{

}

TextureManager::~TextureManager()
{

}

void TextureManager::loadTextures(SDL_Renderer* gRenderer, std::string filename)
{
	// TODO: Need to add error checking

	std::ifstream mapFile;
	mapFile.open(filename);
	if (!mapFile) {
		printf("Error opening texture map file.");
	} else {
		std::string line;
		getline(mapFile, line);
		char delim = '\t';
		while (getline(mapFile, line)) {
			std::vector<std::string> tokens;
			int startPos = 0;
			int pos = line.find(delim);
			while (pos != std::string::npos) {
				tokens.push_back(line.substr(startPos, pos-startPos));
				startPos = ++pos;
				pos = line.find(delim, pos);

				if (pos == std::string::npos) {
					tokens.push_back(line.substr(startPos, line.length()));
				}
			}

			if (tokens.size() != 7) {
				printf("Error in texture map file");
				continue;
			}
			LTexture *texture = new LTexture();
			texture->loadFromFile(gRenderer, tokens[1], stoi(tokens[2]), stoi(tokens[3]), stoi(tokens[4]));

			LTextureAnimation *textureSheet = new LTextureAnimation();
			textureSheet->setTexture(texture, stoi(tokens[5]), stoi(tokens[6]));	

			m_textureMap[stoi(tokens[0])] = textureSheet;
		}
	}
}

LTextureAnimation TextureManager::getTextureAnimation(const int &textureID) const
{
	try {
		return *(m_textureMap.at(textureID));
	} catch (std::out_of_range) {
		printf("Error finding texture animation\n");
		return LTextureAnimation();
	}
}