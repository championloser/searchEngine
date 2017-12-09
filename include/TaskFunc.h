#ifndef __TASKFUNC_H__
#define __TASKFUNC_H__

#include"Connection.h"
#include"ReactorThreadpool.h"
#include<memory>
using std::shared_ptr;
namespace jjx
{
int HandleNewCon(shared_ptr<Connection> pCon);

int BusinessRecvData(void *p, shared_ptr<Connection> pCon);

int Compute(void *pCorrector, void * pCachManag, void *pReaThr, shared_ptr<Task> pTask) ;

int BusinessSendData(void *p);

int WriteCacheToFile(void *pCachManag, void *p);

int DisConnect(shared_ptr<Connection> pCon);
}//end of namespace jjx
#endif
