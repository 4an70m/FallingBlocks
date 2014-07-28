#ifndef __COINS_H__
#define __COINS_H__

#include "cocos2d.h"
#include "Defenitions.h"

class Coins
{
public:

	//default constructor
	Coins();

	cocos2d::Sprite *getSprite();
	cocos2d::PhysicsBody *getBody();

	static void generateCoins(cocos2d::Layer *layer, int number, cocos2d::Point point);

private:
	cocos2d::Sprite *coinSprite;
	cocos2d::PhysicsBody *coinBody;
};

#endif // __COINS_H__
