
#include "LayoutManager.h"
#include "manager/BlockPainter.h"
#include "block/BlockType.h"
#include "board/Board.h"


void LayoutManager::init(BlockPainter* painter)
{
	auto screenSize = Director::getInstance()->getOpenGLView()->getDesignResolutionSize();
	_defaultBlockSize = painter->createSpriteByType(BlockType::NONE, false)->getContentSize().height;

	size_t rowCount = Board::getInstance()->getRowCount();
	_startingBlockHeight = screenSize.height - (screenSize.height * 0.5 - (Board::CEIL_INDEX * _defaultBlockSize) - (rowCount - Board::CEIL_INDEX) * 0.5 * _defaultBlockSize);

	CCLOG("[LayoutManager] Block Starting point is %d", _startingBlockHeight);
}
