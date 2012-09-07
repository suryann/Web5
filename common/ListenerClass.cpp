#include "ListenerClass.h"
#include "Logger.h"
#include <cstdio>
ListenerClass::ListenerClass(int port,int queue,PacketClass * p):SocketClass(), ThreadClass(){
	Data = p;
	tempData = packetInformation();
	SocketClass::bindTo(port);
	SocketClass::listenTo(queue);
	ThreadClass::Start(this);
	Log("Listener: Starting");
}
ListenerClass::~ListenerClass(){}
void ListenerClass::broadcast(int bdesc, const string msg){
	std::map<int, Player>::iterator it;
	for(it=users.begin(); it!=users.end(); it++)
		if(bdesc!=it->second.getSocket())
			  sendTo(it->second.getSocket(), msg);
}
void ListenerClass::sendTo(int desc, const string packet){
	send(desc, packet.c_str(), packet.length(), 0);
}
void ListenerClass::addConnection(int desc){
	Log("Listener: User Connected");
	try{
		SocketClass::setNonBlocking(desc);
		ev.events = EPOLLIN | EPOLLET;
		ev.data.fd = desc;
		if(epoll_ctl(eventFD, EPOLL_CTL_ADD, desc, &ev)<0)
			throw LogString("Unable to add new connection");
	}catch(LogString e){
		Log("Listener: "+ e);
	}
}
void ListenerClass::removeConnection(int desc){
	Log("Listener: User Disconnect");
	try{
		if(epoll_ctl(eventFD, EPOLL_CTL_DEL, desc ,NULL)<0)
			throw LogString("User Doesn't Exist");
		removePlayer(desc);//Clear it if it exists or not.
		close(desc);
	}catch(LogString e){
		Log("Listener: "+ e);
	}
}
Player * ListenerClass::getPlayer(int key){
	if(users.find(key)!=users.end())
		return &users.find(key)->second;
	else
		return NULL;
}
void ListenerClass::addPlayer(int desc, PStats ps){
	users.insert (std::pair<int, Player>(desc, Player(desc)));
	
}
void ListenerClass::removePlayer(int key){
	std::map<int, Player>::iterator it = users.find(key);
	if(it != users.end())
		users.erase(it);
}
void ListenerClass::Setup(){
	try{
		eventFD = epoll_create(10);//10 Doesn't mean anything after Linux Kern 2.6.8
		if(eventFD<0)
			  throw LogString("Unable to create an epoll Pipe");
		ev.events = EPOLLIN;//Accept incoming on the following setup
		ev.data.fd = SocketClass::socketDesc;
		if(epoll_ctl(eventFD,EPOLL_CTL_ADD,SocketClass::socketDesc, &ev)<0)
			  throw LogString("Unable to setup Listener!");
	}catch(LogString e){
		Log("Listener: " + e);
		std::exit(0);
	}
}
void ListenerClass::Execute(void * arg){
	Log("Listener: Started");
	unsigned char buffer[1024];
	try{
		for(;;){
			eventsOccuring = epoll_wait(eventFD, eventsList, MAX_EVENTS, -1);
			
			if(eventsOccuring < 0){
				  throw LogString("Unable to wait error occured");
			}
			for(int ce = 0; ce < eventsOccuring; ce++){
				if(eventsList[ce].data.fd == SocketClass::socketDesc){
					//Incoming Connection
					incomingFD = accept(SocketClass::socketDesc, (sockaddr *)&tempInfo, &tempLen);
					addConnection(incomingFD);
				}else{
					//Receving Information 
					memset(buffer, 0x0, 1024);
					if(recv(eventsList[ce].data.fd,buffer,sizeof(buffer)-1,0)==0){
						 removeConnection(eventsList[ce].data.fd);
						 continue;
					}
					tempData.socket = eventsList[ce].data.fd;
					tempData.buffer = string(buffer,sizeof(buffer)*sizeof(unsigned char));
					Data->insert(tempData);
					Data->post();
				}
			}
		}
	}catch(LogString e){
		Log("Listener: " + e);
		std::exit(0);
	}
}
