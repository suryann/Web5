#ifndef AUTHORITY_HEADER
#define AUTHORITY_HEADER
#include "../common/DatabaseClass.h"
#include "../common/PacketClass.h"
#include "../common/Parser.h"

class Authority{
	public:
		 Authority();
		 void Wait();
		 ~Authority();
	private:
		 PacketClass Data;
		 ListenerClass LS;
		 DatabaseClass DB;
		 Parser dataParsers;
};

#endif