#include "SpaceObject.h"

SpaceObject::SpaceObject()
{
	m_width = 0;
	m_height = 0;
	m_pos.x = 0;
	m_pos.y = 0;
	m_vel.vx = 0;
	m_vel.vy = 0;
	m_rotation = 0;
	m_rotationVel = 0;
}

SpaceObject::~SpaceObject()
{
	free();
}

bool SpaceObject::loadTextureFromFile(SDL_Renderer* gRenderer, std::string path, 
	uint16_t alphaR, uint16_t alphaG, uint16_t alphaB, int rows, int cols)
{
	/*free();

	m_texture = new LTexture();

	if (m_texture->loadFromFile(gRenderer, path, alphaR, alphaG, alphaB)) {
		// Define the clips
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
		m_width = clipWidth;
		m_height = clipHeight;

		return true;
	}*/

	return false;
}

void SpaceObject::setTextureAnimation(const LTextureAnimation& textureAnim)
{
	m_textureAnim = textureAnim;
	m_textureAnim.start();
	m_width = m_textureAnim.getClipWidth();;
	m_height = m_textureAnim.getClipHeight();
}

void SpaceObject::free()
{
	/*if (m_texture != NULL) {
	//Free texture if it exists
		m_texture->free();
		delete m_texture;
		m_texture = NULL;
	}*/
	// Doesn't delete the texture

	m_width = 0;
	m_height = 0;
	m_pos.x = 0;
	m_pos.y = 0;
	m_vel.vx = 0;
	m_vel.vy = 0;
}

int SpaceObject::getWidth() const
{
	return m_width;
}

int SpaceObject::getHeight() const
{
	return m_height;
}

void SpaceObject::setWidth(const int &w)
{
	if (w > 0)
		m_width = w;
}

void SpaceObject::setHeight(const int &h)
{
	if (h > 0)
		m_height = h;
}

void SpaceObject::setSize(const int &w, const int &h)
{
	if (w > 0 && h > 0) {
		m_width = w;
		m_height = h;
	}
}

Point2D SpaceObject::getPos() const
{
	return m_pos;
}
void SpaceObject::setPos(const Point2D &pos)
{
	m_pos = pos;
}

void SpaceObject::setPos(const int &x, const int &y)
{
	m_pos.x = x;
	m_pos.y = y;
}

Vector2D SpaceObject::getVel() const
{
	return m_vel;
}
void SpaceObject::setVel(const Vector2D &vel)
{
	m_vel = vel;
}

double SpaceObject::getRotation() const
{
	return m_rotation;
}

void SpaceObject::setRotation(const double &angle)
{
	m_rotation = angle;
}

double SpaceObject::getRotationVel() const
{
	return m_rotationVel;
}

void SpaceObject::setRotationVel(const double &velocity)
{
	m_rotationVel = velocity;
}

int SpaceObject::getFrameNum() const
{
	return m_textureAnim.getFrameNum();
}

void SpaceObject::setFrameNum(const int &f)
{
	m_textureAnim.setFrameNum(f);
}

int SpaceObject::getFrameNumScaled() const
{
	return m_textureAnim.getFrameNumScaled();
}

void SpaceObject::setFrameNumScaled(const int &f)
{
	m_textureAnim.setFrameNumScaled(f);
}

int SpaceObject::getFrameSpeed() const
{
	return m_textureAnim.getFrameSpeed();
}

void SpaceObject::setFrameSpeed(const int &s)
{
	m_textureAnim.setFrameSpeed(s);
}

void SpaceObject::render(SDL_Renderer* gRenderer, int camX, int camY, double camScale, SDL_Rect* clip,
	double angle, SDL_Point* center, SDL_RendererFlip flip )
{
	//if (m_textureAnim == NULL) return;

	SDL_Rect renderQuad = { (m_pos.x * camScale - camX), (m_pos.y * camScale - camY), 
		m_width * camScale, m_height * camScale };

	//Set clip rendering dimensions
	if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	} 

	//Render to screen
	//SDL_Rect* m_currentClip = &m_SpriteClips[ m_frame / m_frameSpeed ]; 

	m_textureAnim.render(gRenderer, renderQuad, m_rotation, center, flip);
}

void SpaceObject::update()
{
	// Update the position 
	m_pos.x += m_vel.vx;
	m_pos.y += m_vel.vy;

	// Update the rotation
	m_rotation += m_rotationVel;

	// Handle animation
	m_textureAnim.update();
}