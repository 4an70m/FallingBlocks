#include "Blocks.h"

USING_NS_CC;

bool Blocks::createBlocks = true;
Blocks::Blocks()
{
}
void Blocks::init()
{
	blockSprite = Sprite::create(BRICK_L);
	blockSprite = Sprite::create(BRICK_O);
	blockSprite = Sprite::create(BRICK_Z);
	blockSprite = Sprite::create(BRICK_T);
	blockSprite = Sprite::create(BRICK_J);
	blockSprite = Sprite::create(BRICK_S);
	blockSprite = Sprite::create(BRICK_I);
	blockSprite = Sprite::create(BONUS_BLOCKS);
	blockSprite = Sprite::create(MEGABLOCK);
}

//default constructor
Blocks *Blocks::create(cocos2d::Point point, BlockSuperType blockSuperType)
{
	Blocks *block = new Blocks();
	Blocks::BlockType enumer;
	if(blockSuperType == BlockSuperType::NORMAL_BLOCK)
	{
		MyBodyParser::getInstance()->parseJsonFile(BRICK_BODIES);
		block->blockType = Blocks::pickABlock();
		char *spriteName;
		char *spritePath;
		switch(block->blockType)
		{
			case Blocks::BlockType::L_BLOCK:
			{
				spriteName = "BRICK-L";
				spritePath = BRICK_L;
				break;
			}
			case Blocks::BlockType::O_BLOCK:
			{
				spriteName = "BRICK-O";
				spritePath = BRICK_O;
				break;
			}
			case Blocks::BlockType::Z_BLOCK:
			{
				spriteName = "BRICK-Z";
				spritePath = BRICK_Z;
				break;
			}
			case Blocks::BlockType::T_BLOCK:
			{
				spriteName = "BRICK-T";
				spritePath = BRICK_T;
				break;
			}
			case Blocks::BlockType::I_BLOCK:
			{
				spriteName = "BRICK-I";
				spritePath = BRICK_I;
				break;
			}
			case Blocks::BlockType::J_BLOCK:
			{
				spriteName = "BRICK-J";
				spritePath = BRICK_J;
				break;
			}
			case Blocks::BlockType::S_BLOCK:
			{
				spriteName = "BRICK-S";
				spritePath = BRICK_S;
				break;
			}
		}
		block->blockSprite = Sprite::create(spritePath);
		block->blockBody = MyBodyParser::getInstance()->bodyFormJson(block->blockSprite, spriteName);
		block->blockSprite->setPhysicsBody(block->blockBody);
		block->blockSprite->setPosition(point);
		block->blockSprite->setRotation(RandomRotation());
		block->blockBody->setContactTestBitmask(true);
		block->blockBody->setCollisionBitmask(BLOCKS_BITMASK);
		block->blockBody->setGroup(-1);
		block->blockBody->setTag(0);
	}
	if(blockSuperType == BlockSuperType::BONUS_BLOCK)
	{
		block->blockSprite = Sprite::create(BONUS_BLOCKS);
		block->blockBody = PhysicsBody::createBox(block->blockSprite->getContentSize());
		block->blockSprite->setPhysicsBody(block->blockBody);
		block->blockSprite->setPosition(point);
		block->blockBody->setTag(Blocks::pickABonus());
		block->blockBody->setContactTestBitmask(true);
		block->blockBody->setCollisionBitmask(BLOCKS_BITMASK);
		block->blockBody->setMass(0.01f);
		block->blockBody->setGroup(-1);
	}
	if(blockSuperType == BlockSuperType::MEGA_BLOCK)
	{
		MyBodyParser::getInstance()->parseJsonFile(BRICK_BODIES);
		block->blockSprite = Sprite::create(MEGABLOCK);
		block->blockBody = MyBodyParser::getInstance()->bodyFormJson(block->blockSprite, "BRICK-BIG");
		block->blockSprite->setPhysicsBody(block->blockBody);
		block->blockSprite->setPosition(point);
		block->blockBody->setTag(0);
		block->blockBody->setContactTestBitmask(true);
		block->blockBody->setCollisionBitmask(MEGABLOCK_BITMASK);
		block->blockBody->setGravityEnable(false);
		block->blockSprite->setRotation(-10.0f);
		block->blockBody->setGroup(-1);
	}
	return block;
}


