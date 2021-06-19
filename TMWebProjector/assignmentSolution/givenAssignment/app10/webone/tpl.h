#ifndef ___TPL
#define ___TPL 123
#include "ExceptionPage.tpl.cpp"
#include<tmwp>
using namespace tmwp;
void getExceptionPage_TPL(Request &request,Response &response);
void registerTPLs(TMWebProjector *server)
{
server->onRequest("/ExceptionPage.tpl",getExceptionPage_TPL);
}
#endif