#ifndef __GROUND_H__
#define __GROUND_H__

#include "cocos2d.h"
#include "Defenitions.h"

class Ground
{
public:

	//default constructor
	Ground();

	//draw the sprite
	void draw(cocos2d::Layer *layer, int zOrder);

	cocos2d::Point getPosition();
	cocos2d::Sprite *getSprite();
	cocos2d::PhysicsBody *getBody();

private:
	//sprtie
    cocos2d::Sprite *ground;
	//sprite's physic body
	cocos2d::PhysicsBody *groundBody;
	cocos2d::Size visibleSize;
};

#endif // __GROUND_H__
