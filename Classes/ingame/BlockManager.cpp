
#include "BlockManager.h"
#include "BlockPainter.h"
#include "Board.h"
#include "Block.h"
#include "NormalBlock.h"
#include "ArrowBlock.h"
#include "BlockType.h"
#include "LayoutManager.h"


void BlockManager::init(BlockPainter* painter)
{
	if (painter != nullptr)
		_blockPainter = painter;

	_stopStep = false;

	size_t rowCount = Board::getInstance()->getRowCount();
	size_t colCount = Board::getInstance()->getColCount();

	// Set the main blocks
	for (unsigned int i = 0; i < rowCount; ++i)
	{
		for (unsigned int j = 0; j < colCount; ++j)
		{
			BlockType type = Board::getInstance()->getTypeAt(i, j);

			initBlockAt(type, i, j);
		}
	}
}

void BlockManager::initBlockAt(const BlockType& type, int x, int y)
{
	Sprite* sprite = _blockPainter->createSpriteByType(type);

	int width = sprite->getContentSize().width;
	int height = sprite->getContentSize().height;

	sprite->setPosition(Vec2(y * width + width * 2 - sprite->getContentSize().width * 0.5, LayoutManager::getInstance()->getStartingHeight() - x * height - height + sprite->getContentSize().height * 0.5));

	Block* newBlock = createBlock(type, sprite, x, y);
	if (newBlock)
	{
		newBlock->retain();
		Board::getInstance()->setBlockAt(x, y, newBlock);

#if SEAFT_MAP_EDITOR
		_allBlocks.push_back(newBlock);
#endif

	}
}

void BlockManager::step()
{
	if (_stopStep)
		return;

	int size = _blocks.size();
	int checked = 0;
	for (int i = 0; i < size; ++i)
	{
		_blockMover.checkMovable(_blocks.at(i));
		if (_blocks.at(i)->getChecked())
		{
			++checked;
		}
	}

	if (checked == size)
	{
		for (int i = 0; i < size; ++i)
		{
			_blocks.at(i)->setChecked(false);
		}
	}
}

Block* BlockManager::createBlock(const BlockType& type, Sprite* sprite, int x, int y)
{
	if (type == BlockType::NORMAL)
	{
		NormalBlock* normalBlock = static_cast<NormalBlock*>(sprite);
		normalBlock->initBlock(x, y, GravityDirection::DOWN);
		_blocks.push_back(normalBlock);
		return normalBlock;
	}
	else if (BlockType::HELPER_ARROW_START <= type && type <= BlockType::HELPER_ARROW_END)
	{
		ArrowBlock* arrowBlock = static_cast<ArrowBlock*>(sprite);
		arrowBlock->initBlock(x, y, static_cast<EArrowDirection>(type));
		return arrowBlock;
	}
	else
	{
		return nullptr;
	}
}

void BlockManager::setGravityDirection(const GravityDirection& direction)
{
	int cnt = _blocks.size();
	for (int i = 0; i < cnt; ++i)
	{
		_blocks[i]->setGravityDirection(direction);
	}
}

void BlockManager::turnGravityOn(bool on)
{
	int cnt = _blocks.size();
	for (int i = 0; i < cnt; ++i)
	{
		_blocks[i]->setIsMoving(!on);
	}
}

void BlockManager::stopCheckingStep(bool stop)
{
	_stopStep = stop;
}

#if SEAFT_MAP_EDITOR

void BlockManager::clearAllBlocks()
{
	_allBlocks.clear();
	_blockPainter->disposeAll();	
}

#endif