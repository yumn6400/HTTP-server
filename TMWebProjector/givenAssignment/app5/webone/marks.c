#include<stdio.h>
#include<stdlib.h>
struct Mark
{
int rollNumber;
int physicsMarks;
int chemistryMarks;
int mathematicsMarks;
int englishMarks;
int hindiMarks;
};
int main()
{
int i;
int rollNumber;
int physicsMarks;
int chemistryMarks;
int mathematicsMarks;
int englishMarks;
int hindiMarks;
FILE *k;
k=fopen("marks.xyz","wb");
struct Mark a={101,65,70,56,85,70};
struct Mark b={102,60,69,78,80,49};
struct Mark c={103,70,76,69,70,80};
struct Mark d={104,65,62,70,90,87};
struct Mark e={105,60,70,76,80,78};
struct Mark f={106,55,66,63,67,86};
struct Mark g={107,44,46,43,56,56};
struct Mark h={108,46,62,76,33,66};
fwrite(&a,sizeof(struct Mark),1,k);
fwrite(&b,sizeof(struct Mark),1,k);
fwrite(&c,sizeof(struct Mark),1,k);
fwrite(&d,sizeof(struct Mark),1,k);
fwrite(&e,sizeof(struct Mark),1,k);
fwrite(&f,sizeof(struct Mark),1,k);
fwrite(&g,sizeof(struct Mark),1,k);
fwrite(&h,sizeof(struct Mark),1,k);
fclose(k);
return 0;
}