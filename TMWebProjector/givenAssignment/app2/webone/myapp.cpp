#include<tmwp>
#include<stdio.h>
#include<fstream>
#include<iostream>
#include<stdlib.h>
#include<string.h>
using namespace std;
using namespace tmwp;
void AddStud(Request &request,Response &response)
{
FILE *f;
f=fopen("data.data","ab");
string rollNumber=request.get("rl");
string name=request.get("nm");
printf("%s,%s\n",rollNumber,name);
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
response.write("<!DOCTYPE HTML>");
response.write("<html lang='en'>");
response.write("<head>");
response.write("<meta charset='utf-8'>");
response.write("<title>Whatever</title>");
response.write("</head>");
response.write("<body>");
response.write("<h1>Student Added</h1>");
response.write("<a href='index.html'>OK</a>");
response.write("</body>");
response.write("</html>");
response.close();
}
void GetAllStudents(Request &request,Response &response)
{
response.write("<!DOCTYPE HTML>");
response.write("<html lang='en'>");
response.write("<head>");
response.write("<meta charset='utf-8'>");
response.write("<title>Whatever</title>");
response.write("</head>");
response.write("<body>");
response.write("<table border=1>");
response.write("<tr>");
response.write("<th>RollNumber</th>");
response.write("<th>Name</th>");
response.write("</tr>");
FILE *f;
char rollNumber[11];
char name[21];
int i;
char c;
f=fopen("data.data","rb");
if(f==NULL)
{
printf("No data input\n");
response.write("</table>");
response.write("No data input<br>");
response.write("<a href='index.html'>OK</a>");
response.write("</body></html>");
response.close();
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
response.write("<tr>");
response.write("<td>");
response.write(rollNumber);
response.write("</td>");
response.write("<td>");
response.write(name);
response.write("</td>");
response.write("</tr>");
}
response.write("</table>");
fclose(f);
response.write("<a href='index.html'>OK</a>");
response.write("</body>");
response.write("</html>");
response.close();
}
void SendStudentEditForm(Request &request,Response &response)
{
string rNo=request.get("rl");
FILE *f;
char rollNumber[11];
char name[21];
int i,found;
char c;
f=fopen("data.data","rb");
if(f==NULL)
{
response.write("<!DOCTYPE HTML>");
response.write("<html lang='en'>");
response.write("<head>");
response.write("<meta charset='utf-8'>");
response.write("<title>GECU,Ujjain</title>");
response.write("</head>");
response.write("<body>");
response.write("<h1>Invalid roll number</h1><br>");
response.write("<a href='index.html'>Home</a>");
response.write("</body>");
response.write("</html>");
response.close();
printf("No data input\n");
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
response.write("<!DOCTYPE HTML>");
response.write("<html lang='en'>");
response.write("<head>");
response.write("<meta charset='utf-8'>");
response.write("<title>GECU,Ujjain</title>");
response.write("</head>");
response.write("<body>");
response.write("Student (Edit module)");
response.write("<form method='get' action='updateStudent'>");
response.write("RollNumber<input  id='rl' name='rl' value=");
response.write(rollNumber);
response.write(" readonly><br>");
response.write("Name<input  id='nm' name='nm' value=");
response.write(name);
response.write(" maxlength='20' required><br>");
response.write("<button type='Submit'>Update</button>");
response.write("</form>");
response.write("<a href='index.html'>Home</a>");
response.write("</body>");
response.write("</html>");
response.close();
}
else
{
response.write("<!DOCTYPE HTML>");
response.write("<html lang='en'>");
response.write("<head>");
response.write("<meta charset='utf-8'>");
response.write("<title>GECU,Ujjain</title>");
response.write("</head>");
response.write("<body>");
response.write("<h1>Invalid roll number</h1><br>");
response.write("<a href='index.html'>Home</a>");
response.write("</body>");
response.write("</html>");
response.close();
}
}
void UpdateStudentData(Request &request,Response &response)
{
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
response.write("<!DOCTYPE HTML>");
response.write("<html lang='en'>");
response.write("<head>");
response.write("<meta charset='utf-8'>");
response.write("<title>GECU,Ujjain</title>");
response.write("</head>");
response.write("<body>");
response.write("Student (Edit module)");
response.write("<h3>Student updated</h3>");
response.write("<form method='get' action='index.html'>");
response.write("<button type='Submit'>Ok</button>");
response.write("</form>");
response.write("</body>");
response.write("</html>");
response.close();
}
void sendStudentDeleteConfirmationForm(Request &request,Response &response)
{
string rNo=request.get("rl");
FILE *f;
char rollNumber[11];
char name[21];
int i,found;
char c;
f=fopen("data.data","rb");
if(f==NULL)
{
response.write("<!DOCTYPE HTML>");
response.write("<html lang='en'>");
response.write("<head>");
response.write("<meta charset='utf-8'>");
response.write("<title>GECU,Ujjain</title>");
response.write("</head>");
response.write("<body>");
response.write("<h1>Invalid roll number</h1><br>");
response.write("<a href='index.html'>Home</a>");
response.write("</body>");
response.write("</html>");
response.close();
printf("No data input\n");
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
response.write("<!DOCTYPE HTML>");
response.write("<html lang='en'>");
response.write("<head>");
response.write("<meta charset='utf-8'>");
response.write("<title>GECU,Ujjain</title>");
response.write("</head>");
response.write("<body>");
response.write("Student (Delete module)");
response.write("<form method='get' action='deleteStudent'>");
response.write("RollNumber<input  id='rl' name='rl' value=");
response.write(rollNumber);
response.write(" maxlength='20' readonly><br>");
response.write("Name<input  id='nm' name='nm' value=");
response.write(name);
response.write(" readonly><br>");
response.write("<button type='Submit'>Delete</button>");
response.write("</form>");
response.write("<a href='index.html'>Home</a>");
response.write("</body>");
response.write("</html>");
response.close();
}
else
{
response.write("<!DOCTYPE HTML>");
response.write("<html lang='en'>");
response.write("<head>");
response.write("<meta charset='utf-8'>");
response.write("<title>GECU,Ujjain</title>");
response.write("</head>");
response.write("<body>");
response.write("<h1>Invalid roll number</h1><br>");
response.write("<a href='index.html'>Home</a>");
response.write("</body>");
response.write("</html>");
response.close();
}
}
void deleteStudentData(Request &request,Response &response)
{
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
response.write("<!DOCTYPE HTML>");
response.write("<html lang='en'>");
response.write("<head>");
response.write("<meta charset='utf-8'>");
response.write("<title>GECU,Ujjain</title>");
response.write("</head>");
response.write("<body>");
response.write("Student (Delete module)");
response.write("<h3>Student deleted</h3>");
response.write("<form method='get' action='index.html'>");
response.write("<button type='Submit'>Ok</button>");
response.write("</form>");
response.write("</body>");
response.write("</html>");
response.close();
}
int main()
{
TMWebProjector server(8080);
server.onRequest("/addStudent",AddStud);
server.onRequest("/getStudent",GetAllStudents);
server.onRequest("/editStudent",SendStudentEditForm);
server.onRequest("/updateStudent",UpdateStudentData);
server.onRequest("/confirmDeleteStudent",sendStudentDeleteConfirmationForm);
server.onRequest("/deleteStudent",deleteStudentData);
server.start();
return 0;
}