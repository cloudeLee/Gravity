
/**

@file    Board.h
@author  cloude.leez@gmail.com
@created Nov 24, 2014 21:40:20 AM

*/

#ifndef __BLOCK_MOVER_H__
#define __BLOCK_MOVER_H__

#include "cocos2d.h"
#include "block/Block.h"
#include "block/BlockType.h"

USING_NS_CC;

class Block;
class NormalBlock;

struct CheckResult
{
public:
	Point next;
	BlockType type;
};

class BlockMover
{
public:
	BlockMover()
		: _checkCount(0)
	{}

	void checkMovable(NormalBlock* inBlock);

	void moveTo(NormalBlock* inBlock, Point inNext);
	void moveDone(Node* pSender, Point inNext);

	void rotateBy(Block* block);
	void rotateDone(Node* pSender);

	void changePosition(Block* block, Point pos);

private:
	
	/**
	* get next block's position
	*/
	CheckResult getNextPosition(NormalBlock* inBlock);

	bool checkNext(const BlockType& type);

	void moveBlock(NormalBlock* block, Vec2 next);
	
	const cocos2d::Point& getNextByUpArrow(NormalBlock* inBlock);
	const cocos2d::Point& getNextByDownArrow(NormalBlock* inBlock);
	const cocos2d::Point& getNextByLeftArrow(NormalBlock* inBlock);
	const cocos2d::Point& getNextByRightArrow(NormalBlock* inBlock);

	cocos2d::Point getNextByGravity(NormalBlock* inBlock);

private:
	int _checkCount;

};

#endif