#include "PacketClass.h"

PacketClass::PacketClass(){/*Constructor*/
}
PacketClass::~PacketClass(){
}
void PacketClass::insert(const packetInformation p){
	packets.push(p); 
}
packetInformation PacketClass::get(){
	packetInformation temp = packets.front();
	packets.pop();
	return temp;	
}