//draw a box to layer
void Blocks::drawBlock(cocos2d::Layer *layer, int zOrder, int speedOfFalling)
{
	blockBody->setGravityEnable(false);
	layer->addChild(this->getSprite(), zOrder);
	auto move = MoveTo::create(speedOfFalling, Point(this->getSprite()->getPositionX(), -this->getSprite()->getContentSize().height / 2));
	auto remove = RemoveSelf::create(true);
	auto seq = Sequence::create(move, remove, NULL);
	this->getSprite()->runAction(seq);
}
void Blocks::drawBlock(cocos2d::Layer *layer, int zOrder)
{
	layer->addChild(this->getSprite(), zOrder);
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

Point Blocks::remove(const PhysicsContact &contact, Layer *layer)
{
	float x = 0;
	float y = 0;
	if(BLOCKS_BITMASK == contact.getShapeA()->getBody()->getCollisionBitmask())
	{
		x = contact.getShapeA()->getBody()->getPosition().x;
		y = contact.getShapeA()->getBody()->getPosition().y;
		contact.getShapeA()->getBody()->removeFromWorld();
		layer->removeChild(contact.getShapeA()->getBody()->getNode());

	}
	else
	{
		x = contact.getShapeB()->getBody()->getPosition().x;
		y = contact.getShapeB()->getBody()->getPosition().y;
		contact.getShapeB()->getBody()->removeFromWorld();
		layer->removeChild(contact.getShapeB()->getBody()->getNode());
	}
	return Point(x, y);
}

Point Blocks::remove(Layer *layer)
{
	float x = 0;
	float y = 0;
	x = blockSprite->getPosition().x;
	y = blockSprite->getPosition().y;
	blockBody->removeFromWorld();
	layer->removeChild(blockSprite);
	return Point(x, y);
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
int Blocks::RandomRotation()
{
	int rotationChooser = RandomIntBetween(0,3);
	switch(rotationChooser)
	{
	case 0: return 0;
	case 1: return 90;
	case 2: return 180;
	case 3: return 270;
	}
}

Blocks::BlockType Blocks::pickABlock()
{
	return BlockType(RandomIntBetween(0, NUMBER_OF_BLOCKS));
}

int Blocks::pickABonus()
{
	return RandomIntBetween(101, 101 + NUMBER_OF_BONUS);
}

cocos2d::Vec2 Blocks::GeneratePoint(float startWidth, float endWidth, float height)
{
	Vec2 point = Vec2::ZERO;
	point.x = RandomFloatBetween(startWidth, endWidth);
	point.y = height;
	return point;
}

void Blocks::emittParticles(cocos2d::Layer *layer, cocos2d::Point point)
{
	ParticleSystemQuad *emitter = ParticleSystemQuad::create("Json/XXX.plist");
	emitter->retain();
	emitter->setPosition(point);
	layer->addChild(emitter, PARTICLE_ZORDER);
}
char* Blocks::getBlockType()
{
	return (char *[]){
		"O_BLOCK",
		"S_BLOCK",
		"Z_BLOCK",
		"J_BLOCK",
		"L_BLOCK",
		"I_BLOCK",
		"T_BLOCK",
		"BONUS_BLOCK"
	}[(int)this->blockType];
}
char* Blocks::getBonusType(int bonusType)
{
	return (char *[]){
		"a tiny bonus",
		"a speedy bonus",
		"x2 points",
		"a stronger gravity",
		"a weaker gravity"
	}[bonusType];
}
