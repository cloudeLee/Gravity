
#include "BlockPainter.h"
#include "block/BlockType.h"
#include "utils/Resources.h"


BlockPainter::~BlockPainter()
{
	_painter->removeAllChildrenWithCleanup(true);	
}

Node* BlockPainter::initPainter()
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("res/blocks.plist");

	_painter = SpriteBatchNode::create("res/blocks.png", 50);
	_painter->setPosition(Vec2(0, 0));

	return _painter;
}

Sprite* BlockPainter::createSpriteByType(const BlockType& type, bool draw)
{
	Sprite* sprite = Sprite::createWithSpriteFrameName(getSpriteFileName(type));

	if (draw)
	{
		_painter->addChild(sprite, type == BlockType::NONE ? 0 : 1);
	}

	return sprite;
}

std::string BlockPainter::getSpriteFileName(const BlockType& type)
{
	switch (type)
	{
		case BlockType::NONE:
			return FILE_NAME_NONE;

		case BlockType::NORMAL:
			return FILE_NAME_BLOCK_NORMAL;

		case BlockType::HELPER_BOX:
			return FILE_NAME_HELPER_BOX;

		case BlockType::HELPER_ARROW_RIGHT:
			return FILE_NAME_HELPER_ARROW_RIGHT;

		case BlockType::EDGE:
			return FILE_NAME_EDGE;

		default:
			return "";
	}
	
}
