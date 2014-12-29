
#ifndef __FILE_IO_MANAGER_H__
#define __FILE_IO_MANAGER_H__

#include "cocos2d.h"
#include "Singleton.h"
#include "BlockType.h"

USING_NS_CC;


class FileIOManager : public Singleton<FileIOManager>
{
	SINGLETON_INIT(FileIOManager)

public:
	void saveXML(int stageId);
	void saveBin(int stageId);

	void loadBin(int stageId);

private:
	void writeBoardItems(std::ofstream& stream);
	std::vector<BlockType> readBoardItems(std::ifstream& stream, int row, int col);

	void writeString(std::ofstream& stream, const std::string& str);
	std::string readString(std::ifstream& stream);

	void writeInt(std::ofstream& stream, int val);
	int readInt(std::ifstream& stream);
};

#endif