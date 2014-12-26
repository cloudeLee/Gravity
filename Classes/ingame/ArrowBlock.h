

#ifndef __ARROW_BLOCK_H__
#define __ARROW_BLOCK_H__

#include "FixedBlock.h"

enum class EArrowDirection : unsigned char
{
	UP = static_cast<unsigned char>(BlockType::HELPER_ARROW_UP),
	DOWN = static_cast<unsigned char>(BlockType::HELPER_ARROW_DOWN),
	LEFT = static_cast<unsigned char>(BlockType::HELPER_ARROW_LEFT),
	RIGHT = static_cast<unsigned char>(BlockType::HELPER_ARROW_RIGHT)
};

class ArrowBlock : public FixedBlock
{
public:

	void initBlock(int x, int y, const EArrowDirection& direction)
	{
		_x = x;
		_y = y;
		_arrowDirection = direction;
	}

	/** properties */

	const EArrowDirection& getArrowDirection()
	{
		return _arrowDirection;
	}

	void setArrowDirection(EArrowDirection arrowDirection)
	{
		_arrowDirection = arrowDirection;
	}

private:
	EArrowDirection _arrowDirection;

};

#endif