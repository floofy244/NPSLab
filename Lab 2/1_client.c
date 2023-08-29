#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/socket.h>
#define myport 1234
int main()
{
	//create assign  listen accept operate reply
	int s, r, recb, sntb, x;
	char buff[50];
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd == -1)
	{	printf("socket creation error");
		exit(0);
	}
	struct sockaddr_in c_addr;
	c_addr.sin_port = htons(myport);
	c_addr.sin_family = AF_INET;
	c_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	memset(c_addr.sin_zero, '\0', sizeof(c_addr.sin_zero));
	
	int size = sizeof(struct sockaddr);
	r = connect(sockfd, (struct sockaddr*) &c_addr, sizeof(c_addr));

	if(r == -1)
	{
		printf("\nConnection Error");
		exit(0);
	}

	printf("\nSocket Connected");

	printf("\n\nType file Name: ");
	scanf("%s", buff);

	sntb = send(sockfd, buff, sizeof(buff), 0);
	if (sntb == -1)
	{
		close(sockfd);
		printf("Message failed to send");
		exit(0);
	}

	recb = recv(sockfd, buff, sizeof(buff), 0);

	if(recb == -1)
	{
		printf("receiving failed");
		close(sockfd);
		exit(0);
	}

	printf("\n\n %s \n\n", buff);

	if(strcmp(buff, "File does not exist!") == 0)
	{
		close(sockfd);
		exit(0);
	}

	int ch = 0;
	while(ch != 4)
	{
		printf("\n1. Search \n2.Replace \n3. Reorder \n4. Exit");
		scanf("%d", ch);
		buff[0] = ch;
		char str1[50], str2[50];

		int n, i, j;
		switch(ch)
		{
			case 1: printf("\nEnter string to be searched: ");
				scanf("%s", str1);
				n = strlen(str1);
				buff[1] = n;
				for (int i = 0; i < n; ++i)
				
					buff[i + 2] = str1[i];
				sntb = send(sockfd, buff, sizeof(buff), 0);
				if(sntb == -1)
				{
					close(sockfd);
					printf("failed to send");
					exit(0);
				}
				recb=recv(s,buff,sizeof(buff),0);
      			if(recb == -1)
      			{
      			printf("\nMessage Recieving Failed"); 
      			close(s);
      			exit(0);
      			}
      			n = buff[0];
      			printf("\nWord found %d number of times!\n",n);
      			break;
			case 2: printf("\nEnter string to be searched and replaced: ");
			      	scanf("%s",str1);
			      	n=strlen(str1);
			      	buff[1] = n;
			      	for(i = 0; i < n; i++)
			        	buff[i+2] = str1[i];
			      	buff[i+2]='\0';
			      	sntb = send(sockfd,buff,sizeof(buff),0);
			      	if(sntb == -1)
			      	{
			      		close(s);
			      		printf("\nMessage Sending Failed");
			      		exit(0);
			      	}
			      	printf("\nEnter new string: ");
			      	scanf("%s",str2);
			      	n=strlen(str2);
			      	buff[1] = n;
			      	i=2;
			      	for(j = 0; j < n; j++)
			      	{
			        	buff[i ]= str2[j];
			        	i++;
			      	}
			      	buff[i] = '\0';
			      	sntb=send(sockfd,buff,sizeof(buff),0);
			      	if(sntb == -1)
			      	{
			      		close(s);
			      		printf("\nMessage Sending Failed");
			      		exit(0);
			      	}
			      	recb=recv(sockfd,buff,sizeof(buff),0);
			      	if(recb == -1)
			      	{
			      		printf("\nMessage Recieving Failed"); 
			      		close(s);
			      		exit(0);
			      	}
			      		printf("%s\n",buff);
			      		break;

			case 3: sntb=send(s,buff,sizeof(buff),0);
          			if(sntb == -1)
          			{
		            	close(s);
		            	printf("\nMessage Sending Failed");
		            	exit(0);
		          	}
          			recb = recv(sockfd,buff,sizeof(buff),0);
      				if(recb == -1)
      				{
				      printf("\nMessage Recieving Failed"); 
				      close(s);
				      exit(0);
				    }
				    printf("%s\n",buff);
      				break;
	        case 4: sntb = send(sockfd,buff,sizeof(buff),0);
	          		if(sntb == -1)
	          		{
	            		close(s);
	            		printf("\nMessage Sending Failed");
	            		exit(0);
	          		}
	      			break;
	        default:
	      			printf("\n Try Again!\n");	
						

		}
	}
}


