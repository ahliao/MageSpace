#ifndef _SPACEOBJECT_H
#define _SPACEOBJECT_H

//Using SDL and standard IO
#include <SDL.h>
#include <SDL_image.h>
#include "GameObject.h"
#include "LTextureAnimation.h"

// Defined classes
struct Point2D 
{
	double x;
	double y;
};

struct Vector2D
{
	double vx;
	double vy;
};

class SpaceObject : public GameObject
{
public:
	SpaceObject();
	~SpaceObject();

	//Deallocates texture
	void free();

	//Loads image at specified path
	virtual bool loadTextureFromFile(SDL_Renderer* gRenderer, std::string path, 
		uint16_t alphaR = 0xFF, uint16_t alphaG = 0xFF, uint16_t alphaB = 0xFF, int rows = 1, int cols = 1);

	virtual void setTextureAnimation(const LTextureAnimation& textureAnim);

	// Accessors
	int getWidth() const;
	int getHeight() const;

	void setWidth(const int &w);
	void setHeight(const int &h);
	void setSize(const int &w, const int &h);

	Point2D getPos() const;
	void setPos(const Point2D &pos);
	void setPos(const int &x, const int &y);

	Vector2D getVel() const;
	void setVel(const Vector2D &vel);

	double getRotation() const;
	void setRotation(const double &angle);

	double getRotationVel() const;
	void setRotationVel(const double &velocity);

	int getFrameNum() const;
	void setFrameNum(const int &f);

	int getFrameNumScaled() const;
	void setFrameNumScaled(const int &f);

	int getFrameSpeed() const;
	void setFrameSpeed(const int &s);

	//Renders texture at given point
	virtual void render( SDL_Renderer* gRenderer, int camX, int camY, double camScale = 1, SDL_Rect* clip = NULL );

	// Updates the position of the object
	virtual void update();

protected:
	//The hardware texture
	LTextureAnimation m_textureAnim;

	//Image dimensions
	int m_width;
	int m_height;
	Point2D m_pos;
	Vector2D m_vel;

	double m_rotation;
	double m_rotationVel;
};

#endif