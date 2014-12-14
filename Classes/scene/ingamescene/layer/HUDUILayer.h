
#ifndef __HUD_UI_LAYER_H__
#define __HUD_UI_LAYER_H__

#include "cocos2d.h"
#include <functional>
#include "block/GravityDirection.h"

USING_NS_CC;

class Button;
class RotatingButton;

class HUDUILayer : public cocos2d::Layer
{
public:
	virtual bool init();

	CREATE_FUNC(HUDUILayer);

	
private:
	void initButtons();
	
	std::function<void(Node*, Vec2)> onTouchBegan();
	std::function<void(Node*, Vec2)> onTouchEnded();

	std::function<void(GravityDirection)> onChanged();


private:
	Button* _btnPower;
	RotatingButton* _gravityArrow2;

	bool _isGravityWork;
};


#endif