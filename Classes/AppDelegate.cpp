#include "AppDelegate.h"
#include "scene/ingamescene/InGameScene.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	if (!glview) {
		glview = GLView::create("My Game");
		glview->setFrameSize(800, 1280);
		glview->setFrameZoomFactor(0.5);
		director->setOpenGLView(glview);
	}

	// Set the design resolution
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, kResolutionShowAll);
#else
	//pEGLView->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, kResolutionNoBorder);
	glview->setDesignResolutionSize(1080, 1920, kResolutionExactFit);
#endif

	// turn on display FPS
	director->setDisplayStats(true);

	auto fileUtils = FileUtils::getInstance();
	auto screenSize = glview->getFrameSize();
	std::vector<std::string> resDirOrders;

// 	int screenWidth = screenSize.width <= screenSize.height ? screenSize.width : screenSize.height;
// 
// 	if (screenWidth >= 1600)
// 	{
// 		resDirOrders.push_back("res/ipad");
// 		resDirOrders.push_back("res/iphonehd5");
// 		resDirOrders.push_back("res/iphonehd");
// 		resDirOrders.push_back("res/iphone");
// 
// 		glview->setDesignResolutionSize(1600, 2560, ResolutionPolicy::NO_BORDER);
// 	}
// 	else if (screenWidth >= 1080)
// 	{
// 		resDirOrders.push_back("res/iphonehd5");
// 		resDirOrders.push_back("res/iphonehd");
// 		resDirOrders.push_back("res/iphone");
// 
// 		glview->setDesignResolutionSize(1080, 1920, ResolutionPolicy::NO_BORDER);
// 	}
// 	else if (screenWidth >= 800)
// 	{
// 		resDirOrders.push_back("res/iphonehd");
// 		resDirOrders.push_back("res/iphone");
// 
// 		glview->setDesignResolutionSize(800, 1280, ResolutionPolicy::NO_BORDER);
// 	}
// 	else
// 	{
// 		resDirOrders.push_back("res/iphone");
// 
// 		glview->setDesignResolutionSize(480, 800, ResolutionPolicy::NO_BORDER);
// 	}

	fileUtils->setSearchPaths(resDirOrders);

	// set FPS. the default value is 1.0/60 if you don't call this
	director->setAnimationInterval(1.0 / 60);

	// create a scene. it's an autorelease object
	auto scene = InGameScene::createScene();

	// run
	director->runWithScene(scene);

	return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
