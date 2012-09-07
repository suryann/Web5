#include "Player.h"

Player::Player(int desc){
	socketID = desc;
}
Player::~Player(){

}
void Player::setStats(const PStats s){
	stats = s;
}
PStats Player::getStats(){
	return stats;
}
int Player::getSocket(){
	return socketID;
}