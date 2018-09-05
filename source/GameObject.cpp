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