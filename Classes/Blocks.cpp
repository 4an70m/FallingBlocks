#include "Blocks.h"

USING_NS_CC;

//default constructor
Blocks::Blocks(cocos2d::Point point)
{
	//Blocks::visibleSize = Director::getInstance()->getVisibleSize();

	//actually here i pick a block
	//but for test i'll leave this test_block
	MyBodyParser::getInstance()->parseJsonFile(BRICK_BODIES);
	this->blockType = pickABlock();
	switch(blockType)
	{
		case BlockType::I_BLOCK:
		{
			blockSprite = Sprite::create(BRICK_I);
			blockBody = MyBodyParser::getInstance()->bodyFormJson(blockSprite, "BRICK-I");
			break;
		}
		case BlockType::J_BLOCK:
		{
			blockSprite = Sprite::create(BRICK_J);
			blockBody = MyBodyParser::getInstance()->bodyFormJson(blockSprite, "BRICK-J");
			break;
		}
		case BlockType::L_BLOCK:
		{
			blockSprite = Sprite::create(BRICK_L);
			blockBody = MyBodyParser::getInstance()->bodyFormJson(blockSprite, "BRICK-L");
			break;
		}
		case BlockType::O_BLOCK:
		{
			blockSprite = Sprite::create(BRICK_O);
			blockBody = MyBodyParser::getInstance()->bodyFormJson(blockSprite, "BRICK-O");
			break;
		}
		case BlockType::S_BLOCK:
		{
			blockSprite = Sprite::create(BRICK_S);
			blockBody = MyBodyParser::getInstance()->bodyFormJson(blockSprite, "BRICK-S");
			break;
		}
		case BlockType::Z_BLOCK:
		{
			blockSprite = Sprite::create(BRICK_Z);
			blockBody = MyBodyParser::getInstance()->bodyFormJson(blockSprite, "BRICK-Z");
			break;
		}
		case BlockType::T_BLOCK:
		{
			blockSprite = Sprite::create(BRICK_T);
			blockBody = MyBodyParser::getInstance()->bodyFormJson(blockSprite, "BRICK-T");
			break;
		}
		case BlockType::BONUS_BLOCK:
		{
			blockSprite = Sprite::create(TEST_BLOCK);
			blockBody = PhysicsBody::createBox(blockSprite->getContentSize());
			break;
		}
	}
	blockSprite->setAnchorPoint(Point(0.5f, 0.5f));
	//physiscs activation!!
	blockBody->setGravityEnable(true);
	blockBody->setDynamic(true);
	blockBody->setRotationEnable(true);
	blockBody->setContactTestBitmask(true);
	blockBody->setCollisionBitmask(BLOCKS_BITMASK);
	blockBody->setMass(0.9f);
	blockBody->setRotationEnable(true);
	blockSprite->setPhysicsBody(blockBody);
	blockSprite->setPosition(point);
	//~physics beatch!

	touchable = true;
}


//draw a box to layer
void Blocks::drawBlock(cocos2d::Layer *layer)
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
//get block's body
PhysicsBody *Blocks::getBody()
{
	return blockBody;
}
//touchable stuff
bool Blocks::isTouchable()
{
	return touchable;
}
void Blocks::toggleTouchable()
{
	touchable = !touchable;
}
//static stuff
bool Blocks::isStatic()
{
	return !blockBody->isDynamic();
}
void Blocks::toggleStatic()
{
	blockBody->setDynamic(isStatic());
}

void Blocks::destroyBlock()
{
	auto remove = RemoveSelf::create(true);
	blockSprite->runAction(remove);
	//blockBody->release();
}

//generates a random number between two numbers
float Blocks::RandomFloatBetween(float smallNumber, float bigNumber)
{
    float diff = bigNumber - smallNumber;
    return (((float) rand() / RAND_MAX) * diff) + smallNumber;
}
int Blocks::RandomIntBetween(int smallNumber, int bigNumber)
{
    int diff = bigNumber - smallNumber;
    return rand() % diff + smallNumber;
}

Blocks::BlockType Blocks::pickABlock()
{
	int random = RandomIntBetween(0, NUMBER_OF_BLOCKS);
	return BlockType(random);
}

cocos2d::Vec2 Blocks::GeneratePoint(float startWidth, float endWidth, float height)
{
	Vec2 point = Vec2::ZERO;
	point.x = RandomFloatBetween(startWidth, endWidth);
	point.y = height;
	return point;
}
