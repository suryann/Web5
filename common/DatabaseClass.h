#ifndef DATABASE_HEADER
#define DATABASE_HEADER
#include <iostream>
#include <string>
#include <mysql/mysql.h>
#include "LockClass.h"
struct queryData{
	MYSQL_RES * table;
};
class DatabaseClass: public LockClass{
	public:
		DatabaseClass(const std::string,const std::string,const std::string,const std::string);
  		~DatabaseClass();

		bool Initialize();
		void query(std::string);
		
	private:
		bool connected;
		std::string dbHost,dbUsername,dbPassword,dbName;
		MYSQL connectionID;
		MYSQL_RES * queryReturn;
		MYSQL_ROW record; 
};
#endif