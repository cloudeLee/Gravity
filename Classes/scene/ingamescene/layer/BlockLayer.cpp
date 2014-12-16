#include "BlockLayer.h"
#include "manager/LayoutManager.h"
#include "manager/BlockManager.h"

USING_NS_CC;


// on "init" you need to initialize your instance
bool BlockLayer::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	// Initialize the board
	Board::getInstance()->init(1);

	// Initialize the assets of blocks
	addChild(_blockPainter.initPainter());

	// Initialize the position that block will be drawed by checking the current resoultion
	LayoutManager::getInstance()->init(&_blockPainter);

	// 
	BlockManager::getInstance()->init(&_blockPainter);
	
	this->scheduleUpdate();	// in order to use "update" function


 	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
 	listener->onTouchBegan = CC_CALLBACK_2(BlockLayer::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(BlockLayer::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(BlockLayer::onTouchEnded, this);

	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 3);
 	
	return true;
}

void BlockLayer::update(float dt)
{
	BlockManager::getInstance()->step();
}


bool BlockLayer::onTouchBegan(Touch *touch, Event *event)
{
	_touchHandler.touchBegan(touch->getLocation());

	return true;
}


void BlockLayer::onTouchMoved(Touch* touch, Event* event)
{
	_touchHandler.touchMoved(touch);
}

void BlockLayer::onTouchEnded(Touch* touch, Event* event)
{
	_touchHandler.touchEnded(touch->getLocation());
}


void BlockLayer::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
	return;
#endif

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
