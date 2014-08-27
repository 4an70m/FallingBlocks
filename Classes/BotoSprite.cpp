#include "BotoSprite.h"

USING_NS_CC;

//default constructor
BotoSprite::BotoSprite()
{
	visibleSize = Director::getInstance()->getVisibleSize();

	//sprite from default pic
	//botoSprite = Sprite::create(BOTO_SPRITE_PATH);
	//set postition
	//botoSprite->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	//physiscs activation!!

	cocostudio::ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(BOTO_MOBING_PNG, BOTO_MOBING_PLIST, BOTO_MOBING_JSON);
	botoSprite = cocostudio::Armature::create("MobingBoto");
	botoSprite->getAnimation()->play("Standing");
	botoSprite->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	botoSprite->setScale(visibleSize.height / 1920);
	createBody(1.0f);
	//~physiscs bitch!!
	moveLeft = false;
	moveRight = false;
	speed = 5.0f;

	state = State::STANDING;
}

//draw BOTO on a layer
void BotoSprite::draw(Layer *layer, int zOrder)
{
	layer->addChild(botoSprite, zOrder);
}
void BotoSprite::createBody(float scale)
{
	botoSprite->setScale(scale * visibleSize.height / 1920);
	auto sprite = Sprite::create(BOTO_SPRITE_PATH);
	botoBody = PhysicsBody::createBox(
		Size(
				sprite->getContentSize().width * scale* visibleSize.height / 1920,
				sprite->getContentSize().height * scale* visibleSize.height / 1920
		)
	);
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
void BotoSprite::remove(Layer *layer)
{
	botoBody->removeFromWorld();
	layer->removeChild(botoSprite);
}
//move action
void BotoSprite::move(float xSpeed)
{
	//move implemetation
	if (moveLeft == true)
	{
		botoSprite->setPositionX(botoSprite->getPositionX()-xSpeed);
		if(state != State::MOVING_LEFT)
		{
			botoSprite->getAnimation()->play("Moving_left");
			state = State::MOVING_LEFT;
		}
	}
	else
	if (moveRight == true)
	{
		botoSprite->setPositionX(botoSprite->getPositionX()+xSpeed);
		if(state != State::MOVING_RIGHT)
		{
			botoSprite->getAnimation()->play("Moving_right");
			state = State::MOVING_RIGHT;
		}
	}
	else
	{
		botoSprite->getAnimation()->play("Standing");
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
cocostudio::Armature *BotoSprite::getSprite()
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

void BotoSprite::switchAnimation(State state)
{
	switch(state)
	{
		case State::STANDING:
		{
			this->state = State::STANDING;
			break;
		}
		case State::MOVING_LEFT:
		{
			this->state = State::MOVING_LEFT;
			break;
		}
		case State::MOVING_RIGHT:
		{
			this->state = State::MOVING_RIGHT;
			break;
		}

	}
}
