#include<iostream>
#include<string.h>
using namespace std;
int main()
{
char arr[]={'a','b'};
string str;
strcpy(str.c_str(),arr);
cout<<str<<endl;
return 0;
}