
/**

@file    Block.h
@author  cloude.leez@gmail.com
@created Nov 23, 2014 22:01:00 AM

*/

#ifndef __BLOCK_H__
#define __BLOCK_H__

#include "cocos2d.h"
#include "GravityDirection.h"

USING_NS_CC;

class Block : public Sprite
{
public:

	inline const Point& getBoardPosition()
	{
		return Point(_x, _y);
	}

	inline void setBoardPosition(size_t inX, size_t inY)
	{
		_x = inX;
		_y = inY;
	}

protected:
	int _x, _y;
	
};

#endif