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
	int highest ,client,y=1;

	fd_set set,set_copy ;

	char data[201],data1[201];

	struct sockaddr_in serv,cl,serv1 ;

	setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &y,sizeof(int)) ;

	serv.sin_family = AF_INET ;
	serv.sin_port = htons(10000) ;
	serv.sin_addr.s_addr = inet_addr("127.0.0.1") ;	

	bind(s,(struct sockaddr *)&serv,sizeof(serv)) ;

	listen(s,5) ;

	highest = s ;

	FD_ZERO(&set);
	FD_ZERO(&set_copy) ;

	FD_SET(s,&set) ;
	FD_SET(s,&set_copy) ;

	int iterator ;	

	while(true)
	{			
		set_copy = set ;
		select(highest + 1,&set_copy,NULL,NULL,NULL) ;

		for(iterator = 0;iterator <= highest;iterator++)
		{
			if(FD_ISSET(iterator,&set_copy))
			{
				if(iterator == s) // new conn
				{
					int temp = sizeof(cl) ;
					client = accept(s,(struct sockaddr *)&cl,&temp) ;
					if(client > highest)highest = client ;
					FD_SET(client, &set) ;
				}
				else
				{		
					memset(data, '\0', 200);
					int x = read(iterator,data,200) ;

					if(x >= 0)
					{	
						int i ;
						for(i =0;i <= highest;i++)
						{
							if(FD_ISSET(i,&set))
							{
								if(i != s && i != iterator)
								{
									write(i,data,sizeof(data)) ;
								} 
							}
						}
					}

				}
			}
		}
	}
	return 0;
}
