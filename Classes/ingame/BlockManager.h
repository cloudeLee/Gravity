
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

	void stopCheckingStep(bool stop);

	void initBlockAt(const BlockType& type, int x, int y);
private:
	Block* createBlock(const BlockType& type, Sprite* sprite, int x, int y);
	
private:
	std::vector<NormalBlock*> _blocks;
	BlockMover		_blockMover;
	BlockPainter*	_blockPainter;

	bool _stopStep;

#if SEAFT_MAP_EDITOR

public:
	void clearAllBlocks();

#endif
};

#endif