#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<stdio.h>
#define MAXLINE 4096 
#define SERV_PORT 3000 
#define LISTENQ 8 
int main()
{
	int s,r,recb,sntb,x,ns,a=0;
	socklen_t len;
	struct sockaddr_in server,client;
	char buff[100];
	char str[100];
	s=socket(AF_INET,SOCK_STREAM,0);
	if(s==-1)
	{
		printf("\nSocket creation error.");
		exit(0);
	}
	printf("\nSocket created.");

	server.sin_family=AF_INET;
	server.sin_port=htons(3388);
	server.sin_addr.s_addr=htonl(INADDR_ANY);

	r=bind(s,(struct sockaddr*)&server,sizeof(server));
	if(r==-1)
	{
		printf("\nBinding error.");
		exit(0);
	}
	printf("\nSocket binded.");

	r=listen(s,LISTENQ);
	if(r==-1)
	{
		close(s);
		exit(0);
	}
	printf("\nSocket listening.\n");

	int childpid,n,no_of_clients=0;

	for(;;){
	len=sizeof(client);
	ns=accept(s,(struct sockaddr*)&client, &len);
	if(ns==-1)
	{
		close(s);
		exit(0);
	}
	printf("\nSocket accepting.\n");

	if(no_of_clients==2)
	{
		printf("\nMore than 2 clients!\n");
		close(ns);
		break;
	}
	no_of_clients++;
	printf("\n%d", no_of_clients);
	
	if ( (childpid = fork ()) == 0 ) {
	close (s);
	n = recv(ns, buff, sizeof(buff),0);
	
	if (n < 0){
	printf("%s\n", "Read error");
	exit(0);
	}
	FILE *fptr;
	fptr=fopen("message.txt","a");
	fputs(buff,fptr);
	fclose(fptr);
	char buff2[50];
	n = recv(ns, buff2, sizeof(buff2),0);
	if (n < 0){
	printf("%s\n", "Read error");
	exit(0);
	}
	FILE *fptr2;
	fptr2=fopen("ipAdd.txt","a");
	fputs(buff2,fptr2);
	fclose(fptr2);
	if(no_of_clients==2)
	{
		FILE *fp;
		int line_num = 1;
		char temp[512];
		if((fp = fopen("message.txt", "r")) == NULL) {	
		close(s);
		exit(0);
		}
		while(fgets(temp, 512, fp) != NULL) {
		strcpy(str,temp);
		printf("%s\t", str);		
		line_num++;
		}
		if(fp) {
		fclose(fp);
		}
		FILE *fp2;
		int line_num2 = 1;
		char temp2[512];
		if((fp2 = fopen("ipAdd.txt", "r")) == NULL) {	
		close(s);
		exit(0);
		}
		while(fgets(temp2, 512, fp2) != NULL) {
		strcpy(str,temp2);
		printf("\n%s", str);		
		line_num2++;
		}
		if(fp2) {
		fclose(fp2);
		}
	}
	exit(0);
	}
 
close(ns);
}
}
