#include "CollisionManager.h"

//default constructor
CollisionManager::CollisionManager()
{
}

bool CollisionManager::CheckCollision(const cocos2d::PhysicsContact& contact, int firstObjectBitmask, int secondObjectBitmask)
{
	//get first and second bodies
	cocos2d::PhysicsBody *firstBody = contact.getShapeA()->getBody();
	cocos2d::PhysicsBody *secondBody = contact.getShapeB()->getBody();

	//check if anyone has collided one another
	if(firstBody->getCollisionBitmask() == firstObjectBitmask && secondBody->getCollisionBitmask() == secondObjectBitmask ||
	   firstBody->getCollisionBitmask() == secondObjectBitmask && secondBody->getCollisionBitmask() == firstObjectBitmask )
	{
		cocos2d::CCLog("Collision");
		return true;
	}
	else
	{
		//if not - return false
		return false;
	}
}

