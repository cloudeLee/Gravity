
#ifndef __LAYOUT_MANAGER_H__
#define __LAYOUT_MANAGER_H__

#include "cocos2d.h"
#include "utils/Singleton.h"

USING_NS_CC;

class BlockPainter;

class LayoutManager : public Singleton<LayoutManager>
{
	SINGLETON_INIT(LayoutManager)

public:
	void init(BlockPainter* painter);

	/**
	* Get real coordinate on "pos(row, col)"
	*/
	inline Point getCoordAt(const Point& pos)
	{
		return Point(pos.y * _defaultBlockSize + _defaultBlockSize * 2 - _defaultBlockSize*0.5, _startingBlockHeight - pos.x * _defaultBlockSize - _defaultBlockSize + _defaultBlockSize * 0.5);
	}

	/**
	 * Get array's index on coordinate
	 */
	inline Point getIndexAt(const Point& coord)
	{
		return Point(
			static_cast<int>((_startingBlockHeight - coord.y) / _defaultBlockSize), 
			static_cast<int>((coord.x - _defaultBlockSize) / _defaultBlockSize)
			);
	}

	inline int getDefaultBlockSize()
	{
		return _defaultBlockSize;
	}

	inline int getStartingHeight()
	{
		return _startingBlockHeight;
	}

private:
	int _defaultBlockSize;
	int _startingBlockHeight;

};


#endif