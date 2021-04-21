#include<tmwp>
#include<stdio.h>
#include<fstream>
#include<iostream>
#include<stdlib.h>
#include<string.h>
using namespace std;
using namespace tmwp;
void FuncOne(Request &request,Response &response)
{
request.setInt("abcd",123);
request.setInt("pqr",355);
request.setInt("xyz",33);
cout<<"One got called"<<endl;
request.forward("/xyz.html");
}
void FuncTwo(Request &request,Response &response)
{
int x=request.getInt("abcd");
printf("**%d**\n",x);
int x1=request.getInt("pqr");
printf("**%d**\n",x1);
int x2=request.getInt("xyz");
printf("**%d**\n",x2);
int k=request.getInt("xyzuu");
printf("**%d**\n",k);
cout<<"Two got called"<<endl;
response.close();
}
void FuncThree(Request &request,Response &response)
{
cout<<"Three got called"<<endl;
response.write("<!DOCTYPE HTML>");
response.write("<html lang='en'>");
response.write("<head>");
response.write("<title>GECU,Ujjain</title>");
response.write("</head>");
response.write("<body>");
response.write("<h1>cool</h1>");
response.write("</body>");
response.write("</html>");
request.forward("/xyz.html");
response.close();
}
int main()
{
TMWebProjector server(8080);
server.onRequest("/one",FuncOne);
server.onRequest("/two",FuncTwo);
server.onRequest("/three",FuncThree);
server.start();
return 0;
}