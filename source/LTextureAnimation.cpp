#include "LTextureAnimation.h"

LTextureAnimation::LTextureAnimation()
{
	m_SpriteClips = NULL;
	m_frame = 0;
	m_frameSpeed = 16;
	m_paused = true;
}

LTextureAnimation::~LTextureAnimation()
{

}

int LTextureAnimation::getClipWidth() const
{
	return m_clipWidth;
}

int LTextureAnimation::getClipHeight() const
{
	return m_clipHeight;
}

int LTextureAnimation::getFrameNum() const
{
	return m_frame / m_frameSpeed;
}

void LTextureAnimation::setFrameNum(const int &f)
{
	if (f >= 0 && f < m_frameMax * m_frameSpeed) {
		m_frame = f * m_frameSpeed;
	}
}

int LTextureAnimation::getFrameNumScaled() const
{
	return m_frame;
}

void LTextureAnimation::setFrameNumScaled(const int &f)
{
	if (f >= 0 && f < m_frameMax * m_frameSpeed) {
		m_frame = f;
	}
}

int LTextureAnimation::getFrameSpeed() const
{
	return m_frameSpeed;
}

void LTextureAnimation::setFrameSpeed(const int &s)
{
	m_frameSpeed = s;
}

void LTextureAnimation::start()
{
	m_paused = false;
}

void LTextureAnimation::stop()
{
	m_paused = true;
}

void LTextureAnimation::setTexture(LTexture *texture, int rows, int cols)
{
	m_texture = texture;

	m_SpriteClips = new SDL_Rect[rows * cols];
	m_frameMax = rows * cols;
	int clipWidth = m_texture->getWidth() / cols;
	int clipHeight = m_texture->getHeight() / rows;
	for (int i = 0; i < rows * cols; ++i) {
		m_SpriteClips[i].x = (i % cols) * clipWidth;
		m_SpriteClips[i].y = (i / cols) * clipHeight;
		m_SpriteClips[i].w = clipWidth;
		m_SpriteClips[i].h = clipHeight;
	}

	//Get image dimensions
	m_clipWidth = clipWidth;
	m_clipHeight = clipHeight;
}

void LTextureAnimation::render(SDL_Renderer* gRenderer, SDL_Rect renderQuad, 
		double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	if (m_texture == NULL) return;

	//Render to screen
	SDL_Rect* m_currentClip = &m_SpriteClips[ m_frame / m_frameSpeed ]; 

	m_texture->render(gRenderer, renderQuad, m_currentClip, angle, center, flip);
}

void LTextureAnimation::update()
{
	// Handle animation
	if (!m_paused) {
		++m_frame; 
		if( m_frame / m_frameSpeed >= m_frameMax ) { m_frame = 0; }
	}
}

LTextureAnimation& LTextureAnimation::operator=(const LTextureAnimation& copy)
{
	m_texture = copy.m_texture;	// Pointer copy

	m_clipWidth = copy.m_clipWidth;
	m_clipHeight = copy.m_clipHeight;

	m_sheetRows = copy.m_sheetRows;
	m_sheetCols = copy.m_sheetCols;

	m_frameMax = copy.m_frameMax;
	m_frameSpeed = copy.m_frameSpeed;
	m_SpriteClips = copy.m_SpriteClips;	// Pointer copy

	//Current animation frame 
	m_frame = copy.m_frame;
}