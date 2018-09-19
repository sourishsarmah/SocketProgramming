#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>

int main(void)
{
    int sockfd = 0,n = 0,num=0, value;
    char sendBuff[1025];
    struct sockaddr_in serv_addr;
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0))< 0)
    {
        printf("\n Error : Could not create socket \n");
        return 1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(5000);           
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); 

    if(connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr))<0)
    {
        printf("\n Error : Connect Failed \n");
        return 1;
    }

    printf("Welcome to our shop\n");
    printf("Please enter the first letter of the item you want to buy followed by the quantity\n");
    fgets(sendBuff,1025,stdin);
    if ((send(sockfd,sendBuff,strlen(sendBuff),0))== -1) 
    {
        fprintf(stderr, "Failure Sending Message\n");
        close(sockfd);
    }

    
    num = read(sockfd, &value, sizeof(value));
    if ( num <= 0 )
    {
        printf("Either Connection Closed or Error\n");

    }
    if(value == -1)
    {
        printf("\nThe requested quantity of the item is not available\n");
    } else {
        printf("%d no. of clients have previously bought the ordered item\n",value);
    }
    close(sockfd); 
    return 0;
}
