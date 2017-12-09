#include"../include/TaskFunc.h"
#include"../include/ReadConfigFile.h"
#include"../include/int2str.h"
#include"../include/Socket.h"
#include"../include/Acceptor.h"
#include"../include/ReactorThreadpool.h"
#include"../include/CreateEnDict.h"
#include"../include/CreateCnDict.h"
#include"../include/Corrector.h"
#include"../include/Cache.h"
#include"../include/CacheManager.h"
using namespace jjx;

//读取配置文件信息
const string IP = ReadConfigFile::getInstance()->find("IP:");
const int PORT = jjx::str2int(ReadConfigFile::getInstance()->find("PORT:"));
const int PTH_NUM = jjx::str2int(ReadConfigFile::getInstance()->find("PTH_NUM:"));
const int PTH_TASKSIZE = jjx::str2int(ReadConfigFile::getInstance()->find("PTH_TASKSIZE:"));
const string LIB_EN = ReadConfigFile::getInstance()->find("LIB_EN:");
const string DICT_EN = ReadConfigFile::getInstance()->find("DICT_EN:");
const string LIB_CN = ReadConfigFile::getInstance()->find("LIB_CN:");
const string DICT_CN = ReadConfigFile::getInstance()->find("DICT_CN:");
const string CACHE_FILE = ReadConfigFile::getInstance()->find("CACHE_FILE:");

int main()
{
	Socket soc(IP, PORT);
	soc.reuseAddr();//重用地址
	soc.bind();
	soc.listen();
	Acceptor acc(soc);
	ReactorThreadpool reaThrPool(acc, PTH_NUM, PTH_TASKSIZE);

	CreateEnDict creEnDict;
	creEnDict.loadFile(LIB_EN, ".txt");//创建英文词典
	creEnDict.dumpFile(DICT_EN);//输出英文词典到文件

	CreateCnDict creCnDict;
	creCnDict.loadFile(LIB_CN, ".txt");//创建中文词典
	creCnDict.dumpFile(DICT_CN);//输出中文词典到文件

	Corrector corr;
	corr.loadDictionary(DICT_EN);//加载英文词典
	corr.loadDictionary(DICT_CN);//加载中文词典
	corr.createIndex();//建立索引

	CacheManager cachManag;
	cachManag.initCache(CACHE_FILE, PTH_NUM);//初始化缓存

	reaThrPool.setHandleNewCon(HandleNewCon);
	reaThrPool.setBusinessRecvData(BusinessRecvData);
	reaThrPool.setCompute(std::bind(Compute,
					&corr,//将词典地址绑定给计算线程函数
					&cachManag,//将缓存地址绑定给计算线程函数
				        std::placeholders::_1,
					std::placeholders::_2));
	reaThrPool.setBusinessSendData(BusinessSendData);
	reaThrPool.setWriteCacheToFile(std::bind(WriteCacheToFile, &cachManag, std::placeholders::_1));
	reaThrPool.setDisConnect(DisConnect);
	reaThrPool.start();
	return 0;
}
