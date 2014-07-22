#include "Blocks.h"

USING_NS_CC;

//default constructor
Blocks::Blocks(cocos2d::Point point)
{
	//Blocks::visibleSize = Director::getInstance()->getVisibleSize();

	//actually here i pick a block
	//but for test i'll leave this test_block
	blockSprite = Sprite::create(TEST_BLOCK);
	//physiscs activation!!
	blockBody= PhysicsBody::createBox(blockSprite->getContentSize());
	blockBody->setGravityEnable(true);
	blockBody->setDynamic(true);
	blockBody->setRotationEnable(false);
	blockBody->setContactTestBitmask(true);
	blockBody->setCollisionBitmask(BLOCKS_BITMASK);
	blockBody->setMass(0.2f);
	blockSprite->setPhysicsBody(blockBody);
	blockSprite->setPosition(point);
	//~physics beatch!
}

//draw a box to layer
void Blocks::DrawBlock(cocos2d::Layer *layer)
{
	layer->addChild(this->getSprite());
}

//setting block position
void Blocks::setPosition(cocos2d::Point point)
{
	blockSprite->setPosition(point);
}

//get block's sprite
Sprite *Blocks::getSprite()
{
	return blockSprite;
}

//generates a random number between two numbers
float Blocks::RandomFloatBetween(float smallNumber, float bigNumber)
{
    float diff = bigNumber - smallNumber;
    return (((float) rand() / RAND_MAX) * diff) + smallNumber;
}

Blocks::BlockType Blocks::PickABlock()
{
	//ToDo: pick implementation
	return BlockType::BONUS_BLOCK;
}

cocos2d::Vec2 Blocks::GeneratePoint(float width, float height)
{
	Vec2 point = Vec2::ZERO;
	point.x = RandomFloatBetween(0, width);
	point.y = height;
	return point;
}
