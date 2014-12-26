
#include "HUDUILayer.h"
#include "GravityDirection.h"
#include "BlockManager.h"

bool HUDUILayer::init()
{
	initButtons();
	
	_isGravityWork = false;

	return true;
}

void HUDUILayer::initButtons()
{
	_btnPower = ui::Button::create("res/power.png");
	_btnPower->setPosition(Vec2(10, 10));
	_btnPower->setAnchorPoint(Vec2(0, 0));
	_btnPower->addTouchEventListener(CC_CALLBACK_2(HUDUILayer::onTouchEnded, this));
		
	addChild(_btnPower);

	_gravityArrow2 = RotatingButton::create("res/arrow.png");
	_gravityArrow2->setPosition(Vec2(200, 100));

	_gravityArrow2->onChangedCallback = onChanged();


	addChild(_gravityArrow2);
}


void HUDUILayer::onTouchEnded(Ref *pSender, ui::Widget::TouchEventType type)
{
	if (type == ui::Widget::TouchEventType::ENDED)
	{
		ui::Button* target = static_cast<ui::Button*>(pSender);
		if (target == _btnPower)
		{
			_isGravityWork = !_isGravityWork;
			BlockManager::getInstance()->turnGravityOn(_isGravityWork);
		}
	}
}



std::function<void(GravityDirection)> HUDUILayer::onChanged()
{
	return[&](GravityDirection direction)
	{
		BlockManager::getInstance()->setGravityDirection(direction);

		switch (direction)
		{
		case GravityDirection::RIGHT:
			_gravityArrow2->setRotation(-90); 
			break;

		case GravityDirection::LEFT:
			_gravityArrow2->setRotation(90);
			break;

		case GravityDirection::UP:
			_gravityArrow2->setRotation(-180);
			break;

		case GravityDirection::DOWN:
			_gravityArrow2->setRotation(0);
			break;
		}
	};
}