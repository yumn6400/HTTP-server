#include<iostream>
#include<stdlib.h>
#include<tuple>
#include<thread>
#include<string.h>
#include<windows.h>
#include<map>
using namespace std;
string decode(string str)
{
int i;
for(i=0;str[i]!='\0';i++)
{
if(str[i]=='+')
{
str.replace(i,1," ");
}
else if(str[i]=='%')
{
if(strncmp(str.c_str()+(i+1),"20",2)==0)str.replace(i,3," ");
else if(strncmp(str.c_str()+(i+1),"21",2)==0)str.replace(i,3,"!");
else if(strncmp(str.c_str()+(i+1),"22",2)==0)str.replace(i,3,"/");
else if(strncmp(str.c_str()+(i+1),"23",2)==0)str.replace(i,3,"#");
else if(strncmp(str.c_str()+(i+1),"24",2)==0)str.replace(i,3,"$");
else if(strncmp(str.c_str()+(i+1),"25",2)==0)str.replace(i,3,"%");
else if(strncmp(str.c_str()+(i+1),"26",2)==0)str.replace(i,3,"&");
else if(strncmp(str.c_str()+(i+1),"27",2)==0)str.replace(i,3,"'");
else if(strncmp(str.c_str()+(i+1),"28",2)==0)str.replace(i,3,"(");
else if(strncmp(str.c_str()+(i+1),"29",2)==0)str.replace(i,3,")");
else if(strncmp(str.c_str()+(i+1),"2A",2)==0)str.replace(i,3,"*");
else if(strncmp(str.c_str()+(i+1),"2B",2)==0)str.replace(i,3,"+");
else if(strncmp(str.c_str()+(i+1),"2C",2)==0)str.replace(i,3,",");
else if(strncmp(str.c_str()+(i+1),"2D",2)==0)str.replace(i,3,"-");
else if(strncmp(str.c_str()+(i+1),"2E",2)==0)str.replace(i,3,".");
else if(strncmp(str.c_str()+(i+1),"2F",2)==0)str.replace(i,3,"/");
else if(strncmp(str.c_str()+(i+1),"3A",2)==0)str.replace(i,3,":");
else if(strncmp(str.c_str()+(i+1),"3B",2)==0)str.replace(i,3,";");
else if(strncmp(str.c_str()+(i+1),"3C",2)==0)str.replace(i,3,"<");
else if(strncmp(str.c_str()+(i+1),"3D",2)==0)str.replace(i,3,"=");
else if(strncmp(str.c_str()+(i+1),"3E",2)==0)str.replace(i,3,">");
else if(strncmp(str.c_str()+(i+1),"3F",2)==0)str.replace(i,3,"?");
else if(strncmp(str.c_str()+(i+1),"40",2)==0)str.replace(i,3,"@");
else if(strncmp(str.c_str()+(i+1),"5B",2)==0)str.replace(i,3,"[");
else if(strncmp(str.c_str()+(i+1),"5C",2)==0)str.replace(i,3,"\\");
else if(strncmp(str.c_str()+(i+1),"5D",2)==0)str.replace(i,3,"]");
else if(strncmp(str.c_str()+(i+1),"5E",2)==0)str.replace(i,3,"^");
else if(strncmp(str.c_str()+(i+1),"5F",2)==0)str.replace(i,3,"_");
else if(strncmp(str.c_str()+(i+1),"60",2)==0)str.replace(i,3,"`");
else if(strncmp(str.c_str()+(i+1),"7B",2)==0)str.replace(i,3,"{");
else if(strncmp(str.c_str()+(i+1),"7C",2)==0)str.replace(i,3,"|");
else if(strncmp(str.c_str()+(i+1),"7D",2)==0)str.replace(i,3,"}");
else if(strncmp(str.c_str()+(i+1),"7E",2)==0)str.replace(i,3,"~");
else if(strncmp(str.c_str()+(i+1),"0D%0A",5)==0)str.replace(i,6,"\n");
else if(strncmp(str.c_str()+(i+1),"0D",2)==0)str.replace(i,3,"\n");
else if(strncmp(str.c_str()+(i+1),"0A",2)==0)str.replace(i,3,"\n");
}
}
return str;
}
class Request
{
public:
char *method;
char *resource;
char *mimeType;
char isClientSideTechnologyResource;
int dataCount;
char **data;
string forwardTo;
map<string,string> keyValues;

void setKeyValue(string k,string v)
{
keyValues.insert(pair<string,string>(k,v));
}
string getValue(string k)
{
map<string,string>::iterator iter;
iter=keyValues.find(k);
if(iter==keyValues.end())return string("");
return decode(iter->second);
}
string get(string name)
{
string val;
int e,i;
for(i=0;i<this->dataCount;i++)
{
for(e=0;data[i][e]!='\0'&&data[i][e]!='=';e++);
if(data[i][e]!='=')continue;
if(strncmp(data[i],name.c_str(),e)==0)break;
}
if(i==this->dataCount)
{
val="";
}
else
{
val=string(data[i]+(e+1));
}
return val;
}
void forward(string forwardTo)
{
this->forwardTo=forwardTo;
}
};
class Response
{
private:
char *contentType;
int clientSocketDescriptor;
bool isClosed;
bool headerCreated;
bool isContentSend;
void createHeader()
{
char header[501];                             
sprintf(header,"HTTP/1.1 200 OK\nContent-Type:%s\n\n",contentType);
send(clientSocketDescriptor,header,strlen(header)+1,0);
this->headerCreated=true;
}
public:
Response(int clientSocketDescriptor)
{
this->clientSocketDescriptor=clientSocketDescriptor;
this->isClosed=false;
this->headerCreated=false;
this->isContentSend=false;
}
void close()
{
if(this->isClosed)return;
closesocket(this->clientSocketDescriptor);
this->isClosed=true;
}
void setContentType(string contentType)
{
this->contentType=(char *)malloc((sizeof(char)*strlen(contentType.c_str()))+1);
strcpy(this->contentType,contentType.c_str());
}
void Send(string content)
{
if(this->isContentSend)return;
if(content.c_str()==NULL)return;
int len=content.size();
if(len==0)return;
if(!(this->headerCreated))createHeader();
int rc;
int i=0;
while(i<len)
{
rc=len-i;
if(rc>1024)rc=1024;
send(clientSocketDescriptor,(content.c_str())+i,rc,0);
i=i+rc;
}
this->isContentSend=true;
}
};
class Error
{
string message="";
public:
Error(string message)
{
this->message=message;
}
bool hasError()
{
if(strlen(message.c_str())==0)return false;
else return true;
}
string getError()
{
if(strlen(message.c_str())==0)return string("");
return message;
}
};
string getExtension(char *resource)
{
int i;
char arr[11];
for(i=0;resource[i]!='\0'&&resource[i]!='.';i++);
if(resource[i]=='\0')return string("");
return string(resource+(i+1));
}
int extensionEquals(const char *left,const char *right)
{
char a,b; 
while(*left&&*right)
{
a=*left;
b=*right;
if(a!=b)return 0;
left++;
right++;
}
return *left==*right;
}
char *isMimeType(char *resource)
{
char *mimeType;
mimeType=NULL;
int i,lastIndexOfDot;
for(i=0;resource[i]!='\0'&&resource[i]!='.';i++);
lastIndexOfDot=i;
if(resource[i]=='\0')return mimeType;
if(extensionEquals(resource+lastIndexOfDot+1,"html"))
{
mimeType=(char *)malloc(sizeof(char)*10);
strcpy(mimeType,"text/html");
}
if(extensionEquals(resource+lastIndexOfDot+1,"css"))
{
mimeType=(char *)malloc(sizeof(char)*9);
strcpy(mimeType,"text/css");
}
if(extensionEquals(resource+lastIndexOfDot+1,"js"))
{
mimeType=(char *)malloc(sizeof(char)*16);
strcpy(mimeType,"text/javascript");
}
if(extensionEquals(resource+lastIndexOfDot+1,"jpg"))
{
mimeType=(char *)malloc(sizeof(char)*11);
strcpy(mimeType,"image/jpeg");
}
if(extensionEquals(resource+lastIndexOfDot+1,"jpeg"))
{
mimeType=(char *)malloc(sizeof(char)*11);
strcpy(mimeType,"image/jpeg");
}
if(extensionEquals(resource+lastIndexOfDot+1,"png"))
{
mimeType=(char *)malloc(sizeof(char)*10);
strcpy(mimeType,"image/png");
}
return mimeType;
}
char isClientSideResource(char *resource)
{
int i;
for(i=0;resource[i]!='\0'&&resource[i]!='.';i++);
if(resource[i]=='\0')return 'N';
else if(extensionEquals((getExtension(resource).c_str()),"tpl"))return 'N';
return 'Y';
}
Request *parseRequest(char *bytes)
{
char method[11];
char resource[1001];
int i,j;
for(i=0;bytes[i]!=' '&&bytes[i]!='\0';i++)method[i]=bytes[i];
method[i]='\0';
i+=2;
char **data=NULL;
int dataCount=0;
if(strcmp(method,"GET")==0)
{
//whatever?eeijieh+edi3wo&dijihid&didjgidj&jihffi
for(j=0;bytes[i]!=' ';j++,i++)
{
if(bytes[i]=='?')break;
resource[j]=bytes[i];
}
resource[j]='\0';
if(bytes[i]=='?')
{
i++;
int si=i;
dataCount=0;
while(bytes[i]!=' ')
{
if(bytes[i]=='&')dataCount++;
i++;
}
dataCount++;
data=(char **)malloc(sizeof(char *)*dataCount);
int *pc=(int *)malloc(sizeof(int)*dataCount);
i=si;
int j=0;
while(bytes[i]!=' ')
{
if(bytes[i]=='&')
{
pc[j]=i;
j++;
}
i++;
}
pc[j]=i;
i=si;
j=0;
int howManyToPick;
while(j<dataCount)
{
howManyToPick=pc[j]-i;
data[j]=(char *)malloc(sizeof(char)*(howManyToPick+1));
strncpy(data[j],bytes+i,howManyToPick);
data[j][howManyToPick]='\0';
i=pc[j]+1;
j++;
}
}
}
printf("Request arrived for %s\n",resource);
Request *request=new Request;
request->dataCount=dataCount;
request->data=data;
request->method=(char *)malloc((sizeof(char)*strlen(method))+1);
strcpy(request->method,method);
if(resource[0]=='\0')
{
request->resource=NULL;
request->mimeType=NULL;
request->isClientSideTechnologyResource='Y';
}
else
{
request->resource=(char *)malloc((sizeof(char)*strlen(resource))+1);
strcpy(request->resource,resource);
request->isClientSideTechnologyResource=isClientSideResource(request->resource);
request->mimeType=isMimeType(request->resource);
}
return request;
}
void seperateThread(int clientSocketDescriptor,string folderPath,map<string,void(*)(Request &,Response &)> requestMappings )
{
FILE *f;
int len,data,i,rc,success;
char requestBuffer[8193];
char responseBuffer[1025];
char header[501];
success=recv(clientSocketDescriptor,requestBuffer,sizeof(requestBuffer),0);
printf("request arrived\n");

Request *request=parseRequest(requestBuffer);
while(1)
{
if(request->isClientSideTechnologyResource=='Y')
{
if(request->resource==NULL)
{
printf("open index.html\n");
folderPath=folderPath+"/index.html";
f=fopen(folderPath.c_str(),"rb");
if(f==NULL)
{
folderPath=folderPath+"/index.htm";
f=fopen(folderPath.c_str(),"rb");
if(f!=NULL)printf("Sending index.htm\n");
}
if(f==NULL)
{
char tmp[501];
strcpy(tmp,"<!DOCTYPE html><html lang='en'><head><title>Whatever</title></head><body><h1>Resource /not found</h1></body></html>");
len=strlen(tmp);
sprintf(header,"HTTP/1.1 200 OK\nContent-Type:text/html\nContent-Length:%d\n\n",len);
send(clientSocketDescriptor,header,strlen(header)+1,0);
strcpy(responseBuffer,"<!DOCTYPE html><html lang='en'><head><title>Whatever</title></head><body><h1>Resource /not found</h1></body></html>");
send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer)+1,0);
closesocket(clientSocketDescriptor);
break;
}
else
{
fseek(f,0,2);
len=ftell(f);
fseek(f,0,0);
sprintf(header,"HTTP/1.1 200 OK\nContent-Type:text/html\nContent-Length:%d\nConnection:close\n\n",len);
send(clientSocketDescriptor,header,strlen(header),0);
i=0;
while(i<len)
{
rc=len-i;
if(rc>1024)rc=1024;
fread(&responseBuffer,rc,1,f);
send(clientSocketDescriptor,responseBuffer,rc,0);
i=i+rc;
}
fclose(f);
closesocket(clientSocketDescriptor);
break;
}
}
else
{
folderPath=folderPath+"/"+request->resource;
f=fopen(folderPath.c_str(),"rb");
if(f==NULL)
{
char tmp[501];
sprintf(tmp,"<!DOCTYPE html><html lang='en'><head><title>Whatever</title></head><body><h1>Resource /%s not found</h1></body></html>",request->resource);
len=strlen(tmp);
sprintf(header,"HTTP/1.1 200 OK\nContent-Type:text/html\nContent-Length:%d\n\n",len);
send(clientSocketDescriptor,header,strlen(header)+1,0);
sprintf(responseBuffer,"<!DOCTYPE html><html lang='en'><head><title>Whatever</title></head><body><h1>Resource /%s not found</h1></body></html>",request->resource);
send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer)+1,0);
closesocket(clientSocketDescriptor);
break;
}
else
{
fseek(f,0,2);
len=ftell(f);
fseek(f,0,0);
sprintf(header,"HTTP/1.1 200 OK\nContent-Type:%s\nContent-Length:%d\nConnection:close\n\n",request->mimeType,len);
send(clientSocketDescriptor,header,strlen(header),0);
i=0;
while(i<len)
{
rc=len-i;
if(rc>1024)rc=1024;
fread(&responseBuffer,rc,1,f);
send(clientSocketDescriptor,responseBuffer,rc,0);
i=i+rc;
}
fclose(f);
closesocket(clientSocketDescriptor);
break;
}
}
}
else
{
map<string,void(*)(Request &,Response &)>::iterator iter;
iter=requestMappings.find(string("/")+string(request->resource));
if(iter==requestMappings.end())
{
char tmp[501];
sprintf(tmp,"<!DOCTYPE html><html lang='en'><head><title>Whatever</title></head><body><h1>Resource /%s not found</h1></body></html>",request->resource);
len=strlen(tmp);
sprintf(header,"HTTP/1.1 200 OK\nContent-Type:text/html\nContent-Length:%d\n\n",len);
send(clientSocketDescriptor,header,strlen(header)+1,0);
sprintf(responseBuffer,"<!DOCTYPE html><html lang='en'><head><title>Whatever</title></head><body><h1>Resource /%s not found</h1></body></html>",request->resource);
send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer)+1,0);
break;
}
else
{
Response response(clientSocketDescriptor);
iter->second(*request,response);
if(request->forwardTo.length()>0)
{
free(request->resource);
request->resource=(char *)malloc((sizeof(char)*request->forwardTo.length())+1);
strcpy(request->resource,request->forwardTo.c_str());
request->isClientSideTechnologyResource=isClientSideResource(request->resource);
request->mimeType=isMimeType(request->resource);
request->forwardTo.resize(0);
continue;
}
if(request->data!=NULL)
{
for(int k=0;k<request->dataCount;k++)free(request->data[k]);
free(request->data);
}
closesocket(clientSocketDescriptor);
break;
}
}
}
}
template<typename p2f,typename ...whatever>
class ThreadManager
{
private:
thread *ttt;
p2f funcAddress;
tuple<whatever...> t;
public:
ThreadManager(p2f f,whatever... n):funcAddress(f),t(n...),ttt(NULL){};
~ThreadManager()
{
if(ttt)
{
this->ttt->join();
delete ttt;
}
}
ThreadManager(const ThreadManager &other)=delete;
ThreadManager & operator =(const ThreadManager &other)=delete;
void * operator new(size_t)=delete;
void start()
{
ThreadStarter(t,index_sequence_for<whatever...>());
}
template<size_t ...c>
void ThreadStarter(tuple<whatever...> &t,index_sequence<c...>)
{
this->ttt=new thread(funcAddress,get<c>(t)...);
}
};
class HttpRock //the multithreaded server
{
private:
string folderPath;
int serverSocketDescriptor,clientSocketDescriptor;
map<string,void(*)(Request &,Response &)>requestMappings;
public:
HttpRock()
{
this->folderPath="";
}
~HttpRock()
{
closesocket(serverSocketDescriptor);
WSACleanup();
}
void useStatic(string folderPath)
{
this->folderPath=folderPath;
}
void get(string url,void(*callBack)(Request &,Response &))
{
if(url.length()==0||callBack==NULL)return;
requestMappings.insert(pair<string,void(*)(Request &,Response &)>(url,callBack));
}
void Listen(int port,void(*callBack)(Error &))
{
WORD ver;
int success,len;
struct sockaddr_in serverSocketInformation;
struct sockaddr_in clientSocketInformation;
WSADATA wsaData;
ver=MAKEWORD(1,1);
WSAStartup(ver,&wsaData);
serverSocketDescriptor=socket(AF_INET,SOCK_STREAM,0);
if(serverSocketDescriptor<0)
{
char message[101];
strcpy(message,"Unable to create a socket");
Error  error(message);
callBack(error);
return;
}
serverSocketInformation.sin_family=AF_INET;
serverSocketInformation.sin_port=htons(port);
serverSocketInformation.sin_addr.s_addr=htonl(INADDR_ANY);
success=bind(serverSocketDescriptor,(struct sockaddr *)&serverSocketInformation,sizeof(serverSocketInformation));
if(success<0)
{
char message[101];
sprintf(message,"Unable to bind to port %s",port);
Error  error(message);
callBack(error);
WSACleanup();
return;
}
listen(serverSocketDescriptor,10);
len=sizeof(serverSocketInformation);
while(1)
{
printf("TM web server is ready to accept request \n");
clientSocketDescriptor=accept(serverSocketDescriptor,(struct sockaddr *)&clientSocketInformation,&len);
if(clientSocketDescriptor<0)
{
char message[101];
sprintf(message,"Unable to accept request from port %s",port);
Error  error(message);
callBack(error);
closesocket(serverSocketDescriptor);
WSACleanup();
return ;
}
ThreadManager<void(*)(int,string,map<string,void(*)(Request &,Response &)>),int,string,map<string,void(*)(Request &,Response &)>> tm(seperateThread,clientSocketDescriptor,folderPath,requestMappings);
cout<<"Task is about to start on seperate thread"<<endl;
tm.start();
}
}
};
//The following code is being written by website developer
int main()
{
HttpRock httpRock;
//request for html/css/js files should be served from xyz folder
httpRock.useStatic("xyz");
httpRock.get("/getCustomers",[](Request &request,Response &response)void{
response.setContentType("text/html");
string html;
html="<!DOCTYPE HTML>";
html+="<html>";
html+="<head>";
html+="<meta charset='utf-8'>";
html+="<title> Online Video Rental Library</title>";
html+="</head>";
html+="<body>";
html+="<h1> Admin Dashboard </h1>";
html+="<h3> Customers </h3>";
html+="Sudhir Gupta <br>";
html+="Ramesh Singh <br>";
html+="Gopal Sharma <br>";
html+="<br>";
html+="<a href='index.html'> Home </a>";
html+="</body>";
html+="</html>";
response.Send(html);//this send should get called once only
});
httpRock.Listen(6060,[](Error &error)void{
if(error.hasError())
{
cout<<error.getError()<<endl;
return;
}
cout<<"HTTP rock web server is ready to accept request on port 6060"<<endl;
});
//because of the destructor of httpRock ,the main should not end
//till the server is not shutdown
return 0;
}