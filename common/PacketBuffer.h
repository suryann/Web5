#ifndef PACKETBUFFER_HEADER
#define PACKETBUFFER_HEADER

#include <string>
#include "types.h"

class PacketBuffer{
	public:
		PacketBuffer();
		void setData(string);
		void resetData();
		void skipBytes(int);
		string getData();
		//Readers
		unsigned char readByte();
		unsigned short readShort();
		unsigned int readInt();
		string readUTF();
		
		//Writers
		void writeByte(unsigned char);
		void writeShort(unsigned short);
		void writeInt(unsigned int);
		void writeUTF(string);
	private:
		string data;
		int pos;
};

#endif
