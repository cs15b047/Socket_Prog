#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>

int main(int argc, char const *argv[])
{
	int c = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP) ;

	char str[200],str1[200] ;

	struct sockaddr_in serv ;

	serv.sin_family = AF_INET ;
	serv.sin_port = htons(10000) ;
	serv.sin_addr.s_addr = inet_addr("127.0.0.1") ;

	connect(c,(struct sockaddr *) &serv,sizeof(serv)) ;

	scanf("%s",str) ;

	write(c,str,strlen(str)); 
	read(c,str1,200) ;

	printf("%s\n",str1 );

	return 0;
}