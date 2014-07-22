#include "BotoSprite.h"

USING_NS_CC;

//default constructor
BotoSprite::BotoSprite()
{
	visibleSize = Director::getInstance()->getVisibleSize();

	//sprite from default pic
	botoSprite = Sprite::create(BOTO_SPRITE_PATH);
	//set postition
	botoSprite->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	//physiscs activation!!
	botoBody = PhysicsBody::createBox(botoSprite->getContentSize());
	botoBody->setGravityEnable(true);
	botoBody->setDynamic(true);
	botoBody->setRotationEnable(false);
	botoBody->setContactTestBitmask(true);
	botoBody->setCollisionBitmask(BOTO_BITMASK);
	botoBody->setMass(0.1f);
	botoSprite->setPhysicsBody(botoBody);
	//~physiscs bitch!!

	moveLeft = false;
	moveRight = false;
	moveJump = false;
}

//draw BOTO on a layer
void BotoSprite::Draw(Layer *layer)
{
	layer->addChild(botoSprite, 0);
}

//jump action
void BotoSprite::Jump(float yPos)
{
	//NOT WORKING PROPERLY
	//NEED SOME IMPROVEMENTS
	//jump implementation
	if (moveJump == true)
	{
		CCLog("Jumping");
		//botoBody->applyImpulse(Vec2(0, 20));
		auto action = MoveTo::create(0.5f, Point(botoSprite->getPosition().x, botoSprite->getPosition().y+100.f));
		botoSprite->runAction(action);
		CCLog("Jumped");
		moveJump = false;
	}
}

//move action
void BotoSprite::Move(float xSpeed)
{
	//move implemetation
	if (moveLeft == true)
	{
		botoSprite->setPositionX(botoSprite->getPositionX()-xSpeed);
	}
	if (moveRight == true)
	{
		botoSprite->setPositionX(botoSprite->getPositionX()+xSpeed);
	}
}

//bonus collected
void BotoSprite::GotBonus(int bonusType)
{
	//Bonus implementation
}

//implementation of movement methods
void BotoSprite::startMoveLeft()
{
	moveLeft = true;
}
void BotoSprite::stopMoveLeft()
{
	moveLeft = false;
}
void BotoSprite::startMoveRight()
{
	moveRight = true;
}
void BotoSprite::stopMoveRight()
{
	moveRight = false;
}
void BotoSprite::startMoveJump()
{
	moveJump = true;
}
void BotoSprite::stopMoveJump()
{
	moveJump = false;
}
