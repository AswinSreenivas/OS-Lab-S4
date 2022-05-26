#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
#include <errno.h>
#include<string.h>
#define DATA_SIZE 1000

void ls(){
char dirname[10];
DIR*p;
struct dirent *d;
printf("Enter directory name\n");
scanf("%s",dirname);
p=opendir(dirname);
if(p==NULL)
  {
  perror("Cannot find directory");
  exit(0);
  }
while(d=readdir(p))
  printf("%s\n",d->d_name);


}
int main()
{
	ls();
}
