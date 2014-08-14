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
	createBody(1.0f);
	//~physiscs bitch!!

	moveLeft = false;
	moveRight = false;
	speed = 5.0f;
}

//draw BOTO on a layer
void BotoSprite::draw(Layer *layer, int zOrder)
{
	layer->addChild(botoSprite, 0);
}
void *BotoSprite::createBody(float scale)
{
	botoBody = PhysicsBody::createBox(
		Size(
				botoSprite->getContentSize().width * scale,
				botoSprite->getContentSize().height * scale
		)
	);
	botoBody->setGravityEnable(true);
	botoBody->setDynamic(true);
	botoBody->setRotationEnable(false);
	botoBody->setContactTestBitmask(true);
	botoBody->setCollisionBitmask(BOTO_BITMASK);
	botoBody->setMass(0.5f);
	botoBody->setGroup(1);
	botoSprite->setPhysicsBody(botoBody);
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
float BotoSprite::getSpeed()
{
	return speed;
}
void BotoSprite::setSpeed(float speed)
{
	this->speed = speed;
}
void BotoSprite::setPosition(Point point)
{
	botoSprite->setPosition(point);
}
