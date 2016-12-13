#include "TcpClient.h"

#include <stdlib.h>
#include <cstdio>
#include <cstring>


int main(int argc , char *argv[])
{
	TcpClient* client = new TcpClient(argv[1], atoi(argv[2]));

	char server_reply[2000];

	if (!client->Connect())
	{
		puts("Connect failed");
	}
	else
	{
		puts("Connection successfully");
	}

	if (client->SendInt(strlen(argv[3])) < 0 || client->Send(argv[3], strlen(argv[3])) < 0)
	{
		puts("Send failed");
	}
	else
	{
		puts("Data Send");
	}

	if (client->Recv(server_reply, 2000) < 0)
	{
		puts("Recv failed");
	}
	else
	{
		puts("Reply received\n");
		puts(server_reply);
	}

	delete client;

	return 0;
}
