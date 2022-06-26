#ifndef Room_H
#define Room_H
#include<string>

using namespace std;

class Room {
public:
	string roomname;
	int exitnum;//the number of exit
	bool east, west, up, down;//record its exit
	bool princess, monster;//record whether have princess or monster
	Room();//construct a room
	~Room();
	void printinfo();//print the information of the room
};
#endif
