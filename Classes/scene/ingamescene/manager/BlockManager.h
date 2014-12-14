
/**

@file    BlockManager.h
@author  cloude.leez@gmail.com
@created Nov 23, 2014 22:06:00 AM

*/

#ifndef __BLOCK_MANAGER_H__
#define __BLOCK_MANAGER_H__

#include "cocos2d.h"
#include "BlockMover.h"
#include "utils/Singleton.h"

class Block;
class NormalBlock;
class BlockPainter;
enum class BlockType;


class BlockManager : public Singleton<BlockManager>
{
	SINGLETON_INIT(BlockManager)

public:
	void init(BlockPainter* painter);
	void dispose()
	{
		_blocks.clear();
	}

	void step();

	BlockMover* getBlockMover()
	{
		return &_blockMover;
	}

	/**
	* turn on/off the gravity. if gravity turns on, blocks are started to move.
	*/
	void turnGravityOn(bool on);

	void setGravityDirection(const GravityDirection& direction);

private:
	Block* createBlock(const BlockType& type, Sprite* sprite, int x, int y);
	
private:
	//cocos2d::Vector<NormalBlock*> _blocks;
	std::vector<NormalBlock*> _blocks;
	BlockMover		_blockMover;
};

#endif