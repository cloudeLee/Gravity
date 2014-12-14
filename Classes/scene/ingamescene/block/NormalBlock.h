
#ifndef __GRAVITY_BLOCK_H__
#define __GRAVITY_BLOCK_H__

#include "Block.h"

class NormalBlock : public Block
{
public:

	inline void initBlock(int x, int y, const GravityDirection& direction)
	{
		_x = x;
		_y = y;
		_direction = direction;
		_isMoving = true;
		_isChecked = false;
	}


	/** properties */

	inline const GravityDirection& getGravityDirection()
	{
		return _direction;
	}

	inline void setGravityDirection(const GravityDirection& inDirection)
	{
		_direction = inDirection;
	}
	
	inline bool getChecked()
	{
		return _isChecked;
	}

	inline void setChecked(bool inChecked)
	{
		_isChecked = inChecked;
	}

	inline bool getIsMoving()
	{
		return _isMoving;
	}

	inline void setIsMoving(bool inIsMoving)
	{
		_isMoving = inIsMoving;
	}

protected:
	GravityDirection _direction;
	bool _isMoving;
	bool _isChecked;

};

#endif