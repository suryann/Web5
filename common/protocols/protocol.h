#include <string>
#include <iostream>

#ifndef PROTOCOL_HEADER
#define PROTOCOL_HEADER

#define MSG 0x24

typedef std::basic_string<unsigned char> ustring;

class protocol{
	protected:
		 virtual ustring handshake(const ustring) = 0;
		 virtual ustring parse(const ustring) = 0;

};

#endif
