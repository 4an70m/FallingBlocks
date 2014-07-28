#include "Coins.h"

USING_NS_CC;

Coins::Coins()
{
	coinSprite = Sprite::create(COIN);
	coinBody = PhysicsBody::createCircle(coinSprite->getContentSize().width / 2.0f);
	coinBody->setContactTestBitmask(true);
	coinBody->setCollisionBitmask(COIN_BITMASK);
	coinBody->setDynamic(true);
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

void Coins::generateCoins(Layer *layer, int number, Point point)
{
	for(int i = 0; i < number; i++)
	{
		Coins *newCoin = new Coins();
		newCoin->coinSprite->setPosition(point);
		newCoin->coinBody->setVelocity(Point(0, 5));
		newCoin->coinBody->applyImpulse(Point(0, 10));
		layer->addChild(newCoin->coinSprite);
	}
	return;
}
