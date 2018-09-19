#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

int main()
{

  int clientSocket;

  char buffer[1024];

  struct sockaddr_in serverAddr, clientAddr;

  socklen_t addr_size;

  /*---- Create the socket. The three arguments are: ----*/

  /* 1) Internet domain 2) Stream socket 3) Dlefault protocol (TCP in this case) */

  clientSocket = socket(PF_INET, SOCK_STREAM, 0);

  /*---- Configure settings of the server address struct ----*/

  /* Address family = Internet */

  serverAddr.sin_family = AF_INET;

  /* Set port number, using htons function to use proper byte order */

  serverAddr.sin_port = htons(7891);

  /* Set IP address to localhost */

  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

  /* Set all bits of the padding field to 0 */

  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

  /*---- Connect the socket to the server using the address struct ----*/

  connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr));

  /* ----  Send something to server ---- */

  printf("Enter message to send to server = ");
  scanf("%s", &buffer);

  send(clientSocket, buffer, 1024, 0);

  recv(clientSocket, buffer, 1024, 0);

  printf("\nData received from server: %s\n", buffer);

  return 0;
}
