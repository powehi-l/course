//declariation of the castle
#ifndef CASTLE_H
#define CASTLE_H
#include<string>
#include<vector>
#include"Room.h"

using namespace std;

class castle {
private:
	vector<Room>cas;//a vector of rooms
	bool meetprincrss;//record whether the player meet princess
	int lobby, princess, monster;//record the position of lobby, princess and monter
public:
	castle();
	~castle();
	void construct();//construct the rooms of this castle
	void randowPM();//initialize the position of princess and monster
	void run();//begin our game
};
#endif