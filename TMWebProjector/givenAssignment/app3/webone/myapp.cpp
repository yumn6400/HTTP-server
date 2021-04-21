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
cout<<"One got called"<<endl;
request.forward("/xyz.html");
}
void FuncTwo(Request &request,Response &response)
{
cout<<"Two got called"<<endl;
request.forward("/three");
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