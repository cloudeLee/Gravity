#ifndef __MAIN_GAME_LAYER_H__
#define __MAIN_GAME_LAYER_H__

#include "cocos2d.h"
#include "board/Board.h"
#include "manager/BlockPainter.h"
#include "manager/TouchHandler.h"

USING_NS_CC;

class BlockLayer : public cocos2d::Layer
{
public:

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	bool onTouchBegan(Touch* touch, Event* event);
	void onTouchMoved(Touch* touch, Event* event);
	void onTouchEnded(Touch* touch, Event* event);

	// implement the "static create()" method manually
	CREATE_FUNC(BlockLayer);

	virtual void update(float dt);
	
private:
	BlockPainter	_blockPainter;
	TouchHandler	_touchHandler;
	

};

#endif // __MAIN_GAME_LAYER_H__