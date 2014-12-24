
#ifndef __BUTTON_H__
#define __BUTTON_H__

#include "cocos2d.h"
#include <functional>

USING_NS_CC;

class Button : public Sprite
{
public:
	static Button* create(const std::string& path);
	static Button* createWithSprite(Sprite* sprite);

	std::function<void(Node*, Vec2)> onTouchBeganCallback;
	std::function<void(Node*, Vec2)> onTouchMovedCallback;
	std::function<void(Node*, Vec2)> onTouchEndedCallback;


protected:
	virtual bool onTouchBegan(Touch* touch, Event* event);
	virtual void onTouchMoved(Touch* touch, Event* event);
	virtual void onTouchEnded(Touch* touch, Event* event);

	void addEvents();
};


#endif