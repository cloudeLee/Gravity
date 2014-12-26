
#include "cocos2d.h"
#include "BlockType.h"
#include "NormalBlock.h"
#include "GravityDirection.h"


class INextChecker
{
public:
	~INextChecker(){}
	virtual cocos2d::Vec2 getNextPosition(NormalBlock* block) = 0;
};

class NormalChecker : public INextChecker
{
public:
	~NormalChecker(){}

	virtual cocos2d::Vec2 getNextPosition(NormalBlock* block) override
	{
		return cocos2d::Vec2(-1, -1);
	}
};

class ArrowUpChecker : public INextChecker
{
public:
	~ArrowUpChecker(){}

	virtual cocos2d::Vec2 getNextPosition(NormalBlock* block) override
	{
		Point p = block->getBoardPosition();
		switch (block->getGravityDirection())
		{
		case GravityDirection::UP:
		case GravityDirection::DOWN:
			return p;

		case GravityDirection::LEFT:
		case GravityDirection::RIGHT:
			if (p.x != 0)
				p.x -= 1;

			return p;

		default:
			CCASSERT(false, "Aaa");
			break;
		}
	}
};

class ArrowDownChecker : public INextChecker
{
public:
	~ArrowDownChecker(){}

	virtual cocos2d::Vec2 getNextPosition(NormalBlock* block) override
	{
		Point p = block->getBoardPosition();
		switch (block->getGravityDirection())
		{
		case GravityDirection::UP:
		case GravityDirection::DOWN:
			return p;

		case GravityDirection::LEFT:
		case GravityDirection::RIGHT:
			if (p.x != Board::getInstance()->getRowCount() - 1)
				p.x += 1;

			return p;

		default:
			CCASSERT(false, "NOT DEFINED");
			break;
		}
	}
};

class ArrowLeftChecker : public INextChecker
{
public:
	~ArrowLeftChecker(){}

	virtual cocos2d::Vec2 getNextPosition(NormalBlock* block) override
	{
		Point p = block->getBoardPosition();
		switch (block->getGravityDirection())
		{
		case GravityDirection::UP:
		case GravityDirection::DOWN:
			if (p.y != 0)
				p.y -= 1;

		case GravityDirection::LEFT:
		case GravityDirection::RIGHT:
			return p;

		default:
			CCASSERT(false, "NOT DEFINED");
			break;
		}
	}
};

class ArrowRightChecker : public INextChecker
{
public:
	~ArrowRightChecker(){}

	virtual cocos2d::Vec2 getNextPosition(NormalBlock* block) override
	{
		Point p = block->getBoardPosition();
		switch (block->getGravityDirection())
		{
		case GravityDirection::UP:
		case GravityDirection::DOWN:
			if (p.y != Board::getInstance()->getColCount() - 1)
				p.y += 1;

		case GravityDirection::LEFT:
		case GravityDirection::RIGHT:
			return p;

		default:
			CCASSERT(false, "NOT DEFINED");
			break;
		}
	}
};

class EdgeChecker : public INextChecker
{
public:
	~EdgeChecker(){}

	virtual cocos2d::Vec2 getNextPosition(NormalBlock* block) override
	{
		return block->getBoardPosition();
	}
};

class NextPositionCheckerFactory
{
public:
	static INextChecker* createChecker(const BlockType& type)
	{
		switch (type)
		{
		case BlockType::NONE:
		case BlockType::NORMAL:
			return new NormalChecker;

		case BlockType::HELPER_ARROW_UP:
		case BlockType::HELPER_BROKEN_UP:
			return new ArrowUpChecker;

		case BlockType::HELPER_ARROW_DOWN:
		case BlockType::HELPER_BROKEN_DOWN:
			return new ArrowDownChecker;

		case BlockType::HELPER_ARROW_LEFT:
		case BlockType::HELPER_BROKEN_LEFT:
			return new ArrowLeftChecker;

		case BlockType::HELPER_ARROW_RIGHT:
		case BlockType::HELPER_BROKEN_RIGHT:
			return new ArrowRightChecker;

		case BlockType::EDGE:
			return new EdgeChecker;

		default:
			CCASSERT(false, "NOT DEFINED");
			return nullptr;
		}
	}
};


