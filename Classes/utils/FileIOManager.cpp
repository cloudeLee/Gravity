
#include "FileIOManager.h"
#include "Resources.h"
#include <fstream>
#include <string>     
#include <iostream>

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
	
	stream.close();

}

void FileIOManager::loadBin(int stageId)
{
	std::ifstream stream;

	std::string fileName = FILE_PATH + "stage_" + std::to_string(stageId) + ".bin";

	stream.open(fileName, std::fstream::binary | std::fstream::in);
	if (!stream.is_open())
	{
		return;
	}
	
	std::string version = readString(stream);
	std::string mapEditorVersion = readString(stream);

	stream.close();
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
