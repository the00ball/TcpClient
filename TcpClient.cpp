/*
 * TcpClient.cpp
 *
 *  Created on: 13 de dez de 2016
 *      Author: sirineo
 */

#include "TcpClient.h"

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

TcpClient::TcpClient(std::string host, uint16_t port) : host_(host),port_(port),socket_desc_(0),is_connected_(false)
{
}

TcpClient::~TcpClient()
{
	SocketShutdown();
}

const std::string& TcpClient::getHost() const
{
	return host_;
}

bool TcpClient::Connect()
{
	SocketShutdown();
	socket_desc_ = socket(AF_INET , SOCK_STREAM , 0);
	if (socket_desc_ != -1)
	{
		struct sockaddr_in server;

	    server.sin_addr.s_addr = inet_addr(host_.c_str());
	    server.sin_family = AF_INET;
	    server.sin_port = htons(port_);

	    is_connected_ = connect(socket_desc_, (struct sockaddr *)&server , sizeof(server)) == 0;
	}
	return is_connected_;
}

void TcpClient::SocketShutdown()
{
	if (socket_desc_ > 0)
		shutdown(socket_desc_, SHUT_RDWR);
	socket_desc_ = 0;
	is_connected_ = false;
}

uint16_t TcpClient::getPort() const
{
	return port_;
}


bool TcpClient::IsConnected() const
{
	return is_connected_;
}

int TcpClient::Send(void* buffer, size_t size)
{

	return send(socket_desc_, buffer, size, 0);

}

int TcpClient::Recv(void* buffer, size_t size)
{
	return recv(socket_desc_, buffer, size, 0);
}
