#include "RotatingButton.h"
#include "BlockManager.h"
#include "GravityDirection.h"

RotatingButton* RotatingButton::create(const std::string& path)
{
	RotatingButton* button = new RotatingButton();
	if (button->initWithFile(path))
	{
		button->autorelease();
		button->addEvents();
		return button;
	}

	CC_SAFE_DELETE(button);
	return nullptr;
}

void RotatingButton::addEvents()
{
	auto listener = cocos2d::EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = [&](cocos2d::Touch* touch, cocos2d::Event* event)
	{
		cocos2d::Vec2 p = touch->getLocation();
		cocos2d::Rect rect = this->getBoundingBox();

		if (rect.containsPoint(p))
		{
			onTouchBegan(touch, event);

			return true; // to indicate that we have consumed it.
		}

		return false; // we did not consume this event, pass thru.
	};

	listener->onTouchMoved = [=](cocos2d::Touch* touch, cocos2d::Event* event)
	{
		onTouchMoved(touch, event);
	};

	listener->onTouchEnded = [=](cocos2d::Touch* touch, cocos2d::Event* event)
	{
		onTouchEnded(touch, event);
	};

	cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void RotatingButton::initButton(cocos2d::Vec2 initial, float rotatingAngle)
{
	// get the unit vector based on initialAngle
	_initial = initial;
	_rotatingAngle = rotatingAngle;
}

bool RotatingButton::onTouchBegan(Touch* touch, Event* event)
{
	_old = touch->getLocation();

	return true;
}

void RotatingButton::onTouchMoved(Touch* touch, Event* event)
{
	Vec2 diff = touch->getLocation() - _old;
	GravityDirection direction;

	if (abs(diff.x) >= abs(diff.y))
	{
		if (abs(diff.x) < this->getContentSize().width)
			return;

		if (diff.x >= 0)
		{
			direction = GravityDirection::RIGHT;
		}
		else
		{
			direction = GravityDirection::LEFT;
		}
	}
	else
	{
		if (abs(diff.y) < this->getContentSize().height)
			return;

		if (diff.y >= 0)
		{
			direction = GravityDirection::UP;
		}
		else
		{
			direction = GravityDirection::DOWN;
		}
	}

	if (onChangedCallback)
	{
		onChangedCallback(direction);
	}
}

void RotatingButton::onTouchEnded(Touch* touch, Event* event)
{
	// call the callback function
}