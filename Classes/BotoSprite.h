#ifndef __BOTO_SPRITE_H__
#define __BOTO_SPRITE_H__

#include "cocos2d.h"
#include "Defenitions.h"
#include "cocostudio/CCArmature.h"
#include "cocostudio/CCArmatureDataManager.h"
class BotoSprite
{
public:

	enum class State
	{
		STANDING,
		MOVING_LEFT,
		MOVING_RIGHT
	};

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
	float getSpeed();
	void setSpeed(float speed);
	void setPosition(cocos2d::Point point);
	void createBody(float scale);

	void switchAnimation(State state);


	cocos2d::Point getPosition();
	cocostudio::Armature *getSprite();
	cocos2d::PhysicsBody *getBody();

	static void remove(const cocos2d::PhysicsContact &contact, cocos2d::Layer *layer);
	void remove(cocos2d::Layer *layer);

private:
	//sprtie
	//cocos2d::Sprite *botoSprite;
	//sprite's physic body
	cocos2d::PhysicsBody *botoBody;
	//cocos2d::PhysicsBody *botoABody;
	cocos2d::Size visibleSize;
	cocostudio::Armature *botoSprite;

	float jumpHeight;
	bool moveLeft;
	bool moveRight;
	float speed;

	State state;
};

#endif // __BOTO_SPRITE_H__
