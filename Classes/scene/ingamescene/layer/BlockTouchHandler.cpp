
#include "BlockTouchHandler.h"
#include "manager/LayoutManager.h"
#include "block/Block.h"
#include "block/FixedBlock.h"
#include "board/Board.h"
#include "manager/TouchManager.h"
#include "manager/BlockManager.h"

void BlockTouchHandler::onTouchBeganBlockLayer(const Vec2& pos)
{
	_oldIndex = LayoutManager::getInstance()->getIndexAt(pos);

	_touched = true;
	_endedCheckRequired = true;

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

void BlockTouchHandler::onTouchMovedBlockLayer(Touch* touch, Node* layer)
{
	// when scrolling the screen not picking the block, move the board
	if (!_touched || _touchedBlock == nullptr)
	{
		Vec2 diff = TouchManager::getInstance()->touchMoved(touch);
		Vec2 newPos = layer->getPosition() + diff;
		layer->setPosition(newPos);

		_endedCheckRequired = false;
		return;
	}

	Point newPoint = LayoutManager::getInstance()->getIndexAt(touch->getLocation() - TouchManager::getInstance()->getScrolledDistance());

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

void BlockTouchHandler::onTouchEndedBlockLayer(const Vec2& pos)
{
	if (!_endedCheckRequired)
	{
		return;
	}

	Point newIndex = LayoutManager::getInstance()->getIndexAt(pos);
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
