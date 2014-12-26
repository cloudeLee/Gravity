
#ifndef __MAP_EDITOR_LAYER_H__
#define __MAP_EDITOR_LAYER_H__

#include "cocos2d.h"
#include "ui/UIButton.h"
#include "ui/UIEditBox/UIEditBox.h"

#include "BlockPainter.h"
#include "BlockType.h"

#include <functional>
#include <vector>

USING_NS_CC;

using namespace ui;

class MapEditorLayer : public cocos2d::Layer
{
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	bool onTouchBegan(Touch* touch, Event* event);
	void onTouchMoved(Touch* touch, Event* event);
	void onTouchEnded(Touch* touch, Event* event);

	void onTouchButton(Ref *pSender, ui::Widget::TouchEventType type);

	// implement the "static create()" method manually
	CREATE_FUNC(MapEditorLayer);

private:
	void setMapToolUI();
	void setBlockUI();
	void setButtonTypes();
	ui::Button* createButtonBlock(const BlockType& type, const Vec2& pos);

	Sprite* getSpriteAt(const Vec2& touchedLocation); 

	void moveLayer(Touch* touch);
	void setBlockAt(Touch* at);

	void onButtonTouchEnded(Ref *pSender, ui::Widget::TouchEventType type);
	void createNewStage();

private:
	BlockPainter				_blockPainter;

	cocos2d::Vector<ui::Button*>	_buttons;
	std::vector<BlockType>		_buttonTypes;

	BlockType	_selectedButton;

	bool _isScrolling;


	Sprite*			_background;
	ui::EditBox*	_edtRowCount;
	ui::EditBox*	_edtColCount;

	ui::Button*	_btnCreate;
	ui::Button*	_btnLoadXML;
	ui::Button*	_btnLoadBin;
	ui::Button*	_btnSave;
};

enum MapButton
{
	CREATE,
	LOAD_XML,
	LOAD_BIN,
	SAVE
};

#endif // __MAP_EDITOR_LAYER_H__