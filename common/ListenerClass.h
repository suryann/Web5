#ifndef LISTENER_HEADER
#define LISTERER_HEADER
#define MAX_EVENTS 10
#include <sys/epoll.h>
#include <iostream>
#include <list>
#include <map>
#include "types.h"
#include "SocketClass.h"
#include "ThreadClass.h"
#include "PacketClass.h"
#include "Player.h"
class ListenerClass: public SocketClass, public ThreadClass{
	 
	public:
		ListenerClass(int,int,PacketClass *);
		void addConnection(int);
		void removeConnection(int);
		void broadcast(int, const string);
		void sendTo(int, const string);
		Player * getPlayer(int);
		void addPlayer(int, PStats);
		void removePlayer(int);
		~ListenerClass();
	private:
		int eventsOccuring,eventFD,incomingFD;
		std::map<int, Player> users;
		PacketClass * Data;
		packetInformation tempData;
		epoll_event ev, eventsList[MAX_EVENTS]; 
		void Setup();
		void Execute(void *);
};

#endif