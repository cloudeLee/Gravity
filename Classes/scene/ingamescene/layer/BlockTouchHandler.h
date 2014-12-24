
#ifndef __BLOCK_TOUCH_HANDLER_H__
#define __BLOCK_TOUCH_HANDLER_H__

#include "cocos2d.h"

USING_NS_CC;

class FixedBlock;

class BlockTouchHandler
{
public:
	void onTouchBeganBlockLayer(const Vec2& pos);
	void onTouchMovedBlockLayer(Touch*, Node* layer);
	void onTouchEndedBlockLayer(const Vec2& pos);

private:
	bool	_touched;
	bool	_endedCheckRequired;
	Point	_oldIndex;

	FixedBlock*	_touchedBlock = nullptr;
};


#endif