
#ifndef __ROTATING_BUTTON_H__
#define __ROTATING_BUTTON_H__

#include "cocos2d.h"
#include "GravityDirection.h"

USING_NS_CC;

class RotatingButton : public Sprite
{
public:
	static RotatingButton* create(const std::string& path);

	/**
	* Initialize the button that can be rotated by dragging
	*
	* @param initial
	* @param rotatingAngle the angle that get rotated
	*		( if angle is 90, button get rotated when dragging over 90 degree )
	*/
	void initButton(cocos2d::Vec2 initial, float rotatingAngle = 90);


	std::function<void(GravityDirection)> onChangedCallback;

protected:
	virtual bool onTouchBegan(Touch* touch, Event* event);
	virtual void onTouchMoved(Touch* touch, Event* event);
	virtual void onTouchEnded(Touch* touch, Event* event);

	void addEvents();

private:
	float _rotatingAngle;
	Vec2 _initial;
	Vec2 _old;
};

#endif