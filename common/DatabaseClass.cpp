#include "DatabaseClass.h"
#include "Logger.h"
DatabaseClass::DatabaseClass(const std::string host,const std::string username,const std::string password,const std::string name):connected(false){
	this->dbHost = host;
	this->dbUsername = username;
	this->dbPassword = password;
	this->dbName = name;
	mysql_init(&connectionID);
}
DatabaseClass::~DatabaseClass(){
	if(this->connected){
		  Log("Cleaning up Database Connection");
		  mysql_close(&connectionID);
	}
}

bool DatabaseClass::Initialize(){
	if(!connected){
		if(!mysql_real_connect(&connectionID,this->dbHost.c_str(),this->dbUsername.c_str(),this->dbPassword.c_str(),this->dbName.c_str(),3306,NULL,0)){
			Log(mysql_error(&connectionID));
			return false;
		}
		
		connected = true;
		Log("Connected");
	}
	return true;
}