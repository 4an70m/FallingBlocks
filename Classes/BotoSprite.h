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
	void Draw(cocos2d::Layer *layer);

	//bonus or antibonus action
	void GotBonus(int bonusType);

	//move sprite
	void Move(float xSpeed);
	//jump sprite
	void Jump(float yPos);

	cocos2d::Sprite *getSprite();

	//methods for controlling movements
	void startMoveLeft();
	void stopMoveLeft();
	void startMoveRight();
	void stopMoveRight();
	void startMoveJump();
	void stopMoveJump();
	void notJumpable();
	void yesJumpable();
	cocos2d::Size visibleSize;

private:
	//sprtie
	cocos2d::Sprite *botoSprite;
	//sprite's physic body
	cocos2d::PhysicsBody *botoBody;


	float jumpHeight;
	bool moveLeft;
	bool moveRight;
	bool moveJump;
	bool jumpable;
};

#endif // __BOTO_SPRITE_H__
