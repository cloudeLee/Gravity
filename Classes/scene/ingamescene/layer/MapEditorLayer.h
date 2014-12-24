
#ifndef __MAP_EDITOR_LAYER_H__
#define __MAP_EDITOR_LAYER_H__

#include "cocos2d.h"
#include "manager/BlockPainter.h"
#include "block/BlockType.h"
#include "framework/ui/Button.h"

#include <functional>
#include <vector>


USING_NS_CC;

class MapEditorLayer : public cocos2d::Layer
{
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	bool onTouchBegan(Touch* touch, Event* event);
	void onTouchMoved(Touch* touch, Event* event);
	void onTouchEnded(Touch* touch, Event* event);

	// implement the "static create()" method manually
	CREATE_FUNC(MapEditorLayer);

private:
	void setBlockUI();
	void setButtonTypes();
	Button* createButtonBlock(const BlockType& type, const Vec2& pos);

	Sprite* getSpriteAt(const Vec2& touchedLocation); 

	void moveLayer(Touch* touch);

	std::function<void(Node*, Vec2)> onButtonTouchBegan();
	std::function<void(Node*, Vec2)> onButtonTouchEnded();

private:
	BlockPainter				_blockPainter;

	cocos2d::Vector<Button*>	_buttons;
	std::vector<BlockType>		_buttonTypes;

	BlockType	_selectedButton;

	bool _isScrolling;
};


#endif // __MAP_EDITOR_LAYER_H__