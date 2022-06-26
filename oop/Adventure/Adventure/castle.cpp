#include"castle.h"
#include<iostream>
#include<fstream>
#include<random>
castle::castle() {
	meetprincrss = false;//at the beginning, player have not meet the princess
	lobby = princess = monster = -1;//not initialize yet
}
castle::~castle() {
	while (!cas.empty()) {
		cas.pop_back();//clear all the room in the cas
	}
}
void castle::construct() {
	string name;
	ifstream file;
	file.open("Castle.txt",ios::in);//open the file
	if (!file)//fail to open the file
	{
		cout << "Error opening file." << endl;
		return;
	}
	file >> this->lobby;//the position of lobby
	//initialize the rooms one by one and push them into the vector cas
	for (int i = 0; i < 25; i++)
	{
		Room *room = new Room;
		file >> room->roomname >> room->exitnum;
		string direction;
		for (int i = 0; i < room->exitnum; i++)//initialize their exit
		{
			file >> direction;
			if (direction == "east") room->east = true;
			if (direction == "west") room->west = true;
			if (direction == "up") room->up = true;
			if (direction == "down") room->down = true;
		}
		cas.push_back(*room);//push room into the cas
	}
	file.close();
}

void castle::randowPM() {
	int prin = rand() % 25;//rand()%25 make a random number between 0 and 25
	int mons = rand() % 25;
	//any two of lobby , princess and monster should not be in the same position
	while (prin == mons || prin == lobby || mons == lobby) {
		prin = rand() % 25;
		mons = rand() % 25;
	}
	this->princess = prin;
	this->monster = mons;
}

void castle::run() {
	Room cur = cas[lobby];//current room in lobby
	int position = lobby;//position record the place of player
	string go, direct;
	//cout << princess << endl;
	//cout << monster << endl;
	while (1) {
		cur.printinfo();//print the information of current room
		cin >> go >> direct;
		if (direct == "east") {
			if (!cur.east) {//if there is no exit in east
				cout << "There is no exit in this direction" << endl;
				continue;
			}
			else {
				position++;//update position
				cur = cas[position];//update the current room
			}
		}
		else if (direct == "west") {
			if (!cur.west) {
				cout << "There is no exit in this direction" << endl;
				continue;
			}
			else {
				position--;
				cur = cas[position];
			}
		}
		else if (direct == "up") {
			if (!cur.up) {
				cout << "There is no exit in this direction" << endl;
				continue;
			}
			else {
				position-=5;
				cur = cas[position];
			}
		}
		else if (direct == "down") {
			if (!cur.down) {
				cout << "There is no exit in this direction" << endl;
				continue;
			}
			else {
				position+=5;
				cur = cas[position];
			}
		}
		else {//invalid direction, input again
			cout << "invalid input! please input again" << endl;
			continue;
		}
		if (position == monster) {//if meet monster, game over
			cout << "a monster eats your brain, game over!" << endl;
			return;
		}
		if (position == princess) {//if meet princess and not meet her before
			if (!meetprincrss) {
				meetprincrss = true;//update meetprincess
				cout << "you find the princess, try to return lobby without meeting monster" << endl;
			}
		}
		if (meetprincrss && position == lobby) {//if meet princess and return lobby, the player wins
			cout << "you have successfully saved princess! congratulations!" << endl;
			return;
		}
		cout << endl;
	}
}