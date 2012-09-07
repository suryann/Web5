#ifndef PACKET_HEADER
#define PACKET_HEADER
#include <iostream>
#include <queue>
#include "SemaphoreClass.h"
#include "Player.h"
#include "types.h"
struct packetInformation{
	int socket;
	string buffer;
};


class PacketClass : public SemClass{
	public:
	 	PacketClass();
    	~PacketClass();
		void insert(const packetInformation);
		packetInformation get();
	private:
		std::queue<packetInformation> packets;
};
#endif