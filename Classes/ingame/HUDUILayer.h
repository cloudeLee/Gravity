
#ifndef __HUD_UI_LAYER_H__
#define __HUD_UI_LAYER_H__

#include "cocos2d.h"
#include "ui/UIButton.h"

#include <functional>
#include "GravityDirection.h"
#include "RotatingButton.h"

USING_NS_CC;

class HUDUILayer : public cocos2d::Layer
{
public:
	virtual bool init();

	CREATE_FUNC(HUDUILayer);

	
private:
	void initButtons();
	
	void onTouchEnded(Ref *pSender, ui::Widget::TouchEventType type);

	std::function<void(GravityDirection)> onChanged();


private:
	ui::Button* _btnPower;
	RotatingButton* _gravityArrow2;

	bool _isGravityWork;
};


#endif