#include"../include/Mylog.h"
#include"../include/ReadConfigFile.h"
#include"../include/int2str.h"
#include<stdlib.h>
#include<iostream>
using std::cout;
using std::endl;
using jjx::ReadConfigFile;

namespace jjx
{
//读取配置文件
const string LOG_FILENAME = ReadConfigFile::getInstance()->find("LOG_FILENAME:");
const int LOG_ISCOUT = str2int(ReadConfigFile::getInstance()->find("LOG_ISCOUT:"));
const int LOG_ISROLLINGFILE = str2int(ReadConfigFile::getInstance()->find("LOG_ISROLLINGFILE:"));
const int LOG_ROLLINGFILESIZE = str2int(ReadConfigFile::getInstance()->find("LOG_ROLLINGFILESIZE:"));
const int LOG_ROLLINGFILENUM = str2int(ReadConfigFile::getInstance()->find("LOG_ROLLINGFILENUM:"));

Mylog * Mylog::_pMylog=NULL;
Mylog::Recycle Mylog::rec;
Mylog * Mylog::getInstance()
{
	if(NULL==_pMylog)_pMylog=new Mylog(LOG_FILENAME.c_str());
	return _pMylog;
}
Mylog::Mylog(const char *filename)
: _root(Category::getRoot())
, _filename(filename)
{
	if(LOG_ISCOUT)
	{
		OstreamAppender *fAppender=new OstreamAppender("fAppender",&std::cout);
		PatternLayout *pLayout=new PatternLayout();
		pLayout->setConversionPattern("%d: [%p]: %m%n");
		fAppender->setLayout(pLayout);
		_root.addAppender(fAppender);
		_root.setPriority(Priority::DEBUG);
	}
	else if(LOG_ISROLLINGFILE)
	{
		RollingFileAppender *fAppender=new RollingFileAppender
			("fAppender",
		 	_filename, 
			LOG_ROLLINGFILESIZE,
			LOG_ROLLINGFILENUM);
		PatternLayout *pLayout=new PatternLayout();
		pLayout->setConversionPattern("%d: [%p]: %m%n");
		fAppender->setLayout(pLayout);
		_root.addAppender(fAppender);
		_root.setPriority(Priority::DEBUG);
	}else{
		FileAppender *fAppender=new FileAppender("fAppender",_filename);
		PatternLayout *pLayout=new PatternLayout();
		pLayout->setConversionPattern("%d: [%p]: %m%n");
		fAppender->setLayout(pLayout);
		_root.addAppender(fAppender);
		_root.setPriority(Priority::DEBUG);
	}
};
}//end of namespace jjx
