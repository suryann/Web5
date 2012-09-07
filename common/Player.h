#ifndef PLAYER_HEADER
#define PLAYER_HEADER
#include <string>
struct PStats{
	int level;
	int hp;
	int mp;
	int experience;
	int x;
	int y;
};
class Player{
	public:
	    Player(int);
   	   ~Player();
	   void setStats(const PStats);
	   PStats getStats();
	   int getSocket();
    private:
	   int socketID;
	   std::string name; 
	   PStats stats;
};

#endif