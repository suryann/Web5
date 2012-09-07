#include "auth.h"
using namespace std;
Authority::Authority():{
	 /*
	dataParsers.push_back(Parser(&LS,&Data,&DB));
	dataParsers.push_back(Parser(&LS,&Data,&DB));
	dataParsers.push_back(Parser(&LS,&Data,&DB));
	dataParsers.push_back(Parser(&LS,&Data,&DB));
	*/
	cout<<"Started Authorization Server"<<endl;	
}

Authority::~Authority(){}

void Authority::Wait(){
	LS.Wait();
}