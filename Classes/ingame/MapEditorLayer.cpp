
#include "MapEditorLayer.h"
#include "InGameScene.h"
#include "LayoutManager.h"
#include "TouchManager.h"
#include "BlockManager.h"

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

	setMapToolUI();


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
	
	setBlockAt(touch);
}

void MapEditorLayer::onTouchEnded(Touch* touch, Event* event)
{
	if (_isScrolling)
		return;

	setBlockAt(touch);
}


void MapEditorLayer::setBlockAt(Touch* at)
{
	Vec2 coord = TouchManager::getInstance()->touchEnded(at->getLocation(), true);
	CCLOG("%f %f", coord.x, coord.y);

	// locate the block on edge when touching at out of the board, 
	int row = Board::getInstance()->getRowCount();
	int col = Board::getInstance()->getColCount();
	if (row <= coord.x)		coord.x = row - 1;
	if (col <= coord.y)		coord.y = col - 1;
	if (coord.x < 0)		coord.x = 0;
	if (coord.y < 0)		coord.y = 0;

	if (_selectedButton != BlockType::EMPTY && _selectedButton != Board::getInstance()->getTypeAt(coord))
	{
		BlockManager::getInstance()->initBlockAt(_selectedButton, coord.x, coord.y);
	}
}


void MapEditorLayer::setMapToolUI()
{
	Sprite* background = Sprite::create("map_editor/background.png");
	background->setPosition(0, 2400);
	background->setAnchorPoint(Vec2(0, 1));
	addChild(background);

	Rect rect = Director::getInstance()->getOpenGLView()->getVisibleRect();
		
	_edtRowCount = EditBox::create(Size(240, 160), Scale9Sprite::create("map_editor/editbox_288x160.png"));
	_edtRowCount->setPosition(Vec2(1200, rect.getMaxY() - 140));
	_edtRowCount->setFontSize(25);
	_edtRowCount->setFontColor(Color3B::BLACK);
	_edtRowCount->setText("5");
	_edtRowCount->setReturnType(EditBox::KeyboardReturnType::DONE);
	addChild(_edtRowCount);

	_edtColCount = EditBox::create(Size(240, 160), Scale9Sprite::create("map_editor/editbox_288x160.png"));
	_edtColCount->setPosition(Vec2(1700, rect.getMaxY() - 140));
	_edtColCount->setFontSize(25);
	_edtColCount->setFontColor(Color3B::BLACK);
	_edtColCount->setText("5");
	_edtColCount->setReturnType(EditBox::KeyboardReturnType::DONE);
	addChild(_edtColCount);

	_btnCreate = ui::Button::create("map_editor/create_button.png");
	_btnCreate->setPosition(Vec2(2100, rect.getMaxY() - 140));
	_btnCreate->addTouchEventListener(CC_CALLBACK_2(MapEditorLayer::onTouchButton, this));
	_btnCreate->setTag(MapButton::CREATE);
	addChild(_btnCreate);

	_btnLoadXML = ui::Button::create("map_editor/load_xml_button.png");
	_btnLoadXML->setPosition(Vec2(2550, rect.getMaxY() - 140));
	_btnLoadXML->addTouchEventListener(CC_CALLBACK_2(MapEditorLayer::onTouchButton, this));
	_btnLoadXML->setTag(MapButton::LOAD_XML);
	addChild(_btnLoadXML);

	_btnLoadBin = ui::Button::create("map_editor/load_bin_button.png");
	_btnLoadBin->setPosition(Vec2(3000, rect.getMaxY() - 140));
	_btnLoadBin->addTouchEventListener(CC_CALLBACK_2(MapEditorLayer::onTouchButton, this));
	_btnLoadBin->setTag(MapButton::LOAD_BIN);
	addChild(_btnLoadBin);

	_btnSave = ui::Button::create("map_editor/save_button.png");
	_btnSave->setPosition(Vec2(3450, rect.getMaxY() - 140));
	_btnSave->addTouchEventListener(CC_CALLBACK_2(MapEditorLayer::onTouchButton, this));
	_btnSave->setTag(MapButton::SAVE);
	addChild(_btnSave);

	setButtonTypes();
	setBlockUI();
}



void MapEditorLayer::setBlockUI()
{
	auto screenSize = Director::getInstance()->getOpenGLView()->getDesignResolutionSize();

	int buttonCount = _buttonTypes.size();
	for (int i = 0; i < buttonCount; ++i)
	{
		_buttons.pushBack(createButtonBlock(_buttonTypes.at(i), Vec2(i * LayoutManager::getInstance()->getDefaultBlockSize() + 50 + i * 20, screenSize.height - 240)));
	}
}

ui::Button* MapEditorLayer::createButtonBlock(const BlockType& type, const Vec2& pos)
{
	ui::Button* button = ui::Button::create("map_editor/" + _blockPainter.getSpriteFileName(type));
	button->setPosition(pos);
	button->setAnchorPoint(Vec2(0, 1));
	button->setTag(static_cast<int>(type));
	button->addTouchEventListener(CC_CALLBACK_2(MapEditorLayer::onButtonTouchEnded, this));
	
	this->addChild(button);

	return button;
}

void MapEditorLayer::setButtonTypes()
{
	_buttonTypes.push_back(BlockType::EDGE);
	_buttonTypes.push_back(BlockType::NONE);
}


void MapEditorLayer::onButtonTouchEnded(Ref *pSender, ui::Widget::TouchEventType type)
{
	if (type == ui::Widget::TouchEventType::ENDED)
	{
		cocos2d::ui::Button* btn = static_cast<cocos2d::ui::Button*>(pSender);
		BlockType type = static_cast<BlockType>(btn->getTag());
		if (type != _selectedButton)
			_selectedButton = type;
		else
			_selectedButton = BlockType::EMPTY;

		CCLOG("[MapEditorLayer] Selected button is %d", _selectedButton);
	}
}
	
void MapEditorLayer::moveLayer(Touch* touch)
{
	Node* scene = Director::getInstance()->getRunningScene();
	Node* layer = scene->getChildByTag(InGameScene::LAYER_BLOCK, true);

	BlockLayer* blockLayer = static_cast<BlockLayer*>(layer);
	blockLayer->onTouchMoved(touch, nullptr);
}

void MapEditorLayer::onTouchButton(Ref *pSender, ui::Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED)
	{
		Button* btn = static_cast<Button*>(pSender);
		switch (btn->getTag())
		{
		case MapButton::CREATE:
			createNewStage();
			break;

		case MapButton::LOAD_XML:
			break;

		case MapButton::LOAD_BIN:
			break;

		case MapButton::SAVE:
			break;
		}
	}
}

void MapEditorLayer::createNewStage()
{
	int row = atoi(_edtRowCount->getText());
	int col = atoi(_edtColCount->getText());

	if (row <= 0 || col <= 0)
	{
		MessageBox("Row or Col count is wrong", "ERROR");
		return;
	}

	BlockManager::getInstance()->clearAllBlocks();
	Board::getInstance()->createNewBoard(row, col);
	BlockManager::getInstance()->init(nullptr);
}
