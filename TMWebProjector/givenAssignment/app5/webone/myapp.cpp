#include<tmwp>
#include<stdio.h>
#include<fstream>
#include<iostream>
#include<stdlib.h>
#include<string.h>
using namespace std;
using namespace tmwp;
struct Mark
{
int rollNumber;
int physicsMarks;
int chemistryMarks;
int mathematicsMarks;
int englishMarks;
int hindiMarks;
};
void Data(Request &request,Response &response)
{
string rollNumber=request.get("rl");
char roll[11];
strcpy(roll,rollNumber.c_str());
int rNumber=atoi(roll);
FILE *f;
f=fopen("marks.xyz","rb");
struct Mark m;
int found=0;
while(1)
{
if(feof(f))break;
fread(&m,sizeof(struct Mark),1,f);
if(m.rollNumber==rNumber)
{
found=1;
break;
}
}
if(found==1)
{
request.setInt("physics",m.physicsMarks);
request.setInt("chemistry",m.chemistryMarks);
request.setInt("mathematics",m.mathematicsMarks);
request.setInt("english",m.englishMarks);
request.setInt("hindi",m.hindiMarks);
request.forward("Marksheet.sct");
}
else
{
response.write("<!DOCTYPE HTML>");
response.write("<head>");
response.write("<meta charset='utf-8'>");
response.write("<title>RESULT</title>");
response.write("</head>");
response.write("<body>");
response.write("<h1>RollNumber:");
response.write(roll);
response.write(" not found</h1>");
response.write("</body>");
response.write("</html>");
}
fclose(f);
response.close();
}
int main()
{
TMWebProjector server(8080);
server.onRequest("/dataSent",Data);
server.start();
return 0;
}