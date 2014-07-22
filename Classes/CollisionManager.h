#ifndef __COLLISION_MANAGER_H__
#define __COLLISION_MANAGER_H__

#include "cocos2d.h"

class CollisionManager
{
public:

	//default constructor
	CollisionManager();

	//check collision
	bool CheckCollision(const cocos2d::PhysicsContact& contact, int firstObjectBitmask, int secondObjectBitmask);
};

#endif // __COLLISION_MANAGER_H__
