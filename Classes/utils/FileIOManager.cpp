
#include <fstream>
#include <string>     
#include <iostream>

#include "FileIOManager.h"
#include "Resources.h"
#include "Board.h"
#include "BlockManager.h"

#include "UIEditBoxImpl-win32.h"
#include "UIEditBoxImpl.h"

const std::string FILE_PATH = "data/stage/";

void FileIOManager::saveXML(int stageId)
{

}

void FileIOManager::saveBin(int stageId)
{
	std::ofstream stream;

	std::string fileName = FILE_PATH + "stage_" + std::to_string(stageId) + ".bin";
	stream.open(fileName, std::fstream::binary | std::fstream::out);
	
	writeString(stream, CLIENT_VERSION);
	writeString(stream, MAP_EDITOR_VERSION);

	writeInt(stream, stageId);

	writeInt(stream, Board::getInstance()->getRowCount());
	writeInt(stream, Board::getInstance()->getColCount());

	writeBoardItems(stream);

	stream.close();

}

void FileIOManager::loadBin(int inStageId)
{
	std::ifstream stream;

	std::string fileName = FILE_PATH + "stage_" + std::to_string(inStageId) + ".bin";

	stream.open(fileName, std::fstream::binary | std::fstream::in);
	if (!stream.is_open())
	{
		return;
	}
	
	std::string version = readString(stream);
	std::string mapEditorVersion = readString(stream);

	int stageId = readInt(stream);

	int rowCount = readInt(stream);
	int colCount = readInt(stream);

	std::vector<BlockType> boards = readBoardItems(stream, rowCount, colCount);

	stream.close();

	Board::getInstance()->init(stageId, rowCount, colCount, boards);

	BlockManager::getInstance()->clearAllBlocks();
	BlockManager::getInstance()->init(nullptr);
}

void FileIOManager::writeBoardItems(std::ofstream& stream)
{
	int row = Board::getInstance()->getRowCount();
	int col = Board::getInstance()->getColCount();

	for (int i = 0; i < row*col; ++i)
	{
		BlockType type = Board::getInstance()->getTypeAt(i);
		writeInt(stream, static_cast<int>(type));
	}
}

std::vector<BlockType> FileIOManager::readBoardItems(std::ifstream& stream, int row, int col)
{
	std::vector<BlockType> boards;
	BlockType* types = new BlockType[row*col];
	for (int i = 0; i < row*col; ++i)
	{
		int val = readInt(stream);
		boards.push_back(static_cast<BlockType>(val));
	}

	return boards;
}

void FileIOManager::writeString(std::ofstream& stream, const std::string& str)
{
	int length = str.length() + 1;
	stream.write((char*)&length, sizeof(int));
	stream.write(str.c_str(), length);
}

std::string FileIOManager::readString(std::ifstream& stream)
{
	int length;
	stream.read((char*)&length, sizeof(int));

	char* version = new char[length];
	stream.read(version, length);

	return std::string(version);
}

void FileIOManager::writeInt(std::ofstream& stream, int val)
{
	stream.write((char*)&val, sizeof(int));
}

int FileIOManager::readInt(std::ifstream& stream)
{
	int val;
	stream.read((char*)&val, sizeof(int));

	return val;
}
