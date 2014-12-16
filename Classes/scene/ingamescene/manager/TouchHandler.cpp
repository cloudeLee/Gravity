

#include <cstddef>

#include "TouchHandler.h"
#include "LayoutManager.h"
#include "BlockManager.h"
#include "BlockMover.h"
#include "board/Board.h"
#include "block/FixedBlock.h"
#include "InGameScene.h"


void TouchHandler::init()
{

}


void TouchHandler::touchBegan(const Point& location)
{
	// get coord 
	Vec2 worldPos = location - _scrolledDistance;
	_oldIndex = LayoutManager::getInstance()->getIndexAt(worldPos);

	_endedCheckRequired = true;
	_touched = true;

	Block* block = Board::getInstance()->getBlockAt(
		static_cast<int>(_oldIndex.x),
		static_cast<int>(_oldIndex.y));

	if (block == nullptr)
	{
		_touchedBlock = nullptr;
		return;
	}

	_touchedBlock = static_cast<FixedBlock*>(block);
}

void TouchHandler::touchMoved(Touch* touch)
{
	// when scrolling the screen not block, move the board
	if (!_touched || _touchedBlock == nullptr)
	{
		moveBoardLayer(touch->getPreviousLocation(), touch->getLocation());
		_endedCheckRequired = false;
		return;
	}

	Point newPoint = LayoutManager::getInstance()->getIndexAt(touch->getLocation() - _scrolledDistance);
	if (Board::getInstance()->getTypeAt(newPoint) != BlockType::NONE)
		return;

	if (_oldIndex != newPoint)
	{
		Point dest = LayoutManager::getInstance()->getCoordAt(newPoint);
		_touchedBlock->setPosition(dest);

		Board::getInstance()->swap(_oldIndex, newPoint);
		_oldIndex = newPoint;

		_endedCheckRequired = false;
	}
	else
	{

	}
}

void TouchHandler::touchEnded(const Point& location)
{
	if (!_endedCheckRequired)
	{
		return;
	}

	Vec2 worldPos = location - _scrolledDistance;
	Point newIndex = LayoutManager::getInstance()->getIndexAt(worldPos);
	BlockType type = Board::getInstance()->getTypeAt(newIndex);
	switch (type)
	{
	case BlockType::HELPER_ARROW_UP:
	case BlockType::HELPER_ARROW_RIGHT:
	case BlockType::HELPER_ARROW_DOWN:
	case BlockType::HELPER_ARROW_LEFT:

		// rotate the button
		BlockManager::getInstance()->getBlockMover()->rotateBy(_touchedBlock);

		// change the value on the board
		if (type == BlockType::HELPER_ARROW_LEFT)
			type = BlockType::HELPER_ARROW_UP;
		else
			type = static_cast<BlockType>(static_cast<int>(type)+1);
		Board::getInstance()->setTypeAt(newIndex, type);

		break;
	}
	

	_touched = false;
	_touchedBlock = nullptr;
}

void TouchHandler::moveBoardLayer(const Vec2& pre, const Vec2& cur)
{
	Vec2 diff = cur - pre;
	_scrolledDistance += diff;
	
	Node* scene = Director::getInstance()->getRunningScene();
	Node* layer = scene->getChildByTag(InGameScene::LAYER_BLOCK, true);

	Vec2 newPos = layer->getPosition() + diff;
	layer->setPosition(newPos);
}
