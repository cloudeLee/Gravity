
#include "block/NormalBlock.h"
#include "BlockMover.h"
#include "board/Board.h"
#include "block/GravityDirection.h"
#include "LayoutManager.h"
#include "NextChecker.h"

const int	CHECK_NEXT_REQUIRED = -1;
const float MOVE_SPEED			= 0.2;
const float ROTATE_DURATION		= 0.2;



void BlockMover::checkMovable(NormalBlock* inBlock)
{
	if (inBlock->getChecked() || inBlock->getIsMoving())
		return;

	//check next position of block by checking the board
	CheckResult result = getNextPosition(inBlock);
	

	//if block cannot be moved
	Point current = inBlock->getBoardPosition();
	if (current == result.next)
	{
		inBlock->setChecked(true);
		return;
	}
	
	//if there's another block on next position, check the block to move
	NormalBlock* nextBlock = static_cast<NormalBlock*>(Board::getInstance()->getBlockAt(result.next));
	if (nextBlock != nullptr)
	{
		checkMovable(nextBlock);	//recursively
		if (Board::getInstance()->getBlockAt(result.next) == nullptr)
		{
			moveTo(inBlock, result.next);
		}
	}
	else
	{
		moveTo(inBlock, result.next);		//if not, move the block 
	}

	inBlock->setChecked(true);
}

void BlockMover::moveTo(NormalBlock* inBlock, Point inNext)
{
	Point dest = LayoutManager::getInstance()->getCoordAt(inNext);
	FiniteTimeAction* actionMove = MoveTo::create(MOVE_SPEED, dest);
	FiniteTimeAction* actionMoveDone = CallFunc::create(CC_CALLBACK_0(BlockMover::moveDone, this, inBlock, inNext));

	inBlock->runAction(CCSequence::create(actionMove, actionMoveDone, nullptr));
	inBlock->setIsMoving(true);

	Board::getInstance()->swap(inBlock->getBoardPosition(), inNext);
	inBlock->setBoardPosition(inNext.x, inNext.y);
}


void BlockMover::moveDone(Node* pSender, Point inNext)
{
	NormalBlock* block = static_cast<NormalBlock*>(pSender);



	block->setIsMoving(false);

// 	static int count = 0;
// 	count++;
// 
// 	if (count / 4 == 4)
// 		CCLOG("BREAK");
}

void BlockMover::rotateBy(Block* block)
{
	FiniteTimeAction* actionMove = RotateBy::create(ROTATE_DURATION, 90.0f);
	FiniteTimeAction* actionMoveDone = CallFunc::create(CC_CALLBACK_0(BlockMover::rotateDone, this, block));

	block->runAction(CCSequence::create(actionMove, actionMoveDone, nullptr));
}

void BlockMover::rotateDone(Node* pSender)
{

}

CheckResult BlockMover::getNextPosition(NormalBlock* inBlock)
{
	cocos2d::Vec2 nextByGravity = getNextByGravity(inBlock);
	BlockType type = Board::getInstance()->getTypeAt(nextByGravity);

	INextChecker* checker = NextPositionCheckerFactory::createChecker(type);
	cocos2d::Vec2 next = checker->getNextPosition(inBlock);
	next = (next.x == -1 && next.y == -1) ? nextByGravity : next;

	delete checker;
	checker = nullptr;

	CheckResult result;
	result.next = next;
	result.type = type;
	
	return result;
}

cocos2d::Point BlockMover::getNextByGravity(NormalBlock* inBlock)
{
	Point old = inBlock->getBoardPosition();
	Point next = old;
	switch (inBlock->getGravityDirection())
	{
	case GravityDirection::UP:
		if (old.x != 0)
			next.x -= 1;
		break;

	case GravityDirection::DOWN:
		if (old.x != Board::getInstance()->getRowCount() - 1)
			next.x += 1;
		break;

	case GravityDirection::LEFT:
		if (old.y != 0)
			next.y -= 1;
		break;

	case GravityDirection::RIGHT:
		if (old.y != Board::getInstance()->getColCount() - 1)
			next.y += 1;
		break;

	case GravityDirection::NONE:
		break;

	default:
		CCASSERT(false, "NOT DEFINED");
		break;
	}

	return next;
}


const cocos2d::Point& BlockMover::getNextByUpArrow(NormalBlock* inBlock)
{
	Point p = inBlock->getBoardPosition();
	switch (inBlock->getGravityDirection())
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

const cocos2d::Point& BlockMover::getNextByDownArrow(NormalBlock* inBlock)
{
	Point p = inBlock->getBoardPosition();
	switch (inBlock->getGravityDirection())
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

const cocos2d::Point& BlockMover::getNextByLeftArrow(NormalBlock* inBlock)
{
	Point p = inBlock->getBoardPosition();
	switch (inBlock->getGravityDirection())
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

const cocos2d::Point& BlockMover::getNextByRightArrow(NormalBlock* inBlock)
{
	Point p = inBlock->getBoardPosition();
	switch (inBlock->getGravityDirection())
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

void BlockMover::changePosition(Block* block, Point pos)
{

}
