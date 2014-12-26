
#include "LayoutManager.h"
#include "BlockType.h"
#include "Board.h"


const int BLOCK_SIZE = 108;

void LayoutManager::init()
{
	auto screenSize = Director::getInstance()->getOpenGLView()->getDesignResolutionSize();
	_defaultBlockSize = BLOCK_SIZE;

	size_t rowCount = Board::getInstance()->getRowCount();
	_startingBlockHeight = screenSize.height - (screenSize.height * 0.5 - (Board::CEIL_INDEX * _defaultBlockSize) - (rowCount - Board::CEIL_INDEX) * 0.5 * _defaultBlockSize);

	CCLOG("[LayoutManager] Block Starting point is %d", _startingBlockHeight);
}
