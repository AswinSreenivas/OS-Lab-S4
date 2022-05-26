#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
#include <errno.h>
#include<string.h>
#define DATA_SIZE 1000

void grep()
{
char fn[DATA_SIZE],pat[DATA_SIZE],temp[DATA_SIZE];
FILE *fp;
printf("Enter file name : ");
scanf("%[^\n]%*c",fn);
printf("Enter pattern to be searched : ");
scanf("%[^\n]%*c",pat);
printf("/n");
fp=fopen(fn,"r"); 

while(!feof(fp))
{
fgets(temp,DATA_SIZE,fp);
if(strstr(temp,pat))
printf("%s",temp);
}
fclose(fp);
}
int main()
{
grep();
}
