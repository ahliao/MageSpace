#ifndef _LTEXTUREANIMATION_H
#define _LTEXTUREANIMATION_H

#include "LTexture.h"

class LTextureAnimation
{
public:
	LTextureAnimation();
	~LTextureAnimation();

	int getClipWidth() const;
	int getClipHeight() const;

	int getFrameNum() const;
	void setFrameNum(const int &f);

	int getFrameNumScaled() const;
	void setFrameNumScaled(const int &f);

	int getFrameSpeed() const;
	void setFrameSpeed(const int &s);

	void start();
	void stop();

	void setTexture(LTexture *texture, int rows = 1, int cols = 1);

	void render(SDL_Renderer* gRenderer, SDL_Rect renderQuad, 
		double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	void update();

	LTextureAnimation& operator=(const LTextureAnimation& copy);

private:
	LTexture *m_texture;

	// Sprite sheet info
	int m_clipWidth;
	int m_clipHeight;

	int m_sheetRows;
	int m_sheetCols;

	// Clips for animations
	int m_frameMax;
	int m_frameSpeed;
	SDL_Rect *m_SpriteClips;

	//Current animation frame 
	int m_frame;

	bool m_paused;
};

#endif