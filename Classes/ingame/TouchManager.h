
#ifndef __TOUCH_MANAGER_H__
#define __TOUCH_MANAGER_H__

#include "cocos2d.h"
#include "Singleton.h"
#include "LayoutManager.h"

USING_NS_CC;

class FixedBlock;

class TouchManager : public Singleton<TouchManager>
{
	SINGLETON_INIT(TouchManager)

public:

	inline Vec2 touchBegan(const Point& location, bool requiredCoord = false)
	{
		return requiredCoord ?
			LayoutManager::getInstance()->getIndexAt(location - _scrolledDistance) :
			location - _scrolledDistance;
	}

	inline Vec2 touchMoved(Touch* touch)
	{
		Vec2 diff = touch->getLocation() - touch->getPreviousLocation();
		_scrolledDistance += diff;

		return diff;
	}

	inline Vec2 touchEnded(const Point& location, bool requiredCoord = false)
	{
		return requiredCoord ?
			LayoutManager::getInstance()->getIndexAt(location - _scrolledDistance) :
			location - _scrolledDistance;
	}

	inline Vec2 getScrolledDistance()
	{
		return _scrolledDistance;
	}

private:
	Vec2	_scrolledDistance;	// distance that have been scrolled

};

#endif