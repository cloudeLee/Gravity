#ifndef __IN_GAME_SCENE_H__
#define __IN_GAME_SCENE_H__

#include "cocos2d.h"

#include "layer/BlockLayer.h"
#include "layer/HUDUILayer.h"

class InGameScene : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(InGameScene);

private:
	HUDUILayer*		_hudUILayer;
	BlockLayer*		_blockLayer;

};

#endif // __IN_GAME_SCENE_H__