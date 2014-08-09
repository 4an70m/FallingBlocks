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
	botoBody->setGroup(1);
	botoSprite->setPhysicsBody(botoBody);
	//~physiscs bitch!!

	moveLeft = false;
	moveRight = false;
//	moveJump = false;
}

//draw BOTO on a layer
void BotoSprite::draw(Layer *layer, int zOrder)
{
	layer->addChild(botoSprite, 0);
}
void BotoSprite::remove(const PhysicsContact &contact, Layer *layer)
{
	if(BOTO_BITMASK == contact.getShapeA()->getBody()->getCollisionBitmask())
	{
		contact.getShapeA()->getBody()->removeFromWorld();
		layer->removeChild(contact.getShapeA()->getBody()->getNode());
	}
	else
	{
		contact.getShapeB()->getBody()->removeFromWorld();
		layer->removeChild(contact.getShapeB()->getBody()->getNode());
	}
}
//move action
void BotoSprite::move(float xSpeed)
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
void BotoSprite::gotBonus(int bonusType)
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
Point BotoSprite::getPosition()
{
	return botoSprite->getPosition();
}
Sprite *BotoSprite::getSprite()
{
	return botoSprite;
}
PhysicsBody *BotoSprite::getBody()
{
	return botoBody;
}
