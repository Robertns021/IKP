#include <winsock2.h>
#include <stdio.h>
#include <conio.h>

#define SERVER_PORT 15000
#define OUTGOING_BUFFER_SIZE 1024
// for demonstration purposes we will hard code
// local host ip adderss
#define SERVER_IP_ADDERESS "127.0.0.1"

// Initializes WinSock2 library
// Returns true if succeeded, false otherwise.
bool InitializeWindowsSockets();
void Connect(char * queueName);
void SendMessage(char *queueName, char* message, int messageSize);

int main(int argc,char* argv[])
{
	// buffer we will use to store message
    char outgoingBuffer[OUTGOING_BUFFER_SIZE];
	int j = 11; //pomocne promenljive za logiku rada
	char q[10]; //queueName
	do
	{
		printf("Recieve messages - 1, Send messages - 2, Exit - 3");
		scanf("%d", &j);

		if (j == 1)
		{
			printf("Enter queue:\n");
			scanf("%s", &q);
			Connect(q);
		}
		else if (j == 2)
		{
			printf("Enter message from server:\n");
			// Read string from user into outgoing buffer
			gets_s(outgoingBuffer, OUTGOING_BUFFER_SIZE);
			printf("Enter queue:\n");
			char queue[10];
			scanf("%s", &queue);
			/*strcat(queue, "^/");
			strcat(outgoingBuffer, "/^");
			strcat(outgoingBuffer, queue);*/

			SendMessage(queue, outgoingBuffer, strlen(outgoingBuffer));
		}
	} 
	while (j != 3);

	printf("Done, press any key to exit.\n");
	_getch();

    return 0;
}

//Primanje svih poruka sa odabranog queue-a
void Connect(char * queueName)
{

}

//Slanje poruke na odabrani queue
void SendMessage(char *queueName, char* message, int messageSize)
{
	int iResult;
	// Server address
	sockaddr_in serverAddress;
	// port used for communication with server
	int serverPort = SERVER_PORT;
	// size of sockaddr structure    
	int sockAddrLen = sizeof(struct sockaddr);

	// Initialize windows sockets for this process
	InitializeWindowsSockets();

	// Initialize serverAddress structure
	memset((char*)&serverAddress, 0, sizeof(serverAddress));
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = inet_addr(SERVER_IP_ADDERESS);
	serverAddress.sin_port = htons((u_short)serverPort);

	// create a socket
	SOCKET clientSocket = socket(AF_INET,      // IPv4 address famly
		SOCK_DGRAM,   // datagram socket
		IPPROTO_UDP); // UDP
	// check if socket creation succeeded
	if (clientSocket == INVALID_SOCKET)
	{
		printf("Creating socket failed with error: %d\n", WSAGetLastError());
		WSACleanup();
	}

	iResult = sendto(clientSocket,
		message,
		messageSize,
		0,
		(LPSOCKADDR)&serverAddress,
		sockAddrLen);

	if (iResult == SOCKET_ERROR)
	{
		printf("sendto failed with error: %d\n", WSAGetLastError());
		closesocket(clientSocket);
		WSACleanup();
	}

	iResult = closesocket(clientSocket);
	if (iResult == SOCKET_ERROR)
	{
		printf("closesocket failed with error: %d\n", WSAGetLastError());
	}

	iResult = WSACleanup();
	if (iResult == SOCKET_ERROR)
	{
		printf("WSACleanup failed with error: %ld\n", WSAGetLastError());
	}
}

bool InitializeWindowsSockets()
{
    WSADATA wsaData;
	// Initialize windows sockets library for this process
    int iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0)
    {
        printf("WSAStartup failed with error: %d\n", iResult);
        return false;
    }
	return true;
}
