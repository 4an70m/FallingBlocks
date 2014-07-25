#ifndef __BLOCKS_H__
#define __BLOCKS_H__

#include "cocos2d.h"
#include "Defenitions.h"
#include "MyBodyParser.h"

class Blocks
{
public:

	enum class BlockType
	{
		O_BLOCK,
		S_BLOCK,
		Z_BLOCK,
		J_BLOCK,
		L_BLOCK,
		I_BLOCK,
		T_BLOCK,
		BONUS_BLOCK
	};

	//default constructor
	Blocks(cocos2d::Point point);

	//set current block's position
	void setPosition(cocos2d::Point point);
	//get current block's sprite
	cocos2d::Sprite *getSprite();

	//generate single block
	void DrawBlock(cocos2d::Layer *layer);

	//function which picks a random block
	BlockType PickABlock();

	//functions generates a random point at a constant height
	static cocos2d::Vec2 GeneratePoint(float startWidth, float endWidth, float height);
	//random generator
	static float RandomFloatBetween(float smallNumber, float bigNumber);
private:


	//block
	cocos2d::Sprite *blockSprite;
	//block's physic body
	cocos2d::PhysicsBody *blockBody;

	BlockType blockType;
	//random generator
	static int RandomIntBetween(int smallNumber, int bigNumber);
};

#endif // __BLOCKS_H__
