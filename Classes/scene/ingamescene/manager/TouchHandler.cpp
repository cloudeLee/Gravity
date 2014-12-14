
#include "TouchHandler.h"
#include "LayoutManager.h"
#include "BlockManager.h"
#include "BlockMover.h"
#include "board/Board.h"
#include "block/FixedBlock.h"

void TouchHandler::touchBegan(const Point& location)
{
	_oldIndex = LayoutManager::getInstance()->getIndexAt(location);
	CCLOG("%f %f", _oldIndex.x, _oldIndex.y);

	size_t rowCount = Board::getInstance()->getRowCount();
	size_t colCount = Board::getInstance()->getColCount();

	if ((_oldIndex.x < 0 && _oldIndex.x >= rowCount) ||
		(_oldIndex.y < 0 && _oldIndex.y >= colCount))
	{
		_touched = false;
		return;
	}

	_moved = false;
	_touched = true;
	_oldLocation = location;

	_canMove = LayoutManager::getInstance()->getDefaultBlockSize() * 0.5;

	Block* block = Board::getInstance()->getBlockAt(
		static_cast<int>(_oldIndex.x),
		static_cast<int>(_oldIndex.y));

	_touchedBlock = static_cast<FixedBlock*>(block);
}

void TouchHandler::touchMoved(const Point& location)
{
	if (!_touched || _touchedBlock == nullptr)
		return;
			
	Point newPoint = LayoutManager::getInstance()->getIndexAt(location);
	if (_oldIndex != newPoint)
	{
		Point dest = LayoutManager::getInstance()->getCoordAt(newPoint);
		_touchedBlock->setPosition(dest);

		Board::getInstance()->swap(_oldIndex, newPoint);
		_oldIndex = newPoint;

		_moved = true;
	}
	else
	{

	}
}

void TouchHandler::touchEnded(const Point& location)
{
	if (_moved)
	{
		return;
	}

	Point newIndex = LayoutManager::getInstance()->getIndexAt(location);
	if (_oldIndex == newIndex)
	{
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
	}
	else
	{
	}

	_touched = false;
}
