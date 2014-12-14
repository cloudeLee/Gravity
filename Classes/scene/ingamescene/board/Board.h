
/**

@file    Board.h
@author  cloude.leez@gmail.com
@created Nov 19, 2014 23:37:20 AM

*/

#ifndef __BOARD_H__
#define __BOARD_H__

#include <vector>
#include <assert.h>

#include "BoardItem.h"
#include "utils/Singleton.h"

class Board : public Singleton<Board>
{
	SINGLETON_INIT(Board)

public:

	const static int CEIL_INDEX = 3;

	/**
	@brief Initialize the board based on the current level
	@param inStageId
	*/
	void init(size_t inStageId);

	/**
	@brief retrieve the block's type at index on the board
	@param inIndex
	@return if there's no item, return the std::nullptr_t;
	*/
	inline BlockType getTypeAt(size_t inIndex)
	{
		assert((_board.size() >= inIndex + 1), "index is over the size");

		return _board[inIndex].getType();
	}

	/**
	@ref Board::getTypeAt(int inIndex)
	*/
	inline BlockType getTypeAt(const cocos2d::Point& p)
	{
		return getTypeAt(to(p.x, p.y));
	}

	/**
	@ref Board::getTypeAt(int inIndex)
	*/
	inline BlockType getTypeAt(size_t inX, size_t inY)
	{
		return getTypeAt(to(inX, inY));
	}

	inline Block* getBlockAt(const cocos2d::Point& p)
	{
		return getBlockAt(to(p.x, p.y));
	}

	inline Block* getBlockAt(size_t inIndex)
	{
		assert((_board.size() >= inIndex + 1), "index is over the size");
		
		return _board[inIndex].getBlock();
	}

	inline Block* getBlockAt(size_t inX, size_t inY)
	{
		return getBlockAt(to(inX, inY));
	}

	/**
	@brief set the new item on the board
	@param inIndex 
	@param inType 
	@param inBlock
	*/
	inline void setItemAt(size_t inIndex, const BlockType& inType, Block* inBlock = nullptr)
	{
		if (_board.size() < inIndex)
		{
			assert("board.size() < index");
			return;
		}

		_board[inIndex].setItem(inType, inBlock); 
	}

	/**
	@ref Board::setItemAt(int inIndex, BlockType inType)
	*/
	inline void setItemAt(size_t inX, size_t inY, const BlockType& inType, Block* inBlock = nullptr)
	{
		setItemAt(to(inX, inY), inType, inBlock);
	}

	inline void setBlockAt(size_t inX, size_t inY, Block* inBlock)
	{
		setBlockAt(to(inX, inY), inBlock);
	}

	inline void setBlockAt(size_t inIndex, Block* inBlock)
	{
		_board[inIndex].setBlock(inBlock);
	}

	inline void setTypeAt(const cocos2d::Point& point, const BlockType& type)
	{
		setTypeAt(to(point.x, point.y), type);
	}

	inline void setTypeAt(size_t index, const BlockType& type)
	{
		assert((_board.size() >= index + 1), "index is over the size");

		_board[index].setType(type);
	}

	/**
	@brief swap the items in the board
	*/
	inline void swap(size_t lhsX, size_t lhsY, size_t rhsX, size_t rhsY)
	{
		BoardItem lhs = _board[to(lhsX, lhsY)];
		BoardItem rhs = _board[to(rhsX, rhsY)];
		
		_board[to(lhsX, lhsY)] = rhs;
		_board[to(rhsX, rhsY)] = lhs;
	}

	inline void swap(Point lhs, Point rhs)
	{
		swap(lhs.x, lhs.y, rhs.x, rhs.y);
	}

	/**
	@brief convert 2D indice to 1D index
	@return 1D index
	*/
	inline int to(size_t inX, size_t inY)
	{
		return inX * _colCount + inY;
	}

	/** Property */
	size_t getRowCount() const
	{
		return _rowCount;
	}

	size_t getColCount() const
	{
		return _colCount;
	}

	

private:
	std::vector<BoardItem> _board;
	int _rowCount;
	int _colCount;

};


#endif	//__BOARD_H__