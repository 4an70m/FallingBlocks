#include "Blocks.h"

USING_NS_CC;

bool Blocks::createBlocks = true;

//default constructor
Blocks::Blocks(cocos2d::Point point, BlockSuperType blockSuperType)
{
	switch(blockSuperType)
	{
		case BlockSuperType::MEGABLOCK:
		{
			MyBodyParser::getInstance()->parseJsonFile(BRICK_BODIES);
			blockSprite = Sprite::create(BRICK_BIG);
			blockBody = MyBodyParser::getInstance()->bodyFormJson(blockSprite, "BRICK-BIG");
			blockBody->setContactTestBitmask(true);
			blockBody->setCollisionBitmask(BIGBLOCK_BITMASK);
			blockBody->setDynamic(false);
			blockBody->setGroup(-1);
			blockSprite->setRotation(10.0f);
			blockSprite->setPhysicsBody(blockBody);
			break;
		}
		case BlockSuperType::BONUS_BLOCK:
		{
			//bonus block
			blockSprite = Sprite::create(TEST_BLOCK);
			blockBody = PhysicsBody::createBox(blockSprite->getContentSize());
			//tag bonus type
			//enum bonus type
			blockBody->setTag(pickABonus());
			blockSprite->setPhysicsBody(blockBody);
			blockSprite->setPosition(point);
			blockBody->setContactTestBitmask(true);
			blockBody->setCollisionBitmask(BLOCKS_BITMASK);
			blockBody->setMass(0.1f);
			blockBody->setGroup(-1);
			break;
		}
		case BlockSuperType::NORMAL_BLOCK:
		{
			MyBodyParser::getInstance()->parseJsonFile(BRICK_BODIES);
			//actually here i pick a block
			blockType = pickABlock();

			switch(blockType)
			{
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
				case BlockType::I_BLOCK:
				{
					blockSprite = Sprite::create(BRICK_I);
					blockBody = MyBodyParser::getInstance()->bodyFormJson(blockSprite, "BRICK-I");
					break;
				}
			}
			blockSprite->setPhysicsBody(blockBody);
			blockSprite->setPosition(point);
			blockSprite->setRotation(RandomRotation());
			blockBody->setContactTestBitmask(true);
			blockBody->setCollisionBitmask(BLOCKS_BITMASK);
			blockBody->setMass(0.1f);
			blockBody->setGroup(-1);
			blockBody->setTag(0);
			//~physics beatch!
		}
	}
}


//draw a box to layer
void Blocks::drawBlock(cocos2d::Layer *layer, int zOrder)
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
