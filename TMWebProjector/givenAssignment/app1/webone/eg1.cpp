#include<iostream>
#include<tmwp>
using namespace tmwp;
using namespace std;
void doSomething(Request &request,Response &response)
{
string n=request.get("nm");
cout<<n<<endl;
string c=request.get("ct");
cout<<c<<endl;
response.write("<!DOCTYPE HTML>");
response.write("<html lang='en'>");
response.write("<head>");
response.write("<meta charset='utf-8'>");
response.write("<title>Whatever</title>");
response.write("</head>");
response.write("<body>");
response.write("Hello");
response.write("<img src=bird.jpg>");
response.write("<h1>How are you</h1>");
response.write("</body>");
response.write("</html>");
response.close();
}
int main()
{
TMWebProjector server(8080);
server.onRequest("/register",doSomething);
server.start();
return 0;
}