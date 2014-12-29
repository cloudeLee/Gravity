
#include "Board.h"

void Board::init(size_t inStageId)
{
	// Read the board information 


	// Get the board's information
	_rowCount = 8 + CEIL_INDEX;
	_colCount = 8;

	// Initiate the 2-Dimension boardarray
	_board.clear();

	for (int i = 0; i < _rowCount * _colCount; ++i) {
		_board.push_back(BoardItem(BlockType::NONE));
	}

	// test
	for (int i = 0; i < _colCount; ++i)
	{
		if (i >= 2 && i <= 5)
			setItemAt(0, i, BlockType::NORMAL);

		if (i >= 2 && i <= 5)
			setItemAt(CEIL_INDEX, i, BlockType::HELPER_ARROW_RIGHT);

		setItemAt(_rowCount - 1, i, BlockType::EDGE);
	}
	for (int i = CEIL_INDEX; i < _rowCount; ++i)
	{
		setItemAt(i, 0, BlockType::EDGE);
		setItemAt(i, _colCount - 1, BlockType::EDGE);
	}

#ifdef SEAFT_DEV
	for (int i = 0; i < _rowCount; ++i)
	{
		char buffer[4];
		std::string str = "";
		for (int j = 0; j < _colCount; ++j)
		{
			itoa(static_cast<int>(getTypeAt(i, j)), buffer, 10);
			str.append(buffer);
			str.push_back(' ');
		}
		CCLOG("%s", str);
		str = "";
	}
#endif
}

void Board::init(size_t stageId, size_t row, size_t col, std::vector<BlockType> boardItems)
{
	_board.clear();

	_rowCount = row;
	_colCount = col;
	
	for (int i = 0; i < _rowCount * _colCount; ++i) {
		_board.push_back(BoardItem(BlockType::NONE));
	}

	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < col; ++j)
		{
			setItemAt(i, j, boardItems[i*col + j]);
		}
	}
}

#if SEAFT_MAP_EDITOR

void Board::createNewBoard(size_t row, size_t col)
{
	_rowCount = row;
	_colCount = col;

	_board.clear();

	for (int i = 0; i < _rowCount * _colCount; ++i) {
		_board.push_back(BoardItem(BlockType::NONE));
	}
}

#endif
