
#include "MapEditorLayer.h"
#include "InGameScene.h"
#include "manager/LayoutManager.h"
#include "manager/TouchManager.h"

bool MapEditorLayer::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(MapEditorLayer::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(MapEditorLayer::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(MapEditorLayer::onTouchEnded, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 2);

	_selectedButton = BlockType::EMPTY;

	addChild(_blockPainter.initPainter());

	setButtonTypes();
	setBlockUI();

	return true;
}


bool MapEditorLayer::onTouchBegan(Touch *touch, Event *event)
{
	_isScrolling = false;

	return true;
}



void MapEditorLayer::onTouchMoved(Touch* touch, Event* event)
{
	_isScrolling = true;

	if (_selectedButton == BlockType::EMPTY)
	{
		moveLayer(touch);
		return;
	}


}

void MapEditorLayer::onTouchEnded(Touch* touch, Event* event)
{
	if (_isScrolling)
		return;

	Vec2 coord = TouchManager::getInstance()->touchEnded(touch->getLocation(), true);
	CCLOG("%f %f", coord.x, coord.y);
}


void MapEditorLayer::setBlockUI()
{
	auto screenSize = Director::getInstance()->getOpenGLView()->getDesignResolutionSize();

	int buttonCount = _buttonTypes.size();
	for (int i = 0; i < buttonCount; ++i)
	{
		_buttons.pushBack(createButtonBlock(_buttonTypes.at(i), Vec2(i * LayoutManager::getInstance()->getDefaultBlockSize(), screenSize.height)));
	}
}

Button* MapEditorLayer::createButtonBlock(const BlockType& type, const Vec2& pos)
{
	Button* button = Button::create("map_editor/" + _blockPainter.getSpriteFileName(type));
	button->setPosition(pos);
	button->setAnchorPoint(Vec2(0, 1));
	button->setTag(static_cast<int>(type));

	button->onTouchEndedCallback = onButtonTouchEnded();

	this->addChild(button);

	return button;
}

void MapEditorLayer::setButtonTypes()
{
	_buttonTypes.push_back(BlockType::EDGE);
	_buttonTypes.push_back(BlockType::NONE);
}


std::function<void(Node*, Vec2)> MapEditorLayer::onButtonTouchEnded()
{
	return [&](Node* target, Vec2 pos)
	{
		BlockType type = static_cast<BlockType>(target->getTag());
		if (type != _selectedButton)
			_selectedButton = type;
		else
			_selectedButton = BlockType::EMPTY;

		CCLOG("[MapEditorLayer] Selected button is %d", _selectedButton);
	};
}

void MapEditorLayer::moveLayer(Touch* touch)
{
	Node* scene = Director::getInstance()->getRunningScene();
	Node* layer = scene->getChildByTag(InGameScene::LAYER_BLOCK, true);

	BlockLayer* blockLayer = static_cast<BlockLayer*>(layer);
	blockLayer->onTouchMoved(touch, nullptr);
}

