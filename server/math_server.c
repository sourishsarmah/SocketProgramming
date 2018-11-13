#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{

  int welcomeSocket, newSocket;

  char buffer[1024];

  struct sockaddr_in serverAddr;

  struct sockaddr_in serverStorage;

  socklen_t addr_size;

  /*---- Create the socket. The three arguments are: ----*/

  /* 1) Internet domain 2) Stream socket 3) Default protocol (TCP in this case) */

  welcomeSocket = socket(PF_INET, SOCK_STREAM, 0);

  /*---- Configure settings of the server address struct ----*/

  /* Address family = Internet */

  serverAddr.sin_family = AF_INET;

  /* Set port number, using htons function to use proper byte order */

  serverAddr.sin_port = htons(16070);

  /* Set IP address to localhost */

  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

  /* Set all bits of the padding field to 0 */

  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

  /*---- Bind the address struct to the socket ----*/

  bind(welcomeSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr));

  /*---- Listen on the socket, with 5 max connection requests queued ----*/

  if (listen(welcomeSocket, 5) == 0)

    printf("Listening\n");

  else

    printf("Error\n");

  /*---- Accept call creates a new socket for the incoming connection ----*/

  while (1)
  {

    addr_size = sizeof serverStorage;

    newSocket = accept(welcomeSocket, (struct sockaddr *)&serverStorage, &addr_size);

    /*---- Identify clients like this. The following information of client are taken from client due to connect function ----*/
    //Change of the following information at client side can not be done. However, padding field may be changed and that may be tried

    struct sockaddr_in *cliIP = (struct sockaddr_in *)&serverStorage;

    struct in_addr ipAddr = cliIP->sin_addr;

    char str[INET_ADDRSTRLEN];

    inet_ntop(AF_INET, &ipAddr, str, INET_ADDRSTRLEN);

    char *ID = cliIP->sin_zero;

    char str2[8];

    inet_ntop(AF_INET, &ID, str2, 8);

    printf("\nClient IP is: %s", str);

    printf("\nClient port is: %d", serverStorage.sin_port);

    printf("\nClient padding characters are (should be blank): ");

    int i;

    for (i = 0; i < 8; i++)
    {
      printf("%c", serverStorage.sin_zero[i]);
    }

    /*---- A  one liner ----*/

    printf("\nGot a client connection from IP, port: <%s, %d> (can be used for client identification)\n", inet_ntoa(serverStorage.sin_addr), serverStorage.sin_port);

    recv(newSocket, buffer, 1024, 0);

    printf("\nExpression received from client <%s, %d>: %s\n", inet_ntoa(serverStorage.sin_addr), serverStorage.sin_port, buffer);

    char num1[10], num2[10], op;
    int k = 0, flag = 0, num_one, num_two, ans = 0;
    i = 0;

    while (buffer[i] != '\0')
    {
      if (buffer[i] == '+' || buffer[i] == '-' || buffer[i] == '*' || buffer[i] == '/')
      {
        op = buffer[i++];
        flag = 1;
        num1[k]='\0';
        k = 0;
      }
      if (flag == 0)
      {
        num1[k++] = buffer[i++];
      }
      else
      {
        
        num2[k++] = buffer[i++];
      }
    }
    num2[k]='\0';

    num_one = atoi(num1);
    num_two = atoi(num2);

    if (op == '+')
    {
      ans = num_one + num_two;
    }

    else if (op == '-')
    {
      ans = num_one - num_two;
    }

    else if (op == '*')
    {
      ans = num_one * num_two;
    }

    else if (op == '/')
    {
      ans = num_one / num_two;
    }

    char *answer;
    sprintf(answer, "%d", ans);

    send(newSocket, answer, 23, 0);

    close(newSocket);
  }
  return 0;
}
