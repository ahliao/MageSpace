/*	GameObject class
	Base abstract class for all game objects
	Holds data for textures, position, velocity, name

	Last Modified: 08/12/2018
	Author: Alex Liao

	This source code copyrighted by Alectryon Technologies (2018)
	and may not be redistributed without written permission.
*/

// Includes
#include "GameObject.h"

// Base Constructor
GameObject::GameObject()
{
	m_name = "Default Name";
	m_pos.x = 0;
	m_pos.y = 0;
	m_vel.vx = 0;
	m_vel.vy = 0;
}

// Deconstructor
GameObject::~GameObject()
{

}

// Accessors
std::string GameObject::getName() const
{
	return m_name;
}
void GameObject::setName(const std::string &name)
{
	m_name = name;
}

Point2D GameObject::getPos() const
{
	return m_pos;
}
void GameObject::setPos(const Point2D &pos)
{
	m_pos = pos;
}

Vector2D GameObject::getVel() const
{
	return m_vel;
}
void GameObject::setVel(const Vector2D &vel)
{
	m_vel = vel;
}