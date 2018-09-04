#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>



void dasan(char buf[],char *argv[])
{
	int argc=0;
	char *ptr=strtok(buf," ");
	argv[argc++]=ptr;
	while(ptr!=NULL)
	{
		ptr=strtok(NULL," ");
		argv[argc++]=ptr;
	}
	argv[argc]=NULL;
	return;
	printf("haha");
}
void zhixing(char*argv[])
{
	pid_t pid=fork();

	if(pid>0)
	{
		wait(NULL);
	}
	else if(pid==0)
	{
		execvp(argv[0],argv);
	}
	else
		perror("fork");
	return;
}

void testdasan(){
	char str[]="ls -a -n";
	char *argv[100]={
		NULL};
	dasan(str,argv);
	int i=0;
	for(;argv[i]!=NULL;++i)
	{
		printf("argv[%lu]=%s\n",i,argv[i]);
	}
}
void run()
{
while(1){
	char buf[1024]={0};
	printf("myshell->");
	//scanf("%[^\n]%c",&buf);
	gets(buf);
	char *argv[8];
	dasan( buf,argv);
	zhixing(argv);
}
}

int main()
{
	run();
	//char buf[1024]={0};
	//printf("myshell->");
//	scanf("%[^\n]%c",buf);
//	char *argv[8];
	//testdasan();
//dasan(buf,argv);
	//zhixing(argv);
//}
	return 0;
}

