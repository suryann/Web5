//#include "./auth/auth.h"
#include "./common/Logger.h"
#include "./common/DatabaseClass.h"
#include "./common/PacketClass.h"
#include "./common/Parser.h"
int main(){
	PacketClass Data = PacketClass();
	ListenerClass LS = ListenerClass(1035,10,&Data);
	DatabaseClass DB = DatabaseClass("173.236.70.178","tempost1_c","blue23","tempost1_dev");
	Parser dataParsers = Parser(&LS,&Data,&DB);
	
	LS.Wait();
	
	return 0;
}
