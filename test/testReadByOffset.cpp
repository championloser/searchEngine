#include"../include/RssParse.h"
#include"../include/ReadConfigFile.h"
#include<string.h>
#include<fstream>
#include<iostream>
using std::cout;
using std::endl;
using std::ifstream;
using jjx::ReadConfigFile;

const string PAGE_LIB = ReadConfigFile::getInstance()->find("PAGE_LIB:");
const string OFFSET_LIB = ReadConfigFile::getInstance()->find("OFFSET_LIB:");

int main()
{
	int docid, begin, length;
	ifstream ifs;
	ifs.open(OFFSET_LIB);
	ifs>>docid>>begin>>length;
	ifs.close();

	ifs.open(PAGE_LIB);
	ifs.seekg(begin);
	char buf[30000];
	memset(buf, 0, sizeof(buf));
	ifs.read(buf, length);
	ifs.close();
	cout<<buf<<endl;
	return 0;
}
