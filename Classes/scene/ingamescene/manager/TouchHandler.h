
#ifndef __TOUCH_MANAGER_H__
#define __TOUCH_MANAGER_H__

#include "cocos2d.h"

USING_NS_CC;

class FixedBlock;

class TouchHandler
{

public:
	void init();

	void touchBegan(const Point& location);

	void touchMoved(Touch* touch);

	void touchEnded(const Point& location);

private:
	void moveBoardLayer(const Vec2& pre, const Vec2& cur);

private:
	FixedBlock*	_touchedBlock = nullptr;

	Point	_oldIndex;

	bool	_touched;
	bool	_endedCheckRequired;

	Vec2	_scrolledDistance;	// distance that have been scrolled

};

#endif