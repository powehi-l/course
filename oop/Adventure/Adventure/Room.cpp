#include"Room.h"
#include<iostream>
#include<string>
Room::Room() {
	east = west = up = down = false;
	princess = monster = false;
	exitnum = 0;
}

Room::~Room() {
}

void Room::printinfo() {
	cout << "Welcome come to the " << this->roomname << ". ";
	if (this->exitnum == 0)// there is no exit
		cout << "There is no exit.";
	else {
		cout << "There is " << this->exitnum << " exit: ";
		string record[4];//store the exact exit
		int i = 0;
		if (this->east) record[i++] = "east";
		if (this->west) record[i++] = "west";
		if (this->up) record[i++] = "up";
		if (this->down) record[i++] = "down";
		for (int i = 0; i < this->exitnum; i++) {
			cout << record[i];//print this exit
			if (i == this->exitnum - 2)	cout << " and ";//if it's the last two exit, print and
			else if (i == this->exitnum - 1) cout << "."<<endl;//if it's the last exit, print "."
			else cout << ", ";
		}
		cout << "Enter your command:";
	}
}