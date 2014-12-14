
#ifndef __TOUCH_MANAGER_H__
#define __TOUCH_MANAGER_H__

#include "cocos2d.h"

USING_NS_CC;

class FixedBlock;

class TouchHandler
{

public:
	void touchBegan(const Point& location);

	void touchMoved(const Point& location);

	/**
	* when the touch is ended to move.
	* 
	* @param location touched position(Real coord)
	*/
	void touchEnded(const Point& location);

private:
	FixedBlock*	_touchedBlock;

	Point	_oldIndex;
	Point	_oldLocation;

	int		_canMove;

	bool	_touched;
	bool	_moved;

};

#endif