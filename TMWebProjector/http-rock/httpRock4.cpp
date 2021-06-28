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
int changePortNumberTo;
map<string,string> keyValues;
Request()
{
dataCount=0;
changePortNumberTo=0;
}
void setKeyValue(string k,string v)
{
keyValues.insert(pair<string,string>(k,v));
}
string getValue(string k)
{
map<string,string>::iterator iter;
iter=keyValues.find(k);
if(iter==keyValues.end())return string("");
return iter->second;
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
return decode(val);
}
void forward(string forwardTo)
{
this->forwardTo=forwardTo;
}
void changePortNumber(int changePortNumberTo)
{
this->changePortNumberTo=changePortNumberTo;
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
sprintf(header,"HTTP/1.1 404 OK\nContent-Type:%s\n\n",contentType);
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
if(!(this->headerCreated))createHeader();
int len=content.size();
if(len==0)return;
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
char isClientSideResource(char *resource,map<string,void(*)(Request &,Response &)> requestMappings)
{
int i;
map<string,void(*)(Request &,Response &)>::iterator iter;
iter=requestMappings.find(string("/")+string(resource));
if(iter==requestMappings.end()) return 'Y';
for(i=0;resource[i]!='\0'&&resource[i]!='.';i++); 
if(resource[i]=='\0')return 'N';
else if(extensionEquals((getExtension(resource).c_str()),"tpl"))return 'N';
return 'Y';
}
char *isMimeType(Request *request)
{
char *mimeType;
char *resource=request->resource;
mimeType=NULL;
int i,lastIndexOfDot;
for(i=0;resource[i]!='\0'&&resource[i]!='.';i++);
lastIndexOfDot=i;
if(request->isClientSideTechnologyResource&&resource[i]=='\0')
{
mimeType=(char *)malloc(sizeof(char)*10);
strcpy(mimeType,"text/html");
}
else if(resource[i]=='\0')return mimeType;
else if(extensionEquals(resource+lastIndexOfDot+1,"html"))
{
mimeType=(char *)malloc(sizeof(char)*10);
strcpy(mimeType,"text/html");
}
else if(extensionEquals(resource+lastIndexOfDot+1,"css"))
{
mimeType=(char *)malloc(sizeof(char)*9);
strcpy(mimeType,"text/css");
}
else if(extensionEquals(resource+lastIndexOfDot+1,"js"))
{
mimeType=(char *)malloc(sizeof(char)*16);
strcpy(mimeType,"text/javascript");
}
else if(extensionEquals(resource+lastIndexOfDot+1,"jpg"))
{
mimeType=(char *)malloc(sizeof(char)*11);
strcpy(mimeType,"image/jpeg");
}
else if(extensionEquals(resource+lastIndexOfDot+1,"jpeg"))
{
mimeType=(char *)malloc(sizeof(char)*11);
strcpy(mimeType,"image/jpeg");
}
else if(extensionEquals(resource+lastIndexOfDot+1,"png"))
{
mimeType=(char *)malloc(sizeof(char)*10);
strcpy(mimeType,"image/png");
}
else if(extensionEquals(resource+lastIndexOfDot+1,"ico"))
{
mimeType=(char *)malloc(sizeof(char)*13);
strcpy(mimeType,"image/x-icon");
}
else if(extensionEquals(resource+lastIndexOfDot+1,"json"))
{
mimeType=(char *)malloc(sizeof(char)*17);
strcpy(mimeType,"application/json");
}
return mimeType;
}
Request *parseRequest(char *bytes,map<string,void(*)(Request &,Response &)> requestMappings)
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

if(strcmp(data[0],"_method")&&strcmp(data[1],"HEAD"))
{
strcpy(method,"HEAD");
}
if(strcmp(data[0],"_method")&&strcmp(data[1],"OPTIONS"))
{
strcpy(method,"OPTIONS");
}
}
}
if(strcmp(method,"POST")==0)
{
for(j=0;bytes[i]!=' ';j++,i++)
{
resource[j]=bytes[i];
}
resource[j]='\0';
while(bytes[i]!='\0')i++;
while(bytes[i]!='\n')i--;
i++;
int si=i;
if(bytes[i]!='\0')
{
dataCount=0;
while(bytes[i]!='\0')
{
if(bytes[i]=='&')dataCount++;
i++;
}
dataCount++;
data=(char **)malloc(sizeof(char *)*dataCount);
int *pc=(int *)malloc(sizeof(int)*dataCount);
i=si;
int j=0;
while(bytes[i]!='\0')
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
if(strcmp(data[0],"_method")&&strcmp(data[1],"PUT"))
{
strcpy(method,"PUT");
}
if(strcmp(data[0],"_method")&&strcmp(data[1],"DELETE"))
{
strcpy(method,"DELETE");
}
if(strcmp(data[0],"_method")&&strcmp(data[1],"CONNECT"))
{
strcpy(method,"CONNECT");
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
request->isClientSideTechnologyResource=isClientSideResource(request->resource,requestMappings);
request->mimeType=isMimeType(request);
}
return request;
}
void seperateThread(int clientSocketDescriptor,int *port,string folderPath,map<string,void(*)(Request &,Response &)> requestMappings )
{
FILE *f;
int len,data,i,rc,success;
char requestBuffer[8193];
char responseBuffer[1025];
char header[501];
success=recv(clientSocketDescriptor,requestBuffer,sizeof(requestBuffer),0);
Request *request=parseRequest(requestBuffer,requestMappings);
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
sprintf(header,"HTTP/1.1 404 OK\nContent-Type:text/html\nContent-Length:%d\n\n",len);
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
sprintf(header,"HTTP/1.1 404 OK\nContent-Type:text/html\nContent-Length:%d\n\n\n",len);
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
sprintf(header,"HTTP/1.1 404 OK\nContent-Type:%s\nContent-Length:%d\n\n",request->mimeType,len);
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
sprintf(header,"HTTP/1.1 404 OK\nContent-Type:%s\nContent-Length:%d\n\n\n",request->mimeType,len);
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
sprintf(header,"HTTP/1.1 404 OK\nContent-Type:text/html\nContent-Length:%d\n\n",len);
send(clientSocketDescriptor,header,strlen(header)+1,0);
sprintf(responseBuffer,"<!DOCTYPE html><html lang='en'><head><title>Whatever</title></head><body><h1>Resource /%s not found</h1></body></html>",request->resource);
send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer)+1,0);
break;
}
else
{
Response response(clientSocketDescriptor);
iter->second(*request,response);
if(request->changePortNumberTo!=0)
{
*port=request->changePortNumberTo;
closesocket(clientSocketDescriptor);
break;
}



if(request->forwardTo.length()>0)
{
free(request->resource);
request->resource=(char *)malloc((sizeof(char)*request->forwardTo.length())+1);
strcpy(request->resource,request->forwardTo.c_str());
request->isClientSideTechnologyResource=isClientSideResource(request->resource,requestMappings);
request->mimeType=isMimeType(request);
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
class HttpRock 
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
int oldPortNumber=port;
WORD ver;
int success,len;
struct sockaddr_in serverSocketInformation;
struct sockaddr_in clientSocketInformation;
WSADATA wsaData;
ver=MAKEWORD(1,1);
WSAStartup(ver,&wsaData);
while(1)
{
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
if(oldPortNumber!=port)
{
closesocket(serverSocketDescriptor);
oldPortNumber=port;
break;
}
printf("TM web server is ready to accept request on port : %d \n",port);
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
ThreadManager<void(*)(int,int *,string,map<string,void(*)(Request &,Response &)>),int,int *,string,map<string,void(*)(Request &,Response &)>> tm(seperateThread,clientSocketDescriptor, &port,folderPath,requestMappings);
cout<<"Task is about to start on seperate thread"<<endl;
tm.start();
}
}
}
};
//The following code is being written by website developer
int main()
{
HttpRock httpRock;
//request for html/css/js files should be served from xyz folder
httpRock.useStatic("xyz");

httpRock.get("/addStudent",[](Request &request,Response &response)void{
response.setContentType("text/html");
string rollNumber=request.get("rl");
string name=request.get("nm");
char oldRollNumber[11];
int i;
char j;
int found=0;
FILE *f;
f=fopen("data.data","rb");
if(f!=NULL)
{
while(1)
{
if(feof(f))break;
j=fgetc(f);
for(i=0;j!='/';i++)
{
if(feof(f))break;
oldRollNumber[i]=j;
j=fgetc(f);
}
oldRollNumber[i]='\0';
if((atoi(rollNumber.c_str()))==(atoi(oldRollNumber)))
{
found=1;
break;
}
while(1)
{
if(feof(f))break;
j=fgetc(f);
if(j=='/')break;
}
}
}
fclose(f);
string html;
if(found==1)
{
html="<!DOCTYPE HTML>";
html+="<html lang='en'>";
html+="<head>";
html+="<meta charset='utf-8'>";
html+="<title>Whatever</title>";
html+="</head>";
html+="<body>";
html+="<h1>RollNumber : ";
html+=rollNumber;
html+=" already present</h1>";
html+="<a href='index.html'>OK</a>";
html+="</body>";
html+="</html>";
response.Send(html);
}
else
{
f=fopen("data.data","ab");
char *str1,*str2;
str1=(char *)malloc(sizeof(char)*strlen(rollNumber.c_str())+1);
strcpy(str1,rollNumber.c_str());
fwrite(str1,strlen(str1),1,f);
fputs("/",f);
str2=(char *)malloc(sizeof(char)*strlen(name.c_str())+1);
strcpy(str2,name.c_str());
fwrite(str2,strlen(str2),1,f);
fputs("/",f);
fclose(f);
string html;
html="<!DOCTYPE HTML>";
html+="<html lang='en'>";
html+="<head>";
html+="<meta charset='utf-8'>";
html+="<title>Whatever</title>";
html+="</head>";
html+="<body>";
html+="<h1>Student Added</h1>";
html+="<a href='index.html'>OK</a>";
html+="</body>";
html+="</html>";
response.Send(html);
}
});


httpRock.get("/getAllStudents",[](Request &request,Response &response)void{
response.setContentType("text/html");
string html;
html="<!DOCTYPE HTML>";
html+="<html lang='en'>";
html+="<head>";
html+="<meta charset='utf-8'>";
html+="<title>Whatever</title>";
html+="</head>";
html+="<body>";
html+="<table border=1>";
html+="<tr>";
html+="<th>RollNumber</th>";
html+="<th>Name</th>";
html+="</tr>";
FILE *f;
char rollNumber[11];
char name[21];
int i;
char c;
f=fopen("data.data","rb");
if(f==NULL)
{
printf("No data input\n");
html+="</table>";
html+="No data input<br>";
html+="<a href='index.html'>OK</a>";
html+="</body></html>";
response.Send(html);
return;
}
fseek(f,0,0);
while(1)
{
c=fgetc(f);
if(feof(f))break;
for(i=0;c!='/';i++)
{
rollNumber[i]=c;
c=fgetc(f);
}
rollNumber[i]='\0';
c=fgetc(f);
for(i=0;c!='/';i++)
{
name[i]=c;
c=fgetc(f);
}
name[i]='\0';
html+="<tr>";
html+="<td>";
html+=rollNumber;
html+="</td>";
html+="<td>";
html+=name;
html+="</td>";
html+="</tr>";
}
html+="</table>";
fclose(f);
html+="<a href='index.html'>OK</a>";
html+="</body>";
html+="</html>";
response.Send(html);
});


httpRock.get("/editStudent",[](Request &request,Response &response)void{
response.setContentType("text/html");
string rNo=request.get("rl");
FILE *f;
char rollNumber[11];
char name[21];
int i,found;
char c;
f=fopen("data.data","rb");
string html;
if(f==NULL)
{
html="<!DOCTYPE HTML>";
html+="<html lang='en'>";
html+="<head>";
html+="<meta charset='utf-8'>";
html+="<title>GECU,Ujjain</title>";
html+="</head>";
html+="<body>";
html+="<h1>Invalid roll number</h1><br>";
html+="<a href='index.html'>Home</a>";
html+="</body>";
html+="</html>";
response.Send(html);
return;
}
fseek(f,0,0);
found=0;
while(1)
{
c=fgetc(f);
if(feof(f))break;
for(i=0;c!='/';i++)
{
rollNumber[i]=c;
c=fgetc(f);
}
rollNumber[i]='\0';
c=fgetc(f);
for(i=0;c!='/';i++)
{
name[i]=c;
c=fgetc(f);
}
name[i]='\0';
if(strcmp(rNo.c_str(),rollNumber)==0)
{
found=1;
break;
}
}
if(found==1)
{
html="<!DOCTYPE HTML>";
html+="<html lang='en'>";
html+="<head>";
html+="<meta charset='utf-8'>";
html+="<title>GECU,Ujjain</title>";
html+="</head>";
html+="<body>";
html+="Student (Edit module)";
html+="<form method='get' action='updateStudent'>";
html+="RollNumber<input  id='rl' name='rl' value=";
html+=rollNumber;
html+=" readonly><br>";
html+="Name<input  id='nm' name='nm' value='";
html+=name;
html+="' maxlength='20' required><br>";
html+="<button type='submit'>Update</button>";
html+="</form>";
html+="<a href='index.html'>Home</a>";
html+="</body>";
html+="</html>";
}
else
{
html="<!DOCTYPE HTML>";
html+="<html lang='en'>";
html+="<head>";
html+="<meta charset='utf-8'>";
html+="<title>GECU,Ujjain</title>";
html+="</head>";
html+="<body>";
html+="<h1>Invalid roll number</h1><br>";
html+="<a href='index.html'>Home</a>";
html+="</body>";
html+="</html>";
}
response.Send(html);
});
httpRock.get("/updateStudent",[](Request &request,Response &response)void{
response.setContentType("text/html");
string rNo=request.get("rl");
string rName=request.get("nm");
FILE *f;
char rollNumber[11];
char name[21];
int i,found;
char c;
f=fopen("data.data","rb");
fseek(f,0,0);
found=0;
FILE *k;
k=fopen("tmp.tmp","wb");
char *str1,*str2;
while(1)
{
c=fgetc(f);
if(feof(f))break;
for(i=0;c!='/';i++)
{
rollNumber[i]=c;
c=fgetc(f);
}
rollNumber[i]='\0';
c=fgetc(f);
for(i=0;c!='/';i++)
{
name[i]=c;
c=fgetc(f);
}
name[i]='\0';
if(strcmp(rNo.c_str(),rollNumber)==0)
{
str1=(char *)malloc(sizeof(char)*strlen(rNo.c_str())+1);
strcpy(str1,rNo.c_str());
fwrite(str1,strlen(str1),1,k);
fputs("/",k);
str2=(char *)malloc(sizeof(char)*strlen(rName.c_str())+1);
strcpy(str2,rName.c_str());
fwrite(str2,strlen(str2),1,k);
fputs("/",k);
}
else
{
str1=(char *)malloc(sizeof(char)*strlen(rollNumber)+1);
strcpy(str1,rollNumber);
fwrite(str1,strlen(str1),1,k);
fputs("/",k);
str2=(char *)malloc(sizeof(char)*strlen(name)+1);
strcpy(str2,name);
fwrite(str2,strlen(str2),1,k);
fputs("/",k);
}
}
fclose(f);
fclose(k);
FILE *f1,*f2;
f1=fopen("data.data","wb");
f2=fopen("tmp.tmp","rb");
fseek(f1,0,0);
fseek(f2,0,0);
while(1)
{
c=fgetc(f2);
if(feof(f2))break;
for(i=0;c!='/';i++)
{
rollNumber[i]=c;
c=fgetc(f2);
}
rollNumber[i]='\0';
c=fgetc(f2);
for(i=0;c!='/';i++)
{
name[i]=c;
c=fgetc(f2);
}
name[i]='\0';
str1=(char *)malloc(sizeof(char)*strlen(rollNumber)+1);
strcpy(str1,rollNumber);
fwrite(str1,strlen(str1),1,f1);
fputs("/",f1);
str2=(char *)malloc(sizeof(char)*strlen(name)+1);
strcpy(str2,name);
fwrite(str2,strlen(str2),1,f1);
fputs("/",f1);
}
fclose(f1);
fclose(f2);
FILE *kk;
kk=fopen("tmp.tmp","wb");
fclose(kk);
string html;
html="<!DOCTYPE HTML>";
html+="<html lang='en'>";
html+="<head>";
html+="<meta charset='utf-8'>";
html+="<title>GECU,Ujjain</title>";
html+="</head>";
html+="<body>";
html+="Student (Edit module)";
html+="<h3>Student updated</h3>";
html+="<a href='index.html'>Ok</a>";
html+="</form>";
html+="</body>";
html+="</html>";
response.Send(html);
});

httpRock.get("/confirmDeleteStudent",[](Request &request,Response &response)void{
response.setContentType("text/html");
string rNo=request.get("rl");
FILE *f;
char rollNumber[11];
char name[21];
int i,found;
char c;
string html;
f=fopen("data.data","rb");
if(f==NULL)
{
html="<!DOCTYPE HTML>";
html+="<html lang='en'>";
html+="<head>";
html+="<meta charset='utf-8'>";
html+="<title>GECU,Ujjain</title>";
html+="</head>";
html+="<body>";
html+="<h1>Invalid roll number</h1><br>";
html+="<a href='index.html'>Home</a>";
html+="</body>";
html+="</html>";
response.Send(html);
return;
}
fseek(f,0,0);
found=0;
while(1)
{
c=fgetc(f);
if(feof(f))break;
for(i=0;c!='/';i++)
{
rollNumber[i]=c;
c=fgetc(f);
}
rollNumber[i]='\0';
c=fgetc(f);
for(i=0;c!='/';i++)
{
name[i]=c;
c=fgetc(f);
}
name[i]='\0';
if(strcmp(rNo.c_str(),rollNumber)==0)
{
found=1;
break;
}
}
if(found==1)
{
html="<!DOCTYPE HTML>";
html+="<html lang='en'>";
html+="<head>";
html+="<meta charset='utf-8'>";
html+="<title>GECU,Ujjain</title>";
html+="</head>";
html+="<body>";
html+="Student (Delete module)";
html+="<form method='get' action='deleteStudent'>";
html+="RollNumber<input  id='rl' name='rl' value=";
html+=rollNumber;
html+=" maxlength='20' readonly><br>";
html+="Name<input  id='nm' name='nm' value='";
html+=name;
html+="' readonly><br>";
html+="<button type='submit'>Delete</button>";
html+="</form>";
html+="<a href='index.html'>Home</a>";
html+="</body>";
html+="</html>";
response.Send(html);
}
else
{
html="<!DOCTYPE HTML>";
html+="<html lang='en'>";
html+="<head>";
html+="<meta charset='utf-8'>";
html+="<title>GECU,Ujjain</title>";
html+="</head>";
html+="<body>";
html+="<h1>Invalid roll number</h1><br>";
html+="<a href='index.html'>Home</a>";
html+="</body>";
html+="</html>";
response.Send(html);
}
});
httpRock.get("/deleteStudent",[](Request &request,Response &response)void{
response.setContentType("text/html");
string rNo=request.get("rl");
FILE *f;
char rollNumber[11];
char name[21];
int i,found;
char c;
f=fopen("data.data","rb");
fseek(f,0,0);
found=0;
FILE *k;
k=fopen("tmp.tmp","wb");
char *str1,*str2;
while(1)
{
c=fgetc(f);
if(feof(f))break;
for(i=0;c!='/';i++)
{
rollNumber[i]=c;
c=fgetc(f);
}
rollNumber[i]='\0';
c=fgetc(f);
for(i=0;c!='/';i++)
{
name[i]=c;
c=fgetc(f);
}
name[i]='\0';
if(strcmp(rNo.c_str(),rollNumber)!=0)
{
str1=(char *)malloc(sizeof(char)*strlen(rollNumber)+1);
strcpy(str1,rollNumber);
fwrite(str1,strlen(str1),1,k);
fputs("/",k);
str2=(char *)malloc(sizeof(char)*strlen(name)+1);
strcpy(str2,name);
fwrite(str2,strlen(str2),1,k);
fputs("/",k);
}
}
fclose(f);
fclose(k);
FILE *f1,*f2;
f1=fopen("data.data","wb");
f2=fopen("tmp.tmp","rb");
fseek(f1,0,0);
fseek(f2,0,0);
while(1)
{
c=fgetc(f2);
if(feof(f2))break;
for(i=0;c!='/';i++)
{
rollNumber[i]=c;
c=fgetc(f2);
}
rollNumber[i]='\0';
c=fgetc(f2);
for(i=0;c!='/';i++)
{
name[i]=c;
c=fgetc(f2);
}
name[i]='\0';
str1=(char *)malloc(sizeof(char)*strlen(rollNumber)+1);
strcpy(str1,rollNumber);
fwrite(str1,strlen(str1),1,f1);
fputs("/",f1);
str2=(char *)malloc(sizeof(char)*strlen(name)+1);
strcpy(str2,name);
fwrite(str2,strlen(str2),1,f1);
fputs("/",f1);
}
fclose(f1);
fclose(f2);
FILE *kk;
kk=fopen("tmp.tmp","wb");
fclose(kk);
string html;
html="<!DOCTYPE HTML>";
html+="<html lang='en'>";
html+="<head>";
html+="<meta charset='utf-8'>";
html+="<title>GECU,Ujjain</title>";
html+="</head>";
html+="<body>";
html+="Student (Delete module)";
html+="<h3>Student deleted</h3>";
html+="<a href='index.html'>Ok</a>";
html+="</form>";
html+="</body>";
html+="</html>";
response.Send(html);
});

httpRock.get("/existsRollNumber",[](Request &request,Response &response)void{
response.setContentType("text/html");
string rollNumber=request.get("rl");
char oldRollNumber[11];
int i;
char j;
FILE *f;
f=fopen("data.data","rb");
int found=0;
if(f!=NULL)
{
while(1)
{
if(feof(f))break;
j=fgetc(f);
for(i=0;j!='/';i++)
{
if(feof(f))break;
oldRollNumber[i]=j;
j=fgetc(f);
}
oldRollNumber[i]='\0';
if((atoi(rollNumber.c_str()))==(atoi(oldRollNumber)))
{
found=1;
break;
}
while(1)
{
if(feof(f))break;
j=fgetc(f);
if(j=='/')break;
}
}
}
fclose(f);
string html;
html="<!DOCTYPE HTML>";
html+="<html lang='en'>";
html+="<head>";
html+="<meta charset='utf-8'>";
html+="<title>404 page</title>";
html+="</head>";
html+="<body>";
if(found==1)html+="<h1>True</h1>";
else html+="<h1>False</h1>";
html+="<a href='index.html'>OK</a>";
html+="</body>";
html+="</html>";
response.Send(html);
});

httpRock.get("/getStudent",[](Request &request,Response &response)void{
response.setContentType("text/html");

string rollNumber=request.get("rl");
string html;
html="<!DOCTYPE HTML>";
html+="<html lang='en'>";
html+="<head>";
html+="<meta charset='utf-8'>";
html+="<title>Whatever</title>";
html+="</head>";
html+="<body>";
html+="<table border=1>";
html+="<tr>";
html+="<th>RollNumber</th>";
html+="<th>Name</th>";
html+="</tr>";
char rRollNumber[11];
char rName[21];
int i;
FILE *f;
f=fopen("data.data","rb");
if(f==NULL)
{
printf("No data present\n");
html+="</table>";
html+="No data present<br>";
html+="<a href='index.html'>OK</a>";
html+="</body></html>";
response.Send(html);
return;
}
fseek(f,0,0);
char j;
int found=0;
while(1)
{
j=fgetc(f);
if(feof(f))break;
for(i=0;j!='/';i++)
{
rRollNumber[i]=j;
j=fgetc(f);
}
rRollNumber[i]='\0';
j=fgetc(f);
for(i=0;j!='/';i++)
{
rName[i]=j;
j=fgetc(f);
}
rName[i]='\0';
if((atoi(rollNumber.c_str()))==(atoi(rRollNumber)))
{
found=1;
break;
}
}
fclose(f);


if(found==1)
{
html+="<tr>";
html+="<td>";
html+=rRollNumber;
html+="</td>";
html+="<td>";
html+=rName;
html+="</td>";
html+="</tr>";
html+="</table>";
html+="<a href='index.html'>OK</a>";
html+="</body>";
html+="</html>";
}
else
{
html+="</table>";
html+="No data present<br>";
html+="<a href='index.html'>OK</a>";
html+="</body></html>";
}
response.Send(html);
});

httpRock.get("/proxy",[](Request &request,Response &response)void{
response.setContentType("text/html");
string portNumber=request.get("pn");
int port=atoi(portNumber.c_str());

request.changePortNumber(port);
string html;
html="<!DOCTYPE HTML>";
html+="<html lang='en'>";
html+="<head>";
html+="<meta charset='utf-8'>";
html+="<title>GECU,Ujjain</title>";
html+="</head>";
html+="<body>";
html+="New Connection";
html+="<h3>connected to Port :";
html+=portNumber;
html+=" </h3>";
html+="</form>";
html+="</body>";
html+="</html>";
response.Send(html);
});




httpRock.Listen(6060,[](Error &error)void{
if(error.hasError())
{
cout<<error.getError()<<endl;
return;
}
cout<<"HTTP rock web server is ready to accept request on port 6060"<<endl;
});
return 0;
}