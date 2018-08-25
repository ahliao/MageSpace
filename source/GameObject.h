/*	GameObject class
	Base abstract class for all game objects
	Holds data for the object name, id, pos, vel

	Last Modified: 08/12/2018
	Author: Alex Liao

	This source code copyrighted by Alectryon Technologies (2018)
	and may not be redistributed without written permission.
*/

// Includes
#include <string>

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

class GameObject
{
public:
	GameObject();
	GameObject(std::string name, Point2D pos, int id);
	~GameObject();

	// Accessors
	std::string getName() const;
	void setName(const std::string &name);

	Point2D getPos() const;
	void setPos(const Point2D &pos);

	Vector2D getVel() const;
	void setVel(const Vector2D &vel);

protected:
	std::string m_name;
	Point2D m_pos;
	Vector2D m_vel;
	int m_id;
};