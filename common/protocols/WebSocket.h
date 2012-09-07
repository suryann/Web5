#include "protocol.h"

#ifndef WEBSOCKET_HEADER
#define WEBSOCKET_HEADER

class WebSocket : public protocol{
	public:
		ustring handshake(const ustring);//Applied once after connection
		ustring parse(const ustring);//Do after for each message and return response
};

#endif