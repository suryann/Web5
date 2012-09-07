#include "PacketBuffer.h"
#include "Logger.h"

PacketBuffer::PacketBuffer():data(string()), pos(0){
}
void PacketBuffer::setData(string d){
	data = d;
	pos = 0;
}
void PacketBuffer::resetData(){
	pos = 0;
}
string PacketBuffer::getData(){
	return data;
}
void PacketBuffer::skipBytes(int a){
	pos += a;
}	
//Readers
unsigned char PacketBuffer::readByte(){
	return data.at(pos++);
}
unsigned short PacketBuffer::readShort(){
	unsigned char shrtC[] = {readByte(), readByte()};
	return (shrtC[0]<<8)|(shrtC[1]);
}

unsigned int PacketBuffer::readInt(){
	unsigned char intC[] = {readByte(), readByte(), readByte(), readByte()};
	return (intC[0]<<24)|(intC[1]<<16)|(intC[2]<<8)|(intC[3]);
}
string PacketBuffer::readUTF(){
	short shrt = readShort();
	string utf =  data.substr( pos, shrt);
	pos += shrt;
	return utf;
}

//Writers
void PacketBuffer::writeByte(unsigned char byte){
	data.insert(pos++, 1, byte);
}
void PacketBuffer::writeShort(unsigned short shrt){
	writeByte(shrt >> 8);
	writeByte(shrt);
}
void PacketBuffer::writeInt(unsigned int i){
	writeByte(i >> 24);
	writeByte(i >> 16);
	writeByte(i >> 8);
	writeByte(i );
}
void PacketBuffer::writeUTF(string str){
	writeShort(str.length());
	data.insert(pos, str);
	pos += str.length();
}
