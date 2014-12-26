
#ifndef __BLOCK_PAINTER_H__
#define __BLOCK_PAINTER_H__

#include "cocos2d.h"

USING_NS_CC;

enum class BlockType;

class BlockPainter
{
public:
	BlockPainter()
		:_painter(nullptr){}

	virtual ~BlockPainter();

	Node* initPainter();

	/**
	 * create sprite having certain type of param.
	 * If second parameter "draw" is "true", new sprite will be drawn automatically.
	 */
	Sprite* createSpriteByType(const BlockType& type, bool draw = true);

	/** property */
	inline Node* getPainter() 
	{
		return _painter;
	}

	std::string getSpriteFileName(const BlockType& type);

	inline void disposeAll()
	{
		_painter->removeAllChildrenWithCleanup(true);
	}

private:
	SpriteBatchNode* _painter;

};

#endif  //__BLOCK_MANAGER_H__