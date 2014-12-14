
#include "HUDUILayer.h"
#include "Button.h"
#include "RotatingButton.h"
#include "block/GravityDirection.h"
#include "manager/BlockManager.h"

bool HUDUILayer::init()
{
	initButtons();
	
	_isGravityWork = false;

	return true;
}

void HUDUILayer::initButtons()
{
	_btnPower = Button::create("res/power.png");
	_btnPower->setPosition(Vec2(10, 10));
	_btnPower->setAnchorPoint(Vec2(0, 0));

	_btnPower->onTouchBeganCallback = onTouchBegan();
	_btnPower->onTouchEndedCallback = onTouchEnded();
	
	addChild(_btnPower);

	_gravityArrow2 = RotatingButton::create("res/arrow.png");
	_gravityArrow2->setPosition(Vec2(200, 100));

	_gravityArrow2->onChangedCallback = onChanged();
// 	_gravityArrow2->onTouchEnded = onTouchEnded();

	addChild(_gravityArrow2);
}

std::function<void(Node*, Vec2)> HUDUILayer::onTouchBegan()
{
	return [&](Node* target, Vec2 pos)
	{
		if (target == _btnPower)
		{
			CCLOG("gravity Arrow Touched");
		}
	};
}


std::function<void(Node*, Vec2)> HUDUILayer::onTouchEnded()
{
	return [&](Node* target, Vec2 pos)
	{
		if (target == _btnPower)
		{
			_isGravityWork = !_isGravityWork;
			BlockManager::getInstance()->turnGravityOn(_isGravityWork);
		}
	};
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