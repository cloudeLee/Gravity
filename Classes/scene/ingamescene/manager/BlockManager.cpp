
#include "BlockManager.h"
#include "BlockPainter.h"
#include "board/Board.h"
#include "block/Block.h"
#include "block/NormalBlock.h"
#include "block/ArrowBlock.h"
#include "block/BlockType.h"
#include "LayoutManager.h"


void BlockManager::init(BlockPainter* painter)
{
	_stopStep = false;

	size_t rowCount = Board::getInstance()->getRowCount();
	size_t colCount = Board::getInstance()->getColCount();

	// Set the main blocks
	for (unsigned int i = 0; i < rowCount; ++i)
	{
		for (unsigned int j = 0; j < colCount; ++j)
		{
			BlockType type = Board::getInstance()->getTypeAt(i, j);

			Sprite* sprite = painter->createSpriteByType(type);

			int width = sprite->getContentSize().width;
			int height = sprite->getContentSize().height;

			sprite->setAnchorPoint(Vec2(0.5, 0.5));

			CCLOG("%d", LayoutManager::getInstance()->getStartingHeight() - i * height);
			CCLOG("%f", height + height * 0.5);

			Point p = Vec2(j * width + width * 2 - width * 0.5, LayoutManager::getInstance()->getStartingHeight() - i * height - height + height * 0.5);
			CCLOG("%f, %f", p.x, p.y);
			sprite->setPosition(Vec2(j * width + width * 2 - sprite->getContentSize().width * 0.5, LayoutManager::getInstance()->getStartingHeight() - i * height - height + sprite->getContentSize().height * 0.5));
						
			Block* newBlock = createBlock(type, sprite, i, j);
			Board::getInstance()->setBlockAt(i, j, newBlock);
		}
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

