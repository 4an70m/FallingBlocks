#ifndef __BOTO_SPRITE_H__
#define __BOTO_SPRITE_H__

#include "cocos2d.h"
#include "Defenitions.h"

class BotoSprite
{
public:

	//default constructor
	BotoSprite();

	//draw the sprite
	void draw(cocos2d::Layer *layer, int zOrder);

	//bonus or antibonus action
	void gotBonus(int bonusType);

	//move sprite
	void move(float xSpeed);

	//methods for controlling movements
	void startMoveLeft();
	void stopMoveLeft();
	void startMoveRight();
	void stopMoveRight();


	cocos2d::Point getPosition();
	cocos2d::Sprite *getSprite();
	cocos2d::PhysicsBody *getBody();

	static void remove(const cocos2d::PhysicsContact &contact, cocos2d::Layer *layer);

private:
	//sprtie
	cocos2d::Sprite *botoSprite;
	//sprite's physic body
	cocos2d::PhysicsBody *botoBody;
	cocos2d::Size visibleSize;

	float jumpHeight;
	bool moveLeft;
	bool moveRight;
};

#endif // __BOTO_SPRITE_H__
