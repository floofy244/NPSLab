#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<stdio.h>
#define myport 1234
#define MAX_LEN 100

void replace(char *str, const char *oldWord, const char *newWord)
{
    char *pos, temp[1000];
    int index = 0;
    int owlen;

    owlen = strlen(oldWord);
    while ((pos = strstr(str, oldWord)) != NULL)
    {
        strcpy(temp, str);

        
        index = pos - str;

        
        str[index] = '\0';

    
        strcat(str, newWord);
        
        
        strcat(str, temp + index + owlen);
    }
}




int main()
{
	//create assign bind listen accept operate reply
	int size;
	int s,r,recb,sntb,x,ns,a=0;
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);	//socket creation
	if(sockfd == -1)
	{
		printf("\nSocket creation error.");
		exit(0);
	}
	printf("\nSocket created.");
	struct sockaddr_in	server_addr, c_addr;	
	
	//feeding values into the socket address structure
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(myport);
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	memset( server_addr.sin_zero, '\0', sizeof(server_addr.sin_zero) );
	
	bind( sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr) );
	
	//ready for listening
	listen(sockfd, 10);
	printf("The server is ready for listening.\n");
	size = sizeof(struct sockaddr);
	
	int afd = accept(sockfd, (struct sockaddr *) & c_addr, &size);
	char buff[50];

	recb = recv(afd, buff, sizeof(buff), 0);

	if(recb == -1)
	{
		printf("Receiving failed");
		close(sockfd);
		close(afd);
		exit(0);
	}

	printf("\nFile Name Recieved!\n");

	char fil[50];

	if( access( buff, F_OK ) != -1 ) 
	{
		strcpy(fil,buff);
		strcpy(buff,"File exists");
	
	} else 
	{
		strcpy(buff,"File does not exist!");
	}

	sntb = send(afd,buff,sizeof(buff),0);
	if(sntb == -1)
	{
		printf("\nMessage Sending Failed");
		close(sockfd);
		close(afd);
		exit(0);
	}
	if(strcmp(buff,"File does not exist!") == 0)
	{
		close(sockfd);
		close(afd);
		exit(0);
	}

	int ch = 0;
	while(ch != 4)
	{
		recb=recv(afd,buff,sizeof(buff),0);
		if(recb==-1)
		{
			printf("\nMessage Recieving Failed");		
			close(s);
			close(ns);
			exit(0);
		}	
		ch = buff[0];
		int i,n,n1,n2,j;
		char str[50],str1[50],str2[50];
		char strTempData[MAX_LEN];
	    char **strData = NULL; 
	    int noOfLines = 0;
		switch(ch)
		{
			case 1:
			printf("\nSearching..\n");
			n=buff[1];
			for(i=0;i<n;i++)
				str[i]=buff[i+2];
			str[n]='\0';
			FILE *fp;
			int line_num = 1;
			int find_result = 0;
			char temp[512];
			if((fp = fopen(fil, "r")) == NULL) {
			printf("\nFile not found");		
			close(s);
			close(ns);
			exit(0);
			}
			while(fgets(temp, 512, fp) != NULL) {
			if((strstr(temp, str)) != NULL) {
				find_result++;
			}
			line_num++;
			}
			if(fp) {
			fclose(fp);
			}
			buff[0]=find_result;
			sntb=send(afd,buff,sizeof(buff),0);
			if(sntb==-1)
			{
			printf("\nMessage Sending Failed");
			close(s);
			close(ns);
			exit(0);
			}
			break;

			case 2:
			n1=buff[1];
			i=2;
			for(j=0;j<n1;j++)
			{
				str1[j]=buff[i];
				i++;
			}
			str1[j]='\0';
			recb=recv(afd,buff,sizeof(buff),0);
		if(recb==-1)
		{
			printf("\nMessage Recieving Failed");		
			close(s);
			close(ns);
			exit(0);
		}	
			n=buff[1];
			i=2;
			for(j=0;j<n;j++)
			{
				str2[j]=buff[i];
				i++;
			}
			str2[j]='\0';
			printf("\nReplacing %s with %s..\n",str1,str2);
			FILE * fPtr;
	    	FILE * fTemp;
	    	char buffer[1000];
	    	fPtr  = fopen(fil, "r");
	    	fTemp = fopen("replace.tmp", "w"); 
	    	if (fPtr == NULL || fTemp == NULL)
	   		 {
	        /* Unable to open file hence exit */
	        printf("\nUnable to open file.\n");
	        printf("Please check whether file exists and you have read/write privilege.\n");
	        exit(0);
	    	}
	    	 while ((fgets(buffer, 1000, fPtr)) != NULL)
	    	{
	        
	        replace(buffer, str1, str2);

	        
	        fputs(buffer, fTemp);
	    	}


	   
	    	fclose(fPtr);
	    	fclose(fTemp);


	    
	    	remove(fil);

	    
	    	rename("replace.tmp", fil);
	    	strcpy(buff,"Replace finished!");
	    	sntb=send(afd,buff,sizeof(buff),0);
			if(sntb==-1)
			{
			printf("\nMessage Sending Failed");
			close(sockfd);
			close(afd);
			exit(0);
			}
			break;

			case 3:printf("\nOrdering file..\n");
			
	    FILE * ptrFileLog = NULL;
	    FILE * ptrSummary = NULL;

	    if ( (ptrFileLog = fopen(fil, "r")) == NULL ) {
	        fprintf(stderr,"Error: Could not open %s\n",fil);
	        return 1;
	    }
	    if ( (ptrSummary = fopen("temp.txt", "a")) == NULL ) {
	        fprintf(stderr,"Error: Could not open temp.txt\n");
	        return 1;
	    }

	    
	    while(fgets(strTempData, MAX_LEN, ptrFileLog) != NULL) {
	        
	        if(strchr(strTempData,'\n'))
	            strTempData[strlen(strTempData)-1] = '\0';
	        strData = (char**)realloc(strData, sizeof(char**)*(noOfLines+1));
	        strData[noOfLines] = (char*)calloc(MAX_LEN,sizeof(char));
	        strcpy(strData[noOfLines], strTempData);
	        noOfLines++;
	    }
	    
	    for(i= 0; i < (noOfLines - 1); ++i) {
	        for(j = 0; j < ( noOfLines - i - 1); ++j) {
	            if(strcmp(strData[j], strData[j+1]) > 0) {
	                strcpy(strTempData, strData[j]);
	                strcpy(strData[j], strData[j+1]);
	                strcpy(strData[j+1], strTempData);
	            }
	        }
	    }
	    
	    for(i = 0; i < noOfLines; i++)
	        fprintf(ptrSummary,"%s\n",strData[i]);
	    
	    for(i = 0; i < noOfLines; i++)
	        free(strData[i]);
	    
	    free(strData);
	    remove(fil);
	    rename("temp.txt",fil);
	    fclose(ptrFileLog);
	    fclose(ptrSummary);
			strcpy(buff,"Ordering done!");
			sntb=send(afd,buff,sizeof(buff),0);
			if(sntb==-1)
			{
			printf("\nMessage Sending Failed");
			close(sockfd);
			close(afd);
			exit(0);
			}
			break;

			case 4: ch=4;
			break;
		}
	}
	close(afd);
	close(sockfd);
}


