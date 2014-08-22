#ifndef __BLOCKS_H__
#define __BLOCKS_H__

#include "cocos2d.h"
#include "Defenitions.h"
#include "MyBodyParser.h"
#include "Coins.h"

class Blocks
{
public:

	enum class BlockType
	{
		I_BLOCK,
		L_BLOCK,
		O_BLOCK,
		Z_BLOCK,
		T_BLOCK,
		J_BLOCK,
		S_BLOCK
	};

	enum class BlockSuperType
	{
		NORMAL_BLOCK,
		BONUS_BLOCK,
		MEGA_BLOCK
	};

	enum class BonusType
	{
		SMALL_BOTO 	= 101,
		FAST_BOTO 	= 102,
		X2_POINTS	= 103,
		FAST_GRAV	= 104,
		SLOW_GRAV	= 105
	};

	Blocks();
	//default create method
	static Blocks *create(cocos2d::Point point, BlockSuperType blockSuperType);
	void init();

	//set current block's position
	void setPosition(cocos2d::Point point);
	//get current block's sprite
	cocos2d::Sprite *getSprite();
	//get current block's body
	cocos2d::PhysicsBody *getBody();

	//generate single block
	void drawBlock(cocos2d::Layer *layer, int zOrder);
	void drawBlock(cocos2d::Layer *layer, int zOrder, int speedOfFalling);

	char* getBlockType();
	static char* getBonusType(int bonusType);

	//function which picks a random block
	static BlockType pickABlock();
	static int pickABonus();
	//removes block
	static cocos2d::Point remove(const cocos2d::PhysicsContact &contact, cocos2d::Layer *layer);
	cocos2d::Point remove(cocos2d::Layer *layer);
	//emitter action
	static void emittParticles(cocos2d::Layer *layer, cocos2d::Point point);
	//random generator
	static float RandomFloatBetween(float smallNumber, float bigNumber);
	static int RandomIntBetween(int smallNumber, int bigNumber);
	//functions generates a random point at a constant height
	static cocos2d::Vec2 GeneratePoint(float startWidth, float endWidth, float height);
	static int RandomRotation();

	static bool createBlocks;

private:
	//block
	cocos2d::Sprite *blockSprite;
	//block's physic body
	cocos2d::PhysicsBody *blockBody;
	BlockType blockType;
	BlockSuperType blockSuperType;
};

#endif // __BLOCKS_H__
