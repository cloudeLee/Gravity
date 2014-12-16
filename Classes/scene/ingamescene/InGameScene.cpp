#include "InGameScene.h"

USING_NS_CC;

Scene* InGameScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an InGameScene object
	auto layer = InGameScene::create();

	// add layer as a child to scene
	scene->addChild(layer);


	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool InGameScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	
	// Initialize the layers
	_blockLayer = BlockLayer::create();
	_blockLayer->setTag(LAYER_BLOCK);
	this->addChild(_blockLayer);

	_hudUILayer = HUDUILayer::create();
	_hudUILayer->setTag(LAYER_HUDUI);
	this->addChild(_hudUILayer);

	return true;
}


void InGameScene::menuCloseCallback(Ref* pSender)
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
