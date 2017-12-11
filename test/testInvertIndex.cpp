#include"../include/InvertIndex.h"
#include"../include/ReadConfigFile.h"
#include<string>
using std::string;
using jjx::InvertIndex;
using jjx::ReadConfigFile;

const string &PAGE_LIB = ReadConfigFile::getInstance()->find("PAGE_LIB:");
const string &OFFSET_LIB = ReadConfigFile::getInstance()->find("OFFSET_LIB:");
const string &INVERTINDEX_LIB = ReadConfigFile::getInstance()->find("INVERTINDEX_LIB:");

int main()
{
	InvertIndex invertIdx;
	invertIdx.loadFile(PAGE_LIB, OFFSET_LIB);
	invertIdx.dumpFile(INVERTINDEX_LIB);
	return 0;
}

