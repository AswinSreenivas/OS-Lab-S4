#include<stdio.h>
#include<unistd.h>
int main()
{
int n=10;
int j;
j=fork();
if(j>0)
{

n++;
printf("Parent process : %d",n);


printf("\n");}
else
{
n--;
printf("Child process : %d",n);
printf("\n");

}
}



















































