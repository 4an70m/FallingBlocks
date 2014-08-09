#include "Ground.h"

USING_NS_CC;

//default constructor
Ground::Ground()
{
	visibleSize = Director::getInstance()->getVisibleSize();

	ground = Sprite::create(GAME_SCENE_GROUND);
	ground->setPosition(Point(visibleSize.width / 2, visibleSize.height / 15));
	groundBody = PhysicsBody::createBox(ground->getContentSize());
	groundBody->setDynamic(false);
	groundBody->setGravityEnable(false);
	groundBody->setContactTestBitmask(true);
	groundBody->setCollisionBitmask(GROUND_BITMASK);
	ground->setPhysicsBody(groundBody);

}

//draw BOTO on a layer
void Ground::draw(Layer *layer, int zOrder)
{
	layer->addChild(ground, zOrder);
}

Point Ground::getPosition()
{
	return groundBody->getPosition();
}
Sprite *Ground::getSprite()
{
	return ground;
}
PhysicsBody *Ground::getBody()
{
	return groundBody;
}
