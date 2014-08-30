#include "Coins.h"
#include "Blocks.h"

USING_NS_CC;

Coins::Coins()
{
	coinSprite = Sprite::create(COIN);
}

Coins *Coins::create()
{
	Coins *coin = new Coins();
	coin->coinSprite = Sprite::create(COIN);
	coin->coinBody = PhysicsBody::createBox(coin->coinSprite->getContentSize());
	coin->coinBody->setGroup(-1);
	coin->coinBody->setContactTestBitmask(true);
	coin->coinBody->setCollisionBitmask(COIN_BITMASK);
	coin->coinBody->setMass(0.01f);
	coin->coinSprite->setPhysicsBody(coin->coinBody);
	return coin;
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
		Coins *newCoin = Coins::create();
		newCoin->coinSprite->setPosition(point);
		newCoin->coinBody->setVelocity(Point(0, 5));
		newCoin->coinBody->applyImpulse(Point(Blocks::RandomFloatBetween(-2,2), 5));
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
