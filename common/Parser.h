#ifndef PARSER_HEADER
#define PARSER_HEADER
#define VER 0x01
#define REGUSER 0x05
#define NEWUSER 0x10
#define UPDATE 0x12
#define MSG 0x11
#define PING 0x25

#define PINGPacket "\xff\0x25"


#include <cstdio>
#include <cstdlib>
#include <string>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include "types.h"
#include "ThreadClass.h"
#include "PacketBuffer.h"
#include "ListenerClass.h"
#include "PacketClass.h"
#include "DatabaseClass.h"
#include "Player.h" 
#include "./hash/md5.h"
#include "./json/jsonxx.h"
#include "./json/json_writer.h"
//create multiple instances of this class and add to main data that *Data will be pointing to.

class Parser : public ThreadClass{
	public:
		  Parser();
		  Parser(ListenerClass *, PacketClass *, DatabaseClass *);
		  ~Parser();
	private:
		  void Setup();
		  void Execute(void*);
		  string handshake(const string);
		  packetInformation tempData;
		  PacketBuffer dataBuffer;
		  ListenerClass * Listener;
		  PacketClass * Data;
		  DatabaseClass * DB;
		  void * dataProcess;
};
#endif