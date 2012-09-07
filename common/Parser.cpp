#include "Parser.h"
#include "Logger.h"
Parser::Parser(){

}
Parser::Parser(ListenerClass * s, PacketClass * p, DatabaseClass * d){
	Listener = s;
	Data = p;
	DB = d;
	ThreadClass::Start(this);
}
Parser::~Parser(){
}
string Parser::handshake(const string check){
	string response = string();
	
	std::istringstream Converter;
 	string handshakeTemplate = (unsigned char*)("HTTP/1.1 101 WebSocket Protocol Handshake\r\n");
		   handshakeTemplate += (unsigned char*)("Upgrade: WebSocket\r\n");
		   handshakeTemplate += (unsigned char*)("Connection: Upgrade\r\n");
		   handshakeTemplate += (unsigned char*)("Sec-WebSocket-Origin: http://tempostudios.com\r\n");
		   handshakeTemplate += (unsigned char*)("Sec-WebSocket-Location: ws://fserver.lndp.net:1035/\r\n\r\n");
	string NL = (unsigned char*)("\r\n");
	string Key1 = (unsigned char*)("Sec-WebSocket-Key1: ");
	string Key2 = (unsigned char*)("Sec-WebSocket-Key2: ");
	string Token, Key1_num, Key2_num;
	size_t Key1_loc,Key2_loc;	
	unsigned int Key1_int, Key2_int;
	unsigned long n = 0, d = 0;	
	
	//Look to see if information is inside check
	Key1_loc = check.find(Key1);
	Key2_loc = check.find(Key2);
	
	if(Key1_loc!=std::string::npos && Key1_loc!=string::npos){
		//Found handshake so start creating response!
		Key1 = check.substr(Key1_loc+Key1.length(),check.find(NL,Key1_loc)-(Key1_loc+Key1.length()));
		Key2 = check.substr(Key2_loc+Key2.length(),check.find(NL,Key2_loc)-(Key2_loc+Key2.length()));
		Token = check.substr(check.find(NL+NL)+string(NL+NL).length(), 8);
			
		for(unsigned int i=0;i<Key1.length();i++){
			if( Key1.at(i) >= '0' && Key1.at(i) <= '9' ){
				Key1_num += Key1.at(i);
			}else 
			if( Key1.at(i) == ' '){
				d++;
			}
		}
			
		Converter.clear();
		Converter.str((char*)Key1_num.c_str());
		Converter>>n;
			
		Key1_int = n/d;
		d = 0;
		n = 0;
		
		for(unsigned int i=0;i<Key2.length();i++){
			if( Key2.at(i) >= '0' && Key2.at(i) <= '9' ){
				Key2_num += Key2.at(i);
			}else 
			if( Key2.at(i) == ' '){
				d++;
			}
		}
		
		Converter.clear();
		Converter.str((char*)Key2_num.c_str());
		Converter>>n;
			 
		Key2_int = n/d;
			
		unsigned char buf[17];
		buf[0] = (Key1_int&0xff000000) >> 24;
		buf[1] = (Key1_int&0x00ff0000) >> 16;
		buf[2] = (Key1_int&0x0000ff00) >> 8;
		buf[3] = Key1_int&0xff;
		buf[4] = (Key2_int&0xff000000) >> 24;
		buf[5] = (Key2_int&0x00ff0000) >> 16;
		buf[6] = (Key2_int&0x0000ff00) >> 8;
		buf[7] = Key2_int&0xff;
		memcpy(&buf[8], Token.c_str() ,8);
		buf[16] = 0x0;
			 
		unsigned char hash_encKey[17];
		memcpy(hash_encKey,MD5(buf,16).getDigest(), 16);
		hash_encKey[16] = 0x0;
		
		//Concatinate the response for handshake
		
		response = handshakeTemplate.c_str() + string(hash_encKey, 16);
	}
	return response;
}
void Parser::Setup(){
	//Setup here
}
void Parser::Execute(void * arg){
	//Process Data
	//Player * tempPlr;
	for(;;){
		//Wait till theres data to be read!
		Data->wait();	
		//Pop data so no other parser reads it
		tempData = Data->get();
		//Make sure to send policy handshake if its a policy packet.
		string handshakeReturn = handshake(tempData.buffer);
		if(handshakeReturn.length()>0){
			//Log("[Parser] Handshake check");
			Listener->sendTo(tempData.socket, handshakeReturn);
		}else{
			unsigned char type = tempData.buffer.at(0);
			switch((type&0x80)){
				case 0x00:
					//Log("[Parser] Data recv");
					string recv;
					if(tempData.buffer.at(1)!=((unsigned char)0xff)){
						for(unsigned int i=1; i<tempData.buffer.length();i++){
							if(tempData.buffer.at(i)!=((char)0xff)){
								recv += tempData.buffer.at(i);
							}else{
								break;
							}
						}
						std::istringstream input(std::string((char*)recv.c_str()));
        				jsonxx::Object o;
						jsonxx::Object::parse(input, o);
						if(o.has<double>("id")){
							switch((int)o.get<double>("id")){
								case VER:
								{
									Log("[VER] Check");
									if(o.has<double>("version")){
										if((int)o.get<double>("version") == 1){
											Log("[VER] OK ");
											string outData = string((unsigned char*)("\x0{\"id\":1")) +(unsigned char*)("}")+string(1,0xf);
											Listener->sendTo(tempData.socket, outData);
											continue;
										}
									}
									Listener->removeConnection(tempData.socket);
								}
								break;
								default:
									Listener->removeConnection(tempData.socket);
							}					
						}else{
							Listener->removeConnection(tempData.socket);
						}
					}else{
						//websocket data recv
					}
				break;
			}
		}
	}
}
