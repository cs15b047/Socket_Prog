#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdbool.h>

int main(int argc, char const *argv[])
{
	int s = socket(AF_INET, SOCK_STREAM,IPPROTO_TCP) ;
	int s1 = socket(AF_INET, SOCK_STREAM,IPPROTO_TCP) ;
	int c ;

	char data[201],data1[201];

	struct sockaddr_in serv,cl,serv1 ;

	serv.sin_family = AF_INET ;
	serv.sin_port = htons(10000) ;
	serv.sin_addr.s_addr = inet_addr("127.0.0.1") ;	

	serv1.sin_family = AF_INET ;
	serv1.sin_port = htons(10001) ;
	serv1.sin_addr.s_addr = inet_addr("127.0.0.1") ;	

	bind(s,(struct sockaddr *)&serv,sizeof(serv)) ;

	while(true)
	{		
		listen(s,2) ;			

		int size = sizeof(cl) ;
		c = accept(s,(struct sockaddr *)&cl,&size) ;

		printf("Client added\n");
		read(c,data,200) ;

		connect(s1,(struct sockaddr *)&serv1,sizeof(serv1)) ;
		
		memset(data,'\0',200) ;
		memset(data1,'\0',200) ;		

		scanf("%s",data1) ;
		write(s1,data1,200) ;
		read(s1,data,200) ;

		write(c,data,200) ;
	}


	return 0;
}




