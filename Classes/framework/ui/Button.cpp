
#include "Button.h"

Button* Button::create(const std::string& path)
{
	Button* button = new Button();

	if (button->initWithFile(path))
	{
		button->autorelease();

		//button->initOptions();

		button->addEvents();
		return button;
	}

	CC_SAFE_DELETE(button);
	return nullptr;
}


Button* Button::createWithSprite(Sprite* sprite)
{
	Button* button = new Button();
	if (button->initWithTexture(sprite->getTexture()))
	{
		button->autorelease();

		//button->initOptions();

		button->addEvents();
		return button;
	}

	CC_SAFE_DELETE(button);
	return nullptr;
}


void Button::addEvents()
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

bool Button::onTouchBegan(Touch* touch, Event* event)
{
	if (onTouchBeganCallback)
	{
		onTouchBeganCallback(event->getCurrentTarget(), touch->getLocation());
	}

	return true;
}


void Button::onTouchMoved(Touch* touch, Event* event)
{
	if (onTouchMovedCallback)
	{
		onTouchMovedCallback(event->getCurrentTarget(), touch->getLocation());
	}
}


void Button::onTouchEnded(Touch* touch, Event* event)
{
	if (onTouchEndedCallback)
	{
		onTouchEndedCallback(event->getCurrentTarget(), touch->getLocation());
	}
}

