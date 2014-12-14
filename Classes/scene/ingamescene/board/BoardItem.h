
/**

@file    BoardItem.h
@author  cloude.leez@gmail.com
@created Nov 23, 2014 21:46:10 AM

*/

#ifndef __BOARD_ITEM_H__
#define __BOARD_ITEM_H__

#include "block/BlockType.h"
#include "block/Block.h"

class BoardItem
{
public:
	BoardItem(BlockType inType, Block* inBlock = nullptr)
		: _block(inBlock), _type(inType)
	{

	}

	inline void setItem(const BlockType& inType, Block* inBlock = nullptr)
	{
		_type = inType;
		_block = inBlock;
	}

	inline Block* getBlock()
	{
		return _block;
	}

	inline void setBlock(Block* inBlock)
	{
		_block = inBlock;
	}

	inline BlockType getType()
	{
		return _type;
	}

	inline void setType(const BlockType& inType)
	{
		_type = inType;
	}

private:
	Block*		_block = nullptr;
	BlockType	_type;

};


#endif
