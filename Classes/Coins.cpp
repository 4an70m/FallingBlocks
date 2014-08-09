#include "Coins.h"
#include "Blocks.h"

USING_NS_CC;

Coins::Coins()
{
	coinSprite = Sprite::create(COIN);

	coinBody = PhysicsBody::createBox(coinSprite->getContentSize());
	coinBody->setGroup(-1);
	coinBody->setContactTestBitmask(true);
	coinBody->setCollisionBitmask(COIN_BITMASK);
	coinBody->setDynamic(true);
	coinBody->setRotationEnable(false);
	coinBody->setGravityEnable(true);
	coinBody->setMass(0.01f);
	coinSprite->setPhysicsBody(coinBody);
}

PhysicsBody *Coins::getBody()
{
	return coinBody;
}
Sprite *Coins::getSprite()
{
	return coinSprite;
}

void Coins::generateCoins(Layer *layer, int number, Point point, int zOrder)
{
	for(int i = 0; i < number; i++)
	{
		Coins *newCoin = new Coins();
		newCoin->coinSprite->setPosition(point);
		newCoin->coinBody->setVelocity(Point(0, 5));
		newCoin->coinBody->applyImpulse(Point(Blocks::RandomIntBetween(-2,2), 5));
		layer->addChild(newCoin->coinSprite, zOrder);
	}
	return;
}

void Coins::remove(const PhysicsContact &contact, Layer *layer)
{
	if(COIN_BITMASK == contact.getShapeA()->getBody()->getCollisionBitmask())
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
