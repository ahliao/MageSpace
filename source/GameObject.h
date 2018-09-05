/*	GameObject class
	Base abstract class for all game objects
	Holds data for the object name, id, pos, vel

	Last Modified: 08/12/2018
	Author: Alex Liao

	This source code copyrighted by Alectryon Technologies (2018)
	and may not be redistributed without written permission.
*/

#ifndef _GAMEOBJECT_H
#define _GAMEOBJECT_H

// Includes
#include <string>

class GameObject
{
public:
	GameObject();
	GameObject(std::string name, int id);
	~GameObject();

	// Accessors
	std::string getName() const;
	void setName(const std::string &name);

protected:
	std::string m_name;
	int m_id;
};

#endif