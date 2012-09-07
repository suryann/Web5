

#ifndef SOCKET_HEADER
#define SOCKET_HEADER
#include <cstdlib>
#include <cstring>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include "types.h"
class SocketClass{
	public:
		SocketClass();//New Socket
		void setNonBlocking(int);
		void resetPort(int);
		bool bindTo(int);
		bool listenTo(int);
		~SocketClass();
	protected:
		int socketDesc,portNumber,queueList;
		socklen_t tempLen;
		sockaddr tempInfo;
	private:
		bool isBinded,isListening,isReady;
		sockaddr_in info;
};
#endif