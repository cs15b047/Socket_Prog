#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>

int main(int argc, char const *argv[])
{
	int c = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP) ;

	char str[201],str1[201] ;

	struct sockaddr_in serv,serv1,cl1 ;

	int c1 = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP) ;

	serv1.sin_family = AF_INET ;
	serv1.sin_port = htons(10001) ;
	serv1.sin_addr.s_addr = inet_addr("127.0.0.1") ;	

	bind(c1,(struct sockaddr*) &serv1,sizeof(serv1)) ;

	listen(c1,2) ;

	int temp = (sizeof(cl1)) ;
	int c2 = accept(c1,(struct sockaddr*)&cl1,&temp) ;

	memset(str1,'\0',200) ;
	memset(str,'\0',200) ;
	read(c2,str1,200) ;
	printf("%s\n",str1 );
	scanf("%s",str) ;
	strcat(str,str1) ;
	write(c2,str,strlen(str)) ;	

	return 0;
}